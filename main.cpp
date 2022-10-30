#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "include/tcp_client.h"

//int main() {
//    //创建套接字
//    int sock = socket(AF_INET, SOCK_STREAM, 0);
//
//    //向服务器（特定的IP和端口）发起请求
//    struct sockaddr_in serv_addr;
//    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
//    serv_addr.sin_family = AF_INET;  //使用IPv4地址
//    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
//    serv_addr.sin_port = htons(10000);  //端口
//    auto ok = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
//
//    std::string msg = "hello from c++ client";
//    send(sock, msg.c_str(), strlen(msg.c_str()), 0);
//    //读取服务器传回的数据
//    char buffer[40];
//    read(sock, buffer, sizeof(buffer) - 1);
//
//    printf("Message form server: %s\n", buffer);
//
//    //关闭套接字
//    close(sock);
//
//    return 0;
//}
//
int main() {
    TCPClient *client = new TCPClient();
    bool ok = client->dial("127.0.0.1", 10000);
    if (!ok) {
        std::cout << "dial error" << std::endl;
    }
    ok = client->send_data("hello from c++ client");
    if (!ok) {
        std::cout << "send data error" << std::endl;
    }

    auto data = client->read();
//    auto data = client->receive(1024);
    if (std::get<1>(data)) {
        std::cout << "receive data: " << std::get<0>(data) << std::endl;
    }

    client->exit();
}
