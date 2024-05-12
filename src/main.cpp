#include "Server.h"
#include <asio.hpp>
#include "RandomServer.h"

uint16_t parse_port(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    // here we create the io_context
    asio::io_context io_context;
    // we'll just use an arbitrary port here
    Server s(io_context, parse_port(argc, argv));
    // and we run until our server is alive
    io_context.run();

    return 0;
}


// Function to parse the port number from command line arguments
uint16_t parse_port(int argc, char *argv[]) {
    int port{25565}; // Default value if no port is specified


    for (size_t i{1}; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-p" || arg == "--port") && i + 1 < argc) {
            port = std::atoi(argv[++i]); // Increment 'i' to get the next argument as the port number
            if (port < 0 || port > 65535) {
                std::cerr << "Invalid port number. It must be between 0 and 65535. Using default port 0." << std::endl;
                return port;
            }
            return static_cast<uint16_t>(port);
        }
    }

    std::cerr << "No port specified. Using default port " << port << "." << std::endl;
    return port; // Return default port if none specified
}

