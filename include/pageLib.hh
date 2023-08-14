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
   PageLib(Mysql *mysql) : _mysql(mysql) {}
    void setDir(string path);
    // void connectMysql(Mysql *mysql);
    void buildLib();

   private:
    DirScanner _dir;
    RssReader _rss;
    Mysql* _mysql;
    vector<string> _filename;
    string _path;
};

#endif