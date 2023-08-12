#include "mySql4cpp.hh"

using namespace Mysql4cpp;
using namespace std;

Mysql::Mysql() {
    lock_guard<mutex> guard(_mutex);
    _mysql = mysql_init(nullptr);
}

Mysql::~Mysql() {
    lock_guard<mutex> guard(_mutex);
    mysql_close(_mysql);
}

bool Mysql::connect(const string& host, const string& user,
                    const string& passwd, const string& db, unsigned int port,
                    const char* unix_socket, unsigned int client_flag) {
    lock_guard<mutex> guard(_mutex);

    MYSQL* ret =
        mysql_real_connect(_mysql, host.c_str(), user.c_str(), passwd.c_str(),
                           db.c_str(), port, unix_socket, client_flag);
    if (ret == nullptr) {
        return false;
    } else {
        return true;
    }
}

bool Mysql::write(const string& mysqlQuery) {
    lock_guard<mutex> guard(_mutex);
    int query = mysql_query(_mysql, mysqlQuery.c_str());
    if (query != 0) {
        return false;
    } else {
        return true;
    }
}

pair<Result, bool> Mysql::read(const string& mysqlQuery) {
    lock_guard<mutex> guard(_mutex);
    Result result;  // 用于存储返回结果
    int query = mysql_query(_mysql, mysqlQuery.c_str());
    if (query != 0) {
        return {result, false};
    }
    MYSQL_RES* res = mysql_store_result(_mysql);

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        vector<string> tmp; // 用于存储一行的结果
        for (unsigned int i = 0; i < mysql_num_fields(res); ++i) {
            tmp.emplace_back(row[i]);
        }
        result.emplace_back(tmp);
    }
    mysql_free_result(res);

    return {result, true};
}

int Mysql::query(const string& mysqlQuery) {
    lock_guard<mutex> guard(_mutex);
    int query = mysql_query(_mysql, mysqlQuery.c_str());
    return query;
}

string Mysql::getError() {
    lock_guard<mutex> guard(_mutex);
    return string(mysql_error(_mysql));
}


string safeSql(MYSQL* mysql, string str) {
    int size = str.size();
    char tmp[2 * size + 1] = {0};
    mysql_real_escape_string(mysql, tmp, str.c_str(), size);
    str.clear();
    str = tmp;
    return str;
}