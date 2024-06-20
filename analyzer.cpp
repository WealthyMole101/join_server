#include "analyzer.h"

#include <iostream>
#include <tuple>
#include <boost/algorithm/string.hpp>

using namespace std;

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{
}

tuple<bool, string> Analyzer::analize(std::string line)
{
    vector<string> strs;
    boost::split(strs, line, boost::is_any_of(" ,\n"));

    bool result = false;
    if (strs[0].compare("INSERT") == 0) {
        string table_name = strs[1];
        string index = strs[2];
        string name = strs[3];
        result = m_database.insert(table_name, index, name);
    } else if (strs[0].compare("TRUNCATE") == 0) {
        string table_name = strs[1];
        result = m_database.truncate(table_name);
    } else if (strs[0].compare("INTERSECTION") == 0) {
        result = m_database.intersection();
    } else if (strs[0].compare("SYMMETRIC_DIFFERENCE") == 0) {
        result = m_database.symmetric_difference();
    }

    return make_tuple(result, result ? "OK" : "Err " + strs[0]);
}
