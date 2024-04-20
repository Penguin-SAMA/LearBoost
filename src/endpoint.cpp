#include "endpoint.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

// client_end_point 函数创建一个客户端端点，用于连接到服务器
int client_end_point() {
    // 定义一个 IP 地址 和 端口号
    std::string raw_ip_address = "127.4.8.1";
    unsigned short port_num = 3333;

    // 从字符串中解析 IP 地址
    boost::system::error_code ec;
    asio::ip::address ip_address = asio::ip::address::from_string(raw_ip_address, ec);

    if (ec.value() != 0) {
        std::cout << "Failed to parse the IP address. Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
        return ec.value();
    }

    // 创建一个端点
    asio::ip::tcp::endpoint ep(ip_address, port_num);

    return 0;
}

// server_end_point 函数创建一个服务器端点，用于接收客户端连接
int server_end_point() {
    // 定义一个端口号和 IP 地址
    unsigned short port_num = 3333;
    asio::ip::address ip_address = asio::ip::address_v6::any();
    // 创建一个端点
    asio::ip::tcp::endpoint ep(ip_address, port_num);

    return 0;
}

// create_tcp_socket 函数创建一个 TCP 套接字
int create_tcp_socket() {
    // 创建一个 IO 上下文
    asio::io_context ioc;
    // 创建一个 TCP 协议
    asio::ip::tcp protocol = asio::ip::tcp::v4();
    // 创建一个TCP套接字
    asio::ip::tcp::socket sock(ioc);

    // 打开套接字
    boost::system::error_code ec;
    sock.open(protocol, ec);

    if (ec.value() != 0) {
        std::cout << "Failed to open the socket. Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
        return ec.value();
    }

    return 0;
}

// create_acceptor_socket 函数创建一个接收器套接字
int create_acceptor_socket() {
    // 创建一个 IO 上下文
    asio::io_context ioc;
    // asio::ip::tcp::acceptor acceptor(ioc);

    // 创建一个接收器套接字, 并绑定到指定端口
    asio::ip::tcp::acceptor a(ioc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3333));

    return 0;
}

// bind_acceptor_socket 函数绑定接收器套接字
int bind_acceptor_socket() {
    // 定义一个端口号和 IP 地址
    unsigned short port_num = 3333;
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
    // 创建一个接收器套接字
    asio::io_context ioc;
    asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());

    // 绑定套接字
    boost::system::error_code ec;
    acceptor.bind(ep, ec);

    if (ec.value() != 0) {
        std::cout << "Failed to open the socket. Error code = " << ec.value() << ". Message: " << ec.message() << std::endl;
        return ec.value();
    }

    return 0;
}

// connect_to_end 函数连接到指定的端点
int connect_to_end() {
    // 定义一个 IP 地址 和 端口号
    std::string raw_ip_address = "192.168.1.124";
    unsigned short port_num = 3333;

    try {
        // 创建一个端点
        asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address), port_num);

        // 创建一个套接字并连接到端点
        asio::io_context ioc;
        asio::ip::tcp::socket sock(ioc, ep.protocol());
        sock.connect(ep);
    } catch (system::system_error& e) {
        std::cout << "Failed to open the socket. Error code = " << e.code() << ". Message: " << e.what() << std::endl;
        return e.code().value();
    }

    return 0;
}

// dns_connect_to_end 函数连接到指定的端点
int dns_connect_to_end() {
    // 定义一个主机名和端口号
    std::string host = "bilibili.com";
    std::string port_num = "3333";
    asio::io_context ioc;
    asio::ip::tcp::resolver::query resolver_query(host, port_num, asio::ip::tcp::resolver::query::numeric_service);
    asio::ip::tcp::resolver resolver(ioc);

    try {
        // 解析主机名并且连接到端点
        auto it = resolver.resolve(resolver_query);
        asio::ip::tcp::socket sock(ioc);
        asio::connect(sock, it);
    } catch (system::system_error& e) {
        std::cout << "Failed to open the socket. Error code = " << e.code() << ". Message: " << e.what() << std::endl;
        return e.code().value();
    }

    return 0;
}

// accept_new_connection 函数接受新的连接
int accept_new_connection() {
    const int BACKLOG_SIZE = 30;    // 定义一个连接队列的大小
    unsigned short port_num = 3333; // 定义一个端口号
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);
    asio::io_context ioc;

    try {
        // 创建一个接收器套接字并接受新的连接
        asio::ip::tcp::acceptor acceptor(ioc, ep.protocol());
        acceptor.bind(ep);
        acceptor.listen(BACKLOG_SIZE);
        asio::ip::tcp::socket sock(ioc);
        acceptor.accept(sock);
    } catch (system::system_error& e) {
        std::cout << "Failed to open the socket. Error code = " << e.code() << ". Message: " << e.what() << std::endl;
        return e.code().value();
    }

    return 0;
}
