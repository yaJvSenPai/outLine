#ifndef __PAGELIB__
#define __PAGELIB__

#include <cppHead>

#include "dirScanner.hh"
#include "mySql4cpp.hh"
#include "parseRss.hh"


using namespace std;
using namespace Mysql4cpp;

class PageLib {
   public:
    void setDir(string path);
    void connectMysql(const string& host, const string& user,
                      const string& passwd, const string& db, unsigned int port,
                      const char* unix_socket, unsigned int client_flag);
    void buildLib();

   private:
    DirScanner _dir;
    RssReader _rss;
    Mysql _mysql;
    vector<string> _filename;
};

#endif