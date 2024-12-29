#include "TcpServer.h"

// Function to process command-line arguments
int processArguments(int argc, char *argv[])
{
    // Check if the user provided at least one argument (the port number)
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <port_number>\n";
        return 1;
    }

    // Access the port number argument
    std::string portStr = argv[1];

    int portNumber;
    try {
        // Convert the string argument to an integer
        portNumber = std::stoi(portStr);
        std::cout << "Port number is: " << portNumber << "\n";
        return 0;
    } catch (const std::invalid_argument& e) {
        // Catch exception if the argument is not a valid integer
        std::cerr << "Error: The provided port number is not a valid integer\n";
    } catch (const std::out_of_range& e) {
        // Catch exception if the integer is out of the acceptable range
        std::cerr << "Error: The provided port number is out of range\n";
    }
    return 1;
}

// Main function
int main(int argc, char* argv[])
{
    // Validate command-line arguments
    if (processArguments(argc, argv) != 0)
        return 1; // Exit if arguments are invalid

    // Retrieve the port number argument
    std::string portStr = argv[1];
    int portNumber = std::stoi(portStr); // Convert to integer

    // Create an instance of TcpServer with the specified port number
    TcpServer server = TcpServer(portNumber);

    // Start the server and begin listening for client connections
    server.listenServer();

    return 0;
}
