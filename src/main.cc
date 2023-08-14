#include <cppHead>

#include "confg.hh"
#include "pageLib.hh"
#include "pageLibPre.hh"

using namespace std;
using namespace Mysql4cpp;

int main() {
    Confg cf("/home/monster/outLine/confg/conf.json");
    MysqlConf mysqlConf = cf.mysqlConf();

    Mysql mysql;
    bool ret = mysql.connect(mysqlConf.host, mysqlConf.user, mysqlConf.passwd,
                             mysqlConf.database, mysqlConf.port,
                             mysqlConf.unix_socket, mysqlConf.client_flag);
    if (!ret) {
        cout << "link mysql fail" << endl;
    }

    PageLib build(&mysql);
    build.setDir(cf.dataPath());
    build.buildLib();

    PageLibPre pagePre(&mysql);
    pagePre.rmDuplicate();
    pagePre.mkInverted();

    return 0;
}
