#ifndef __PAGELIBPRE__
#define __PAGELIBPRE__

#include <cppHead>

#include "mySql4cpp.hh"

using namespace std;
using namespace Mysql4cpp;

class PageLibPre {
   public:
    PageLibPre(Mysql *mysql) : _mysql(mysql) {}
    void rmDuplicate();
    void mkInverted();

   private:
    void preInverted();
    void setWeight();
    void normalization();
    Mysql* _mysql;
};

#endif