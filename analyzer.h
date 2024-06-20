#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include <stack>

#include "database.h"

class Analyzer
{
public:
    explicit Analyzer();
    ~Analyzer();
    std::tuple<bool, std::string> analize(std::string line);

private:
    std::string m_line;
    std::vector<std::string> m_commands;
    std::stack<bool> m_dynamic_validator;
    Database m_database;
};

#endif // ANALYZER_H
