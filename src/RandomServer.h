//
// Created by urpagin on 11/05/2024.
//

#ifndef MCRANDOMPROXY_RANDOMSERVER_H
#define MCRANDOMPROXY_RANDOMSERVER_H


#include <cstdint>
#include <string>
#include <vector>

class RandomServer {
public:
    explicit RandomServer(std::string srv_list_filepath = DEFAULT_SRV_LIST_FILEPATH);

    std::string address{};
    uint16_t port{};

private:
    static constexpr size_t MAX_RETRIES{100};
    inline static const std::string DEFAULT_ADDR{"127.0.0.1"}; // loop back
    static constexpr uint16_t DEFAULT_PORT{25565}; // Default MC port
    inline static const std::string DEFAULT_SRV_LIST_FILEPATH{"servers.txt"}; // Default server list file path

    const std::string srv_list_filepath;

    void set_random_server();

    static bool validate_address(const std::string &addr);

    template<typename T>
    static T get_random_item(const std::vector<T> &vec);

    static std::vector<std::string> split(const std::string &s, char delimiter = ':');

};

#endif //MCRANDOMPROXY_RANDOMSERVER_H
