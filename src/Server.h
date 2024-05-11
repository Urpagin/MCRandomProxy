//
// Created by urpagin on 11/05/2024.
//

#ifndef MCRANDOMPROXY_SERVER_H
#define MCRANDOMPROXY_SERVER_H

#include <iostream>
#include <vector>
#include <asio.hpp>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>

class Server {
public:
    // We need an io_context and a port where we listen to
    Server(asio::io_context &io_context, uint16_t port);

private:
    asio::ip::tcp::acceptor m_acceptor;

    void do_accept();

};


#endif //MCRANDOMPROXY_SERVER_H
