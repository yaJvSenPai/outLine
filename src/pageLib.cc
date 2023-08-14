#include "pageLib.hh"

void PageLib::setDir(string path) {
    _path = path;
    _dir.traverse(path);
    _filename = _dir.getName();
}

// void PageLib::connectMysql(Mysql *mysql) {
//     _mysql = mysql;
// }

void PageLib::buildLib() {
    // int num = 1;
    // int no = 1;

    vector<RssItem> data;
    for (const auto& file : _filename) {
        _rss.star(_path + "/" + file);
        data = _rss.getData();

        for (const auto& rs : data) {
            if (rs.link.find("http") != string::npos) {
                string s =
                    "INSERT INTO webPage (url, title, description, content) "
                    "VALUES (";
                s += "\'" + rs.link + "\',";
                s += "\'" + safeSql(_mysql->getMysql(), rs.title) + "\',";
                s += "\'" + safeSql(_mysql->getMysql(), rs.description) + "\',";
                s += "\'" + safeSql(_mysql->getMysql(), rs.content) + "\')";
                if (!_mysql->write(s)) {
                    cout << file << " : " << rs.title << " : ";
                    cout << _mysql->getError() << endl;
                }  // else {
                   // cout << "real no " << no++ << " " << rs.title << endl;
                // }
            }
        }
        // cout << "-----------------------" << endl;
        // cout << num++ << " " << file + " done" << endl;
        // cout << "-----------------------" << endl;
    }
}