//
// Created by urpagin on 11/05/2024.
//

#include "Session.h"
#include "RandomServer.h"
#include <iostream>
#include <vector>
#include <asio.hpp>


Session::Session(asio::ip::tcp::socket client_socket)
        : client_socket_(std::move(client_socket)),
          server_socket_(asio::make_strand(client_socket_.get_executor())),
          rnd_srv(RandomServer()) {}


void Session::start() {
    connect_to_server();
}

void Session::connect_to_server() {
    auto self(shared_from_this());
    asio::ip::tcp::endpoint server_endpoint(asio::ip::make_address(rnd_srv.address), rnd_srv.port);

    server_socket_.async_connect(server_endpoint, [this, self](const asio::error_code &ec) {
        if (!ec) {

            std::cout << "[ Connecting " <<
            client_socket_.remote_endpoint().address().to_string() <<
            ":" << client_socket_.remote_endpoint().port() <<
            " to " << server_socket_.remote_endpoint().address().to_string() <<
            ":" << server_socket_.remote_endpoint().port() << " ]" << std::endl;

            read_from_client();
            read_from_server();
        } else {
            std::cerr << "Failed to connect to server: " << ec.message() << std::endl;
        }
    });
}

void Session::read_from_client() {
    auto self(shared_from_this());
    client_socket_.async_read_some(asio::buffer(client_buffer_.prepare(128)),
                                   [this, self](const asio::error_code &ec, size_t bytes_transferred) {
                                       if (!ec) {
                                           client_buffer_.commit(bytes_transferred);
                                           write_to_server();
                                       } else {
                                           std::cerr << "Read from client failed: " << ec.message() << std::endl;
                                       }
                                   });
}

void Session::write_to_server() {
    auto self(shared_from_this());
    asio::async_write(server_socket_, client_buffer_.data(),
                      [this, self](const asio::error_code &ec, size_t bytes_transferred) {
                          if (!ec) {
                              client_buffer_.consume(bytes_transferred);
                              read_from_client();
                          } else {
                              std::cerr << "Write to server failed: " << ec.message() << std::endl;
                          }
                      });
}

void Session::read_from_server() {
    auto self(shared_from_this());
    server_socket_.async_read_some(asio::buffer(server_buffer_.prepare(128)),
                                   [this, self](const asio::error_code &ec, size_t bytes_transferred) {
                                       if (!ec) {
                                           server_buffer_.commit(bytes_transferred);
                                           write_to_client();
                                       } else {
                                           std::cerr << "Read from server failed: " << ec.message() << std::endl;
                                       }
                                   });
}

void Session::write_to_client() {
    auto self(shared_from_this());
    asio::async_write(client_socket_, server_buffer_.data(),
                      [this, self](const asio::error_code &ec, size_t bytes_transferred) {
                          if (!ec) {
                              server_buffer_.consume(bytes_transferred);
                              read_from_server();
                          } else {
                              std::cerr << "Write to client failed: " << ec.message() << std::endl;
                          }
                      });
}
