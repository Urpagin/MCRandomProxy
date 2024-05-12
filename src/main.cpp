#include "Server.h"
#include <asio.hpp>
#include "RandomServer.h"

int main() {
    // here we create the io_context
    asio::io_context io_context;
    // we'll just use an arbitrary port here
    Server s(io_context, 25565);
    // and we run until our server is alive
    io_context.run();

    return 0;
}
