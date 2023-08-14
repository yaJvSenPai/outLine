#ifndef __CONFG__
#define __CONFG__

#include <cppHead>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

typedef struct _MysqlConf {
    string host;
    string user;
    string passwd;
    string database;
    unsigned int port = 0;
    char* unix_socket = nullptr;
    unsigned int client_flag = 0;
} MysqlConf;

class Confg {
   public:
    Confg(string path) : _path(path) {
        ifstream confile;
        confile.open(_path);
        if(!confile.is_open()) {
            cerr << "open confg fail" << endl;
            exit(1);
        }
        _confg = json::parse(confile);
        if(_confg.find("mysql") == _confg.end()) {
            cerr << "can't find mysql confg" << endl;
        } else {
            _mysqlconf.host = _confg["mysql"]["host"];
            _mysqlconf.user = _confg["mysql"]["user"];
            _mysqlconf.passwd = _confg["mysql"]["passwd"];
            _mysqlconf.database = _confg["mysql"]["database"];
            if(_confg["mysql"].find("port") != _confg["mysql"].end()) {
                _mysqlconf.port = _confg["mysql"]["port"];
            }
            if(_confg["mysql"].find("unix_socket") != _confg["mysql"].end()) {
                string tmp = _confg["mysql"]["unix_socket"];
                _mysqlconf.unix_socket = const_cast<char *>(tmp.c_str());
            }
            if(_confg["mysql"].find("client_flag") != _confg["mysql"].end()) {
                _mysqlconf.client_flag = _confg["mysql"]["client_flag"];
            }
            _dataPath = _confg["dataPath"];
        }
        confile.close();
    }

    string dataPath() {
        return _dataPath;
    }

    MysqlConf mysqlConf() {
        return _mysqlconf;
    }

   private:
    string _path;
    string _dataPath;
    json _confg;
    MysqlConf _mysqlconf;
};

#endif