#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../utils/threadPool.hpp"

const int MAX_CONNECTIONS = 10;
const int BUFFER_SIZE = 1024;

void taskFunction(int client_socket)
{
    char buffer[BUFFER_SIZE];
    while (true)
    {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
        std::cout << bytes_read << buffer << std::endl;
        if (bytes_read == -1)
        {
            std::cout << "读取数据失败，连接断开" << std::endl;
            close(client_socket);
            return;
        }

        if (bytes_read == 0)
            break;

        if (write(client_socket, buffer, bytes_read) == -1)
        {
            std::cout << "发送数据失败，连接断开" << std::endl;
            close(client_socket);
            return;
        }
    }
}

int main(int argc, char *argv[])
{
    ThreadPool pool(4);
    // 创建socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cout << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 设置地址可重用
    int reuse_addr = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));

    // 绑定地址和端口
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cout << "Failed to bind socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    // 开始监听
    if (listen(server_socket, MAX_CONNECTIONS) == -1)
    {
        std::cout << "Failed to listen." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started. Listening on port 8080..." << std::endl;

    // 接收连接并处理
    while (true)
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr *)&client_addr, &client_len);
        if (client_socket == -1)
        {
            std::cout << "Failed to accept connection." << std::endl;
            exit(EXIT_FAILURE);
        }

        pool.enqueue(taskFunction, client_socket);
    }

    // 关闭socket
    close(server_socket);

    return 0;
}
