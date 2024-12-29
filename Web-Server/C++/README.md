# Web Server

A simple, extensible TCP server implementation in C++ that handles HTTP requests.

## How to Run

Open the terminal and navigate to the root directory containing the code files (driver.cpp, etc.).

Use a C++ compiler such as g++ to compile the code (C++11 or higher, POSIX-compliant operating system). Here's the build command:

```bash
   g++ routes.cpp TcpServer.cpp  driver.cpp -o driver
```

After successfully building the executable, you can run the program by executing the following command:

```bash
   ./driver <port_number>
```

Replace `<port_number>` with the desired port number (e.g., 8080).

The server will start and listen for incoming connections. You can now send HTTP requests to `http://localhost:<port_number>` or `http://127.0.0.1:<port_number>/`.

## API

### `TcpServer` Class

- `TcpServer(int port)`: Constructor that initializes the server with the specified port.
- `~TcpServer()`: Destructor that cleans up resources.
- `int listenServer()`: Starts listening for client connections.

### Request Handlers

You can add custom request handlers by modifying the `setupHandlers()` method in `TcpServer.cpp`:

```cpp
void TcpServer::setupHandlers() {
    requestHandlers["/"] = {HttpMethod::GET, handleHomePage, "text/html"};
    requestHandlers["/api/greet"] = {HttpMethod::GET, handleGreetRequest, "application/json"};
    // Add more handlers here
}
```

## Code Flow

The TCP server follows this general flow of execution:

1. **Initialization**:
   - The `TcpServer` constructor is called with a port number.
   - `startServer()` is called to create and bind the server socket.
   - `setupHandlers()` is called to initialize the request handlers.

2. **Listening for Connections**:
   - `listenServer()` is called, which puts the server socket in listening mode.
   - The server enters an infinite loop, waiting for client connections.

3. **Handling Client Connections**:
   - When a client connects, `accept()` is called to create a new socket for the client.
   - `handleClient()` is called with the new client socket.

4. **Processing Requests**:
   - `handleClient()` reads the incoming HTTP request from the client socket.
   - It calls `processRequest()` to parse the request and determine the appropriate response.

5. **Generating Responses**:
   - `processRequest()` checks the request against the registered handlers.
   - If a matching handler is found, it's called to generate the response.
   - If no handler matches, a 404 Not Found response is generated.

6. **Sending Responses**:
   - The response is sent back to the client using the client socket.
   - The client socket is then closed.

7. **Continuation**:
   - The server continues listening for new connections (step 2).

Throughout this process, error handling is performed at various stages to manage issues like failed socket operations or invalid requests.


Once the server is up and running, we can try executing these:

## Example Usage:

- Making a request to /

```bash
   curl -i http://localhost:8080
```

Output:

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 655

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome to My Server</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            padding: 20px;
            background-color: #f0f0f0;
        }
        h1 {
            color: #333;
        }
        p {
            font-size: 18px;
            line-height: 1.6;
        }
    </style>
</head>
<body>
    <h1>Welcome to the TCP Server</h1>
    <p>This is a basic HTML page served from the server.</p>
</body>
</html>
```

- Making a request to index.html

```bash
   curl -i http://localhost:8080/index.html
```

Output:

```
HTTP/1.1 200 OK
Content-Type: text/html
Content-Length: 655

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Welcome to My Server</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
            padding: 20px;
            background-color: #f0f0f0;
        }
        h1 {
            color: #333;
        }
        p {
            font-size: 18px;
            line-height: 1.6;
        }
    </style>
</head>
<body>
    <h1>Welcome to the TCP Server</h1>
    <p>This is a basic HTML page served from the server.</p>
</body>
</html>
```

- Making a request to invalid path

```bash
   curl -i http://localhost:8080/invalid.html
```

Output:

```
HTTP/1.1 404 Not Found
Content-Type: text/html
Content-Length: 945

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>404 Not Found</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f8f9fa;
            color: #333;
            text-align: center;
            padding: 50px;
        }
        h1 {
            font-size: 50px;
            margin-bottom: 20px;
        }
        p {
            font-size: 20px;
        }
        a {
            text-decoration: none;
            color: #007bff;
            font-weight: bold;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <h1>404 Not Found</h1>
    <p>Sorry, the page you are looking for does not exist.</p>
    <p>
        You can go back to the <a href="/">homepage</a>
    </p>
</body>
</html>
```

- Making a request to an API with JSON response

```bash
   curl -i http://localhost:8080/api/greet
```

Output:

```
HTTP/1.1 200 OK
Content-Type: application/json
Content-Length: 41

{"message": "Greetings from the server!"}
```

- To display multiple client handling at the same time

```bash
   # Simple test clients:
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
   curl -i http://localhost:8080/api/greet
```

```bash
   # Logs on the server, with 7 connection handling threads:
   Thread Id: 140003710203584
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003701810880
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003693418176
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003685025472
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003710203584
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003701810880
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
   Thread Id: 140003693418176
   Method: GET, Path: /api/greet, HttpVersion: HTTP/1.1
```

## Build Your Own Basic Web Server

This challenge is to build your own Basic Web Server.

This challenge corresponds to the "Build Your Own Basic Web Server" [Coding Challenges series by John Crickett](https://codingchallenges.fyi/challenges/challenge-webserver).
