#include <iostream>
#include <string>
#include <vector>

#include <boost/asio/io_context.hpp>

#include "version.h"
#include "async.h"
#include "server.h"
#include "database.h"

int version() {
    return PROJECT_VERSION_PATCH;
}

using namespace std;

int main(int argc, char* argv[])
{
    try {
        boost::asio::io_context io_context;
        Server server(io_context, std::atoi(argv[1]));
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }



    return 0;
}
