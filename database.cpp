#include "database.h"

#include <iostream>

using namespace std;

std::list<std::tuple<std::string, std::string>> Database::list_a;
std::list<std::tuple<std::string, std::string>> Database::list_b;

Database::Database()
{
    const char* db_name = "db.sqlite";
    m_handle = nullptr;

    if (sqlite3_open(db_name, &m_handle)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_handle) << std::endl;
        sqlite3_close(m_handle);
    }

    // TODO: проверить наличие файл, при отсутствии создать таблицы
    create_tables();
}


Database::~Database()
{
    if (m_handle) {
        sqlite3_close(m_handle);
    }
}


void Database::create_tables()
{
    const char* create_table_A =
"CREATE TABLE A "
    "("
    "   id INT NOT NULL, "
    "   name VARCHAR(32)NOT NULL"
    ");";
    const char* create_table_B =
"CREATE TABLE B "
    "("
    "   id INT NOT NULL,"
    "   name VARCHAR(32) NOT NULL"
    ");";

    execute_command(0, create_table_A);
    execute_command(0, create_table_B);
}

bool Database::insert(std::string table_name, std::string id, std::string name)
{
    string cmd = string("INSERT INTO " + table_name + " (id, name) " + "VALUES (" + id + ", " + "\'" + name + "\'" + ")");
    return execute_command(0, cmd);
}

bool Database::truncate(std::string table_name)
{
    string cmd = string("DELETE FROM " + table_name);
    return execute_command(0, cmd);
}

bool Database::intersection()
{
    string cmd = string("SELECT * FROM A JOIN B ON A.id=B.id WHERE (SELECT id FROM A INTERSECT SELECT id FROM B)");

    auto print_results = [](void *, int columns, char **data, char **names) -> int{
        std::cout << data[0] << "\t" << data[1] << "\t" << data[3] << std::endl;
        return 0;
    };

    std::cout << "id\tname\tname" << std::endl;
    return execute_command(print_results, cmd);
}

int Database::make_list_a(void *, int columns, char **data, char **names)
{
    cout << data[0] << "\t" << data[1] << endl;
    list_a.push_back(make_tuple(data[0], data[1]));

    return 0;
};

int Database::make_list_b(void *, int columns, char **data, char **names)
{
    cout << data[0] << "\t\t" << data[1] << endl;
    list_b.push_back(make_tuple(data[0], data[1]));

    return 0;
};

bool Database::symmetric_difference()
{
    list_a.clear();
    list_b.clear();

    std::cout << "id\tname\tname" << std::endl;
    string cmd0 = string("SELECT * FROM A WHERE A.id IN (SELECT id FROM A EXCEPT SELECT id FROM B)");
    string cmd1 = string("SELECT * FROM B WHERE B.id IN (SELECT id FROM B EXCEPT SELECT id FROM A)");
    bool result = execute_command(make_list_a, cmd0);
    result &= execute_command(make_list_b, cmd1);

    return result;
}

bool Database::execute_command(int(*handler)(void*, int columns, char **data, char **names), std::string cmd)
{
    char *errmsg;
    int rc = sqlite3_exec(m_handle, cmd.c_str(), handler, 0, &errmsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't execute query: " << errmsg << std::endl;
        sqlite3_free(errmsg);
        return false;
    }

    return true;
}
