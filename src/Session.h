//
// Created by urpagin on 11/05/2024.
//

#ifndef MCRANDOMPROXY_SESSION_H
#define MCRANDOMPROXY_SESSION_H

#include <iostream>
#include <vector>
#include <asio.hpp>
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include "RandomServer.h"


class Session : public std::enable_shared_from_this<Session> {
private:
    asio::ip::tcp::socket client_socket_;
    asio::ip::tcp::socket server_socket_;
    asio::streambuf client_buffer_;
    asio::streambuf server_buffer_;

    const std::string server_list_filepath;
    const RandomServer rnd_srv;

public:
    explicit Session(asio::ip::tcp::socket client_socket);

    void start();

    void connect_to_server();

    void read_from_client();

    void write_to_server();

    void read_from_server();

    void write_to_client();

};


#endif //MCRANDOMPROXY_SESSION_H
