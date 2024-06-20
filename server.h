#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <string>
#include <boost/asio.hpp>

#include "analyzer.h"
#include "database.h"

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket socket, Analyzer& analyzer);
    ~session();
    void start();

private:
    void do_read();

    tcp::socket m_socket;
    enum { max_length = 1024 };
    char m_data[max_length];
    Analyzer& m_analyzer;
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port);

private:
    void do_accept();

    tcp::acceptor m_acceptor;
    Analyzer m_analyzer;
//    session m_session;
};

#endif // SERVER_H
