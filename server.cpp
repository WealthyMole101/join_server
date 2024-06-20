#include "server.h"
#include <string.h>

using namespace std;
using namespace boost::asio;

session::session(tcp::socket socket, Analyzer& analyzer) : m_socket(std::move(socket)), m_analyzer(analyzer)
{
}

session::~session()
{

}

void session::start()
{
    do_read();
}

void session::do_read()
{
    auto self(shared_from_this());
    m_socket.async_read_some(boost::asio::buffer(m_data, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                std::string str(m_data, length);
                if (get<0>(m_analyzer.analize(str))) {
                    write(m_socket, buffer("OK\n"));
                } else {
                    write(m_socket, buffer("Err TODO\n"));
                }
            }
        });
}

Server::Server(boost::asio::io_context& io_context, short port) : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
    do_accept();
}

void Server::do_accept()
{
    m_acceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::make_shared<session>(std::move(socket), m_analyzer)->start();
        }

        do_accept();
    });
}
