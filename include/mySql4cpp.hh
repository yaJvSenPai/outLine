#ifndef __MYSQL4CPP__
#define __MYSQL4CPP__

#include <mysql/mysql.h>

#include <iostream>
#include <mutex>
#include <string>
#include <vector>

using std::mutex;
using std::pair;
using std::string;
using std::vector;

namespace Mysql4cpp {

using Result = vector<vector<string>>;  // 用于存储查询结果

class Mysql {
   public:
    Mysql();
    ~Mysql();
    bool connect(const string& host, const string& user, const string& passwd,
                 const string& db, unsigned int port, const char* unix_socket,
                 unsigned int client_flag);  // 连接，失败会返回false

    bool write(const string& mysqlQuery);  // 仅用于写语句。写入失败会设置错误码

    pair<Result, bool> read(const string& mysqlQuery, int lines);  // 仅用于查询语句，失败时设置错误码

    int query(const string& mysqlQuery);  // 可任意的mysql请求，返回值非0则是请求失败，设置错误码

    string getError();  // 当有错误码产生时，获取错误信息

    MYSQL* getMysql() { return _mysql; }

   private:
    MYSQL* _mysql;
    mutex _mutex;  // 为了实现线程安全，加锁
};

};  // end of namespace Mysql4cpp

string safeSql(MYSQL* mysql, string str);

#endif