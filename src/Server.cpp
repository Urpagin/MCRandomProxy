//
// Created by urpagin on 11/05/2024.
//

#include "Server.h"
#include "Session.h"

#include <iostream>
#include <vector>
#include <asio.hpp>
#include <chrono>
#include <random>


Server::Server(asio::io_context &io_context, uint16_t port)
        : m_acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
    // now we call do_accept() where we wait for clients
    do_accept();
    std::cout << "[[  LISTENING ON 0.0.0.0:" << port << "...  ]]\n\n" << std::endl;
}

void Server::do_accept() {
    // this is an async accept which means the lambda function is
    // executed, when a client connects
    m_acceptor.async_accept([this](asio::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            // let's see where we created our session
            std::cout << "[ creating session on: "
                      << socket.remote_endpoint().address().to_string()
                      << ":" << socket.remote_endpoint().port() << " ]\n";
            // create a session where we immediately call the run function
            // note: the socket is passed to the lambda here
            std::make_shared<Session>(std::move(socket))->start();
        } else {
            std::cout << "Error creating session: " << ec.message() << std::endl;
        }
        // since we want multiple clients to connect, wait for the next one by calling do_accept()
        do_accept();
    });
}