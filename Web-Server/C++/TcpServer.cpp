#include "TcpServer.h"
#include "routes.h"

// To get HTTP method
HttpMethod getHttpMethod(const std::string& method)
{
    if (method == "GET") return HttpMethod::GET;
    if (method == "POST") return HttpMethod::POST;
    if (method == "PUT") return HttpMethod::PUT;
    if (method == "DELETE") return HttpMethod::DELETE;
    if (method == "PATCH") return HttpMethod::PATCH;
    if (method == "OPTIONS") return HttpMethod::OPTIONS;
    if (method == "HEAD") return HttpMethod::HEAD;
    return HttpMethod::INVALID; 
}

// To get HTTP status
std::string getHttpStatusInString(HttpStatus status)
{
    switch (status)
    {
        case HttpStatus::OK: return "200 OK";
        case HttpStatus::NotFound: return "404 Not Found";
        case HttpStatus::MethodNotAllowed: return "405 Method Not Allowed";
        case HttpStatus::BadRequest: return "400 Bad Request";
        default: return "Unknown Status";
    }
}

// To get HTTP content type
std::string getHttpContentTypeInString(HttpContentType type)
{
    switch (type)
    {
        case HttpContentType::TEXT_HTML: return "text/html";
        case HttpContentType::TEXT_PLAIN: return "text/plain";
        case HttpContentType::APPLICATION_JSON: return "application/json";
        case HttpContentType::APPLICATION_XML: return "application/xml";
        default: return "application/octet-stream"; // Fallback content type
    }
}

// Constructor implementation
TcpServer::TcpServer(int port, int threadPoolSize)
    : portNumber(port), serverSocket(-1), addrLen(sizeof(serverAddr))
{
    // Initialize the server address structure
    serverAddr.sin_family = AF_INET;            // Set address family to IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY;    // Accept connections from any IP address
    serverAddr.sin_port = htons(portNumber);    // Convert port number to network byte order

    // Start the server and handle any initialization errors
    if (startServer() != 0)
    {
        std::cerr << "Failure in starting the server\n";
        return;
    }

    setupHandlers(); // Initialize the request handlers for different routes

    // Create a pool of worker threads
    for (int i = 0; i < threadPoolSize; ++i)
        threadPool.emplace_back(&TcpServer::workerThread, this);
}

// Destructor implementation
TcpServer::~TcpServer()
{
    // Ensure the server socket is closed when the TcpServer object is destroyed
    closeSocket(serverSocket);

    // Join all worker threads
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        // Notify all threads to exit
        // Empty the queue
        clientQueue = std::queue<int>();
    }

    queueCondVar.notify_all();

    for (auto &thread : threadPool)
    {
        if (thread.joinable())
            thread.join();
    }
}

// Method to listen for incoming client connections
int TcpServer::listenServer()
{
    std::cout << "Server started listening\n";

    // Set the socket to listen for incoming connections with a queue size of BACKLOG
    if (listen(serverSocket, BACKLOG) < 0)
    {
        std::cerr << "Failure in listening server\n";
        closeSocket(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on PORT " << portNumber << "\n";

    while (true) // Infinite loop to accept incoming connections
    {
        // Accept the incoming client connection
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
        if (clientSocket < 0)
        {
            std::cerr << "Failure in accepting the incoming client connection\n";
            continue; // Continue to next iteration on failure
        }

        // Add client socket to the queue
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            clientQueue.push(clientSocket);
        }
        queueCondVar.notify_one(); // Notify a worker thread
    }

    // Close the server socket after exiting the loop (this point is never reached)
    closeSocket(serverSocket);

    return 0;
}

// Start the server
int TcpServer::startServer()
{
    std::cout << "Starting the server\n";
    
    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        std::cerr << "Failure in socket creation\n";
        return 1;
    }

    std::cout << "Socket successfully created\n";

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Failure in binding the socket to the specific address and port\n";
        closeSocket(serverSocket);
        return 1;
    }

    std::cout << "Socket successfully binded to address and port\n";

    return 0;
}

// Close the socket
void TcpServer::closeSocket(int socket)
{
    if (socket >= 0)
        close(socket);
}

// Handle incoming client requests
int TcpServer::handleClient(int clientSocket)
{
    std::string request;
    char buffer[CHUNK_SIZE];
    ssize_t bytesRead;
    bool headersComplete  = false;
    size_t contentLength  = 0;
    size_t totalBytesRead = 0;

    // Read the client request
    while (true)
    {
        bytesRead = read(clientSocket, buffer, CHUNK_SIZE - 1);
        if (bytesRead <= 0)
        {
            if (bytesRead == 0)
                std::cerr << "Client closed the connection\n";
            else
                std::cerr << "Failure in reading from client socket\n";

            closeSocket(clientSocket);
            return 1;
        }

        buffer[bytesRead] = '\0';
        request.append(buffer, bytesRead);
        totalBytesRead += bytesRead;

        if (!headersComplete)
        {
            size_t headerEnd = request.find("\r\n\r\n");
            if (headerEnd != std::string::npos)
            {
                headersComplete = true;

                size_t contentLengthPos = request.find("Content-Length: ");
                if (contentLengthPos != std::string::npos)
                {
                    size_t valueStart = contentLengthPos + 16; // length of "Content-Length: "
                    size_t valueEnd   = request.find("\r\n", valueStart);
                    contentLength     = std::stoul(request.substr(valueStart, valueEnd - valueStart));
                }

                // If we've read beyond the headers, adjust totalBytesRead
                totalBytesRead = request.length() - (headerEnd + 4);
            }
        }

        // If we've read all headers and the full body (if any), we're done
        if (headersComplete && (contentLength == 0 || totalBytesRead >= contentLength))
            break;
    }

    // Process the request and generate a response
    auto [responseBody, status, contentType] = processRequest(request);

    // Create the HTTP response
    std::ostringstream responseStream;
    responseStream << "HTTP/1.1 " << status << "\r\n"
                   << "Content-Type: " << contentType << "\r\n"
                   << "Content-Length: " << responseBody.length() << "\r\n"
                   << "\r\n"
                   << responseBody;

    // Send the HTTP response
    const std::string& response = responseStream.str();
    ssize_t totalBytesSent = 0;
    while (totalBytesSent < response.length())
    {
        ssize_t sent = write(clientSocket, response.c_str() + totalBytesSent, response.length() - totalBytesSent);
        if (sent < 0)
        {
            std::cerr << "Failure in writing to client socket\n";
            closeSocket(clientSocket);
            return 1;
        }
        totalBytesSent += sent;
    }

    // Close the client socket after responding
    closeSocket(clientSocket);
    return 0;
}

void TcpServer::workerThread()
{
    while (true)
    {
        int clientSocket;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCondVar.wait(lock, [this] { return !clientQueue.empty(); });

            clientSocket = clientQueue.front();
            clientQueue.pop();
        }

        std::cout << "Thread Id: " << std::this_thread::get_id() << "\n";

        // Process the client request
        if (handleClient(clientSocket) != 0)
            std::cerr << "Failure in processing the client request\n";
    }
}

// Initialize the request handlers for different routes
void TcpServer::setupHandlers()
{
    // Handle requests to the root path
    requestHandlers["/"] = {HttpMethod::GET, handleHomePage, "text/html"};
    // Handle requests to index.html
    requestHandlers["/index.html"] = {HttpMethod::GET, handleHomePage, "text/html"};
    // Handle requests to dummy.html
    requestHandlers["/dummy.html"] = {HttpMethod::GET, handleDummyPage, "text/html"};
    // Handle API greet requests
    requestHandlers["/api/greet"] = {HttpMethod::GET, handleGreetRequest, "application/json"};
    // Handle API post requests
    requestHandlers["/api/post"] = {HttpMethod::POST, handlePostRequest, "application/json"};
}

/* Processing the client request
    Basic Structure of an HTTP Request:
        METHOD /path HTTP/1.1
        Host: example.com
        User-Agent: YourUserAgent/1.0
        Accept: text/html
        Content-Type: application/json
        Content-Length: 123

        {"key": "value"}
*/
std::tuple<std::string, std::string, std::string> TcpServer::processRequest(const std::string& request)
{
    // Extract the first line of the request
    std::istringstream requestStream(request);
    std::string requestLine;
    std::getline(requestStream, requestLine);

    // Parse the request line
    std::istringstream requestLineStream(requestLine);
    std::string method, path, httpVersion;
    requestLineStream >> method >> path >> httpVersion;

    // Check for valid HTTP methods
    if (getHttpMethod(method) == HttpMethod::INVALID)
    {
        return {"", "405 Method Not Allowed", "text/plain"};
    }

    std::cout << "Method: " << method << ", Path: " << path << ", HttpVersion: " << httpVersion << "\n";

    if (path != "")
    {
        // Find a match in request handlers
        auto it = requestHandlers.find(path);
        if (it != requestHandlers.end())
        {
            // Key found, access the RequestHandler
            const RequestHandler& handler = it->second;
            if (handler.method == getHttpMethod(method)) // If a matching handler is found
            {
                std::string body = handler.handlerFunction();   // Call the handler function
                return {body, getHttpStatusInString(HttpStatus::OK), handler.responseType};  // Return the response body, status, and content type
            }
        }

        // If no handler matched, return a 404 response
        return {handleNotFound(), getHttpStatusInString(HttpStatus::NotFound), getHttpContentTypeInString(HttpContentType::TEXT_HTML)};
    }

    // If the request format is malformed, return a 400 response
    return {"", getHttpStatusInString(HttpStatus::BadRequest), getHttpContentTypeInString(HttpContentType::TEXT_PLAIN)};
}
