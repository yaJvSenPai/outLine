#include <cppHead>

#include "pageLib.hh"

using namespace std;
using namespace Mysql4cpp;

int main() {
    // PageLib build;
    // build.setDir("../data/corpus");
    // build.connectMysql("localhost", "root", "123", "webData", 0, nullptr, 0);
    // build.buildLib();
    Mysql mysql;
    mysql.connect("localhost", "root", "123", "webData", 0, nullptr, 0);
    Result res = mysql.read("SELECT * FROM webPage", 5000).first;
    cout << res.size() << endl;
    
    return 0;
}

