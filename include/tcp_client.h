//
// Created by XDD on 2022/10/30.
//

#ifndef TCP_CLIENT_TCP_CLIENT_H
#define TCP_CLIENT_TCP_CLIENT_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <tuple>

class TCPClient {
public:
    TCPClient() = default;

    bool dial(std::string host, int port);

    bool send_data(std::string data);

    std::tuple<std::string, bool> receive(int size = 4096);

    std::tuple<std::string, bool> read();

    void exit();

private:
    int socket_{-1};
};


#endif //TCP_CLIENT_TCP_CLIENT_H
