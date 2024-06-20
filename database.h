#ifndef DATABASE_H
#define DATABASE_H

#include <list>
#include <tuple>
#include <map>
#include <string>

#include <sqlite3.h>

class Database
{
public:
    Database();
    ~Database();
    bool insert(std::string table_name, std::string id, std::string name);
    bool truncate(std::string table_name);
    bool intersection();
    bool symmetric_difference();

private:
    void create_tables();
    static int make_list_a(void *, int columns, char **data, char **names);
    static int make_list_b(void *, int columns, char **data, char **names);
    bool execute_command(int (*handler)(void *, int, char **, char **), std::string cmd);
    sqlite3* m_handle;
    static std::list<std::tuple<std::string, std::string>> list_a;
    static std::list<std::tuple<std::string, std::string>> list_b;
};

#endif // DATABASE_H
