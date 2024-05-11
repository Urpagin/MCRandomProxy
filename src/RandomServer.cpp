//
// Created by urpagin on 11/05/2024.
//

#include "RandomServer.h"

RandomServer::RandomServer(std::string srv_list_filepath)
        : srv_list_filepath(std::move(srv_list_filepath)) {
    get_random_server();
}

void RandomServer::get_random_server() {
    this->address = "192.168.1.45";
    this->port = 25590;
}
