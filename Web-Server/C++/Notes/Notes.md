# Notes

## What is the file TcpServer1.cpp?
TcpServer1.cpp is the basic web server implementation without multi-threading. To use this, you can simply replace the `#include "TcpServer.h"` in `driver.cpp` with `#include "TcpServer1.h"` and move the files `TcpServer1.cpp` and `TcpServer1.h` to the root directory and build the executable like `g++ routes.cpp TcpServer1.cpp  driver.cpp -o driver`.

## How does an HTTP request look like?

An HTTP request consists of several components, including a request line, headers, and an optional body. Here's a breakdown of the structure of a typical HTTP request:

### Basic Structure of an HTTP Request

```
METHOD /path HTTP/1.1
Host: example.com
User-Agent: YourUserAgent/1.0
Accept: text/html
Content-Type: application/json
Content-Length: 123

{"key": "value"}
```

### Components

1. **Request Line**:
   - **METHOD**: The HTTP method (e.g., `GET`, `POST`, `PUT`, `DELETE`).
   - **Path**: The URL path of the resource being requested (e.g., `/path`).
   - **HTTP Version**: Indicates the version of the HTTP protocol being used (e.g., `HTTP/1.1`).

   **Example**: `GET /api/data HTTP/1.1`

2. **Headers**:
   - Headers provide additional information about the request. Common headers include:
     - `Host`: The domain name of the server (required in HTTP/1.1).
     - `User-Agent`: Information about the client (browser, application, etc.).
     - `Accept`: Specifies the media types that are acceptable for the response.
     - `Content-Type`: The media type of the body of the request (e.g., `application/json`).
     - `Content-Length`: The size of the body in bytes (if present).

3. **Body** (optional):
   - The body contains the data being sent to the server, typically used with `POST`, `PUT`, or `PATCH` methods. The body can be in various formats, such as JSON, XML, or form data.

### Example of a GET Request

```http
GET /api/data HTTP/1.1
Host: example.com
User-Agent: MyApp/1.0
Accept: application/json
```

### Example of a POST Request

```http
POST /api/data HTTP/1.1
Host: example.com
User-Agent: MyApp/1.0
Accept: application/json
Content-Type: application/json
Content-Length: 27

{"key": "value"}
```

## More resources to refer

- [A simple HTTP server from scratch by Trung Vuong Thien](https://trungams.github.io/2020-08-23-a-simple-http-server-from-scratch/)

- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/)
