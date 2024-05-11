//
// Created by urpagin on 11/05/2024.
//

#ifndef MCRANDOMPROXY_RANDOMSERVER_H
#define MCRANDOMPROXY_RANDOMSERVER_H


#include <cstdint>
#include <string>

class RandomServer {
public:
    explicit RandomServer(std::string srv_list_filepath);

    std::string address{};
    uint16_t port{};

private:
    void get_random_server();

    const std::string srv_list_filepath;
};


#endif //MCRANDOMPROXY_RANDOMSERVER_H
