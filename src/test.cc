#include <cppHead>

#include "pageLib.hh"
#include "pageLibPre.hh"

using namespace std;
using namespace Mysql4cpp;

int main() {
    Mysql mysql;
    bool ret =
        mysql.connect("localhost", "root", "123", "webData", 0, nullptr, 0);
    if (!ret) {
        cout << "link fail" << endl;
    }

    PageLib build(&mysql);
    build.setDir("../data/corpus");
    cout << "----------------------------------" << endl;
    cout << "set dir ok" << endl;
    build.buildLib();
    cout << "----------------------------------" << endl;
    cout << "build lib ok" << endl;

    PageLibPre pagePre(&mysql);
    pagePre.rmDuplicate();
    cout << "----------------------------------" << endl;
    cout << "rmDuplicate ok" << endl;
    pagePre.mkInverted();
    cout << "----------------------------------" << endl;
    cout << "mkInverted ok" << endl;


    return 0;
}

// int main() {
// PageLib build;
// build.setDir("../data/corpus");
// build.connectMysql("localhost", "root", "123", "webData", 0, nullptr, 0);
// build.buildLib();

// cout << "sql ok" << endl;

// 去重
// Mysql mysql;
// mysql.connect("localhost", "root", "123", "webData", 0, nullptr, 0);
// Result res = mysql.read("SELECT * FROM webPage").first;

// Simhasher simhasher("../data/dict/jieba.dict.utf8",
//                     "../data/dict/hmm_model.utf8",
//                     "../data/dict/idf.utf8",
//                     "../data/dict/stop_words.utf8");

// int maxSize = res.size();
// set<string> willDec;
// vector<uint64_t> us;
// for (int i = 0; i < maxSize; ++i) {
//     string s1 = res[i][2] + res[i][3] + res[i][4];
//     size_t topN1 = 1000;
//     uint64_t u1 = 0;
//     vector<pair<string, double> > results1;
//     simhasher.extract(s1, results1, topN1);
//     simhasher.make(s1, topN1, u1);
//     us.push_back(u1);
// }
// cout << "hash done" << endl;

// for (int i = 0; i < maxSize - 1; ++i) {
//     for (int j = i + 1; j < maxSize; ++j) {
//         if (Simhasher::isEqual(us[i], us[j])) {
//             if (res[i][2] == res[j][2]) {
//                 willDec.insert(res[j][0]);
//                 cout << res[i][0] << " : " << res[j][0]
//                      << endl;  // 调试，输出重发文章的id
//             }
//         }
//     }
// }
// cout << willDec.size() << endl;

// while (willDec.size()) {
//     string decSql =
//         "DELETE FROM webPage WHERE docId = " + *(willDec.begin());
//     willDec.erase(willDec.begin());
//     int ret = mysql.query(decSql);
//     if (ret != 0) {
//         cout << mysql.getError() << endl;
//     }
// } //去重over

// 建立没有权重额倒排索引
// Mysql mysql;
// mysql.connect("localhost", "root", "123", "webData", 0, nullptr, 0);
// Result res = mysql.read("SELECT * FROM webPage").first;

// Jieba cutor("../data/dict/jieba.dict.utf8",
// "../data/dict/hmm_model.utf8",
//             "");
// vector<string> participle;
// map<string, int> writeBack;

// ifstream stop("../data/dict/stop_words.utf8");
// set<string> stopWord;
// string buf;
// while (getline(stop, buf)) {
//     stopWord.insert(buf);
// }
// stop.close();

// int docSize = res.size();
// for (int i = 0; i < docSize; ++i) {
//     string docId = res[i][0];
//     string content = res[i][2] + res[i][3] + res[i][4];

// cutor.CutForSearch(content, participle);
// for (auto it = participle.begin(); it != participle.end(); ++it) {
//     if (stopWord.find(*it) != stopWord.end() || iscntrl((*it)[0])) {
//         continue;
//     } else {
//         if(writeBack.find(*it) != writeBack.end()) {
//             writeBack[*it]++;
//         } else {
//             writeBack.insert(make_pair(*it, 1));
//         }
//     }
// }

//     while(writeBack.size()) {
//         string write = "INSERT INTO invertedList (word, docId, frequency)
//         VALUES ("; write += "\'" + (*writeBack.begin()).first + "\',"; write
//         += docId + ","; write += to_string((*writeBack.begin()).second) +
//         ")"; writeBack.erase(writeBack.begin()); if(!mysql.write(write)) {
//             cout << mysql.getError() << endl;
//         }
//     }

//     participle.clear();
// } // 建立没有权重额倒排索引end

//     Mysql mysql;
//     mysql.connect("localhost", "root", "123", "webData", 0, nullptr, 0);
//     Result res = mysql.read("SELECT word,docId,frequency FROM
//     invertedList").first;

//     Result allPage = mysql.read("SELECT COUNT(docId) FROM webPage").first;
//     int N = atoi(allPage[0][0].c_str());

//     int invertedSize = res.size();
//     for(int i = 0; i < invertedSize; ++i) {
//         int nf = atoi(res[i][2].c_str());

//         string findDf = "SELECT COUNT(wId) FROM invertedList WHERE word = ";
//         findDf += "\'" + res[i][0] + "\'";
//         Result getDf = mysql.read(findDf).first;
//         int df = atoi(getDf[0][0].c_str());
//         double weight = log2((double)(N+1)/(double)(df+1)) * (double)nf;

//         string setWg = "UPDATE invertedList SET weight = ";
//         setWg += to_string(weight);
//         setWg += " WHERE word = ";
//         setWg += "\'" + res[i][0] + "\'";
//         setWg += " AND docId = ";
//         setWg += "\'" + res[i][1] + "\'";
//         mysql.write(setWg);

//     }
//     return 0;
// }
