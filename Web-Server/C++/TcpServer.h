#include <iostream>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <unordered_map>

// Define constants
const int CHUNK_SIZE = 1024;    // Size of the buffer for reading client data
const int BACKLOG = 10;         // Number of connections to queue

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    OPTIONS,
    HEAD,
    INVALID
};

HttpMethod getHttpMethod(const std::string& method);

enum class HttpStatus {
    OK,
    NotFound,
    MethodNotAllowed,
    BadRequest
};

std::string getHttpStatusInString(HttpStatus status);

enum class HttpContentType {
    TEXT_HTML,
    TEXT_PLAIN,
    APPLICATION_JSON,
    APPLICATION_XML
};

std::string getHttpContentTypeInString(HttpContentType type);

// Struct to hold request handler information
struct RequestHandler {
    HttpMethod method;                              // Method that this handler responds to
    std::function<std::string()> handlerFunction;   // Function to handle requests for this URL
    std::string responseType;                       // Content type of the response
};

// TcpServer class definition
class TcpServer {
public:
    TcpServer(int port, int threadPoolSize = 4);    // Constructor to initialize the server
    ~TcpServer();                                   // Destructor to clean up resources
    int listenServer();                             // To start listening for client connections

private:
    int serverSocket;                           // File descriptor for the server socket
    int clientSocket;                           // File descriptor for the client socket
    struct sockaddr_in serverAddr;              // Structure to hold the server address information
    struct sockaddr_in clientAddr;              // Structure to hold the client address information
    socklen_t addrLen;                          // Length of the address structures
    int portNumber;                             // Port number on which the server listens
    std::unordered_map <std::string, RequestHandler> requestHandlers; // To hold request handlers

    std::vector<std::thread> threadPool;        // Thread pool
    std::queue<int> clientQueue;                // Queue to hold client sockets
    std::mutex queueMutex;                      // Mutex to synchronize access to the client queue
    std::condition_variable queueCondVar;       // Condition variable to notify worker threads

    int startServer();                          // To set up the server socket
    void closeSocket(int socket);               // To close the socket
    int handleClient(int clientSocket);         // To handle incoming client requests
    std::tuple<std::string, std::string, std::string> processRequest(const std::string& request);   // Method to process requests
    void setupHandlers();                       // Function to initialize the request handlers
    void workerThread();                        // Method run by each worker thread
};
