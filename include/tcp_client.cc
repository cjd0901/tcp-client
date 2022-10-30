//
// Created by XDD on 2022/10/30.
//

#include "tcp_client.h"
#include "iostream"

bool TCPClient::dial(std::string host, int port) {
    if (socket_ != -1) {
        return true;
    }
    socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_ == -1) {
        std::cout << "create socket failed" << std::endl;
        return false;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host.c_str());
    serv_addr.sin_port = htons(port);

    auto ok = connect(socket_, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    std::cout << ok << std::endl;
    if (ok < 0) {
        std::cout << "connect failed" << std::endl;
        return false;
    }
    return true;
}

bool TCPClient::send_data(std::string data) {
    if (socket_ == -1) {
        return false;
    }
    auto ok = send(socket_, data.c_str(), strlen(data.c_str()), 0);
    if (ok < 0) {
        std::cout << "send data failed" << std::endl;
        return false;
    }
    return true;
}

std::tuple<std::string, bool> TCPClient::receive(int size) {
    if (socket_ == -1) {
        return std::make_tuple("", false);
    }
    char buffer[size];
    memset(&buffer[0], 0, sizeof(buffer));

    std::string resp;
    auto ok = recv(socket_, buffer, size, 0);
    if (ok < 0) {
        std::cout << "recv failed" << std::endl;
        return std::make_tuple("", false);
    }
    buffer[size - 1] = '\0';
    resp = buffer;
    return std::make_tuple(resp, true);
}

std::tuple<std::string, bool> TCPClient::read() {
    if (socket_ == -1) {
        return std::make_tuple("", false);
    }
    char buffer[1] = {};
    std::string resp;
    while (buffer[0] != '\n') {
        if (recv(socket_, buffer, sizeof(buffer), 0) < 0) {
            std::cout << "read failed" << std::endl;
            return std::make_tuple("", false);
        }
        resp += buffer[0];
    }
    return std::make_tuple(resp, true);
}

void TCPClient::exit() {
    if (socket_ == -1) {
        return;
    }
    close(socket_);
    socket_ = -1;
}
