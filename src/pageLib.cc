#include "pageLib.hh"

void PageLib::setDir(string path) {
    _dir.traverse(path);
    _filename = _dir.getName();
}

void PageLib::connectMysql(const string& host, const string& user,
                           const string& passwd, const string& db,
                           unsigned int port, const char* unix_socket,
                           unsigned int client_flag) {
    bool ret = _mysql.connect(host, user, passwd, db, port, unix_socket, client_flag);
    if(!ret) {
        _mysql.getError();
    }
}

void PageLib::buildLib() {
    // int num = 1;
    // int no = 1;

    vector<RssItem> data;
    for (const auto& file : _filename) {
        _rss.star("../data/corpus/" + file);
        data = _rss.getData();

        for (const auto& rs : data) {
            if (rs.link.find("http") != string::npos) {
                string s =
                    "INSERT INTO webPage (url, title, description, content) "
                    "VALUES (";
                s += "\'" + rs.link + "\',";
                s += "\'" + safeSql(_mysql.getMysql(), rs.title) + "\',";
                s += "\'" + safeSql(_mysql.getMysql(), rs.description) + "\',";
                s += "\'" + safeSql(_mysql.getMysql(), rs.content) + "\')";
                if (!_mysql.write(s)) {
                    cout << file << " : " << rs.title << " : ";
                    cout << _mysql.getError() << endl;
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