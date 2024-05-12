//
// Created by urpagin on 11/05/2024.
//

#include "RandomServer.h"
#include <random>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <algorithm>
#include <sstream>


RandomServer::RandomServer(std::string srv_list_filepath)
        : srv_list_filepath(std::move(srv_list_filepath)) {

    size_t retries{0};
    while (retries < MAX_RETRIES) {
        set_random_server();
        if (!this->address.empty()) {
            return;
        }
        ++retries;
    }
    std::cerr << "Exhausted all retries (" << MAX_RETRIES << ") to find a random server. Choosing mc.hypixel.net"
              << std::endl;
    this->address = DEFAULT_ADDR; // $ dig +short mc.hypixel.net
    this->port = DEFAULT_PORT;
}

void RandomServer::set_random_server() {

    std::string line;
    std::ifstream file(srv_list_filepath);
    std::unordered_set<std::string> servers_uset;

    if (!file.is_open()) {
        std::cerr << "Could not open file '" << srv_list_filepath << "'" << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        if (validate_address(line)) {
            servers_uset.insert(line);
        }
    }

    // Now this vector has no doubles.
    std::vector<std::string> servers_vec;
    servers_vec.reserve(servers_uset.size());

    for (const std::string &addr: servers_uset)
        servers_vec.emplace_back(addr);

    const std::string random_server = get_random_item(servers_vec);

    const std::vector<std::string> result = split(random_server, ':');

    this->address = result[0];
    this->port = static_cast<uint16_t>(std::stoi(result[1]));
}

bool RandomServer::validate_address(const std::string &addr) {
    // Return false if is empty or is way too small to have a port and address.
    // The <= 2 also checks if `addr == '\n'`.
    // I am aware that this is quite dirty.
    if (addr.empty() || addr.size() <= 2)
        return false;

    for (const unsigned char c: addr) {
        if (!std::isalnum(c) && c != '.' && c != '-' && c != ':')
            return false;
    }

    const std::vector<std::string> result{split(addr)};

    if (result.size() != 2)
        return false;

    try {
        int temp_port{std::stoi(result[1])};

        if (temp_port < 0 || temp_port > 65535)
            return false;
    } catch (const std::exception &ex) {
        std::cerr << "Address invalid: '" << addr << "'. Cause: " << ex.what() << std::endl;
        return false;
    }

    return true;
}

std::vector<std::string> RandomServer::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


template<typename T>
T RandomServer::get_random_item(const std::vector<T> &vec) {
    if (vec.empty()) {
        throw std::out_of_range("Cannot get random element, vector is empty!");
    }

    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<size_t> dist(0, vec.size() - 1);
    size_t random_index = dist(engine);

    return vec.at(random_index);
}
