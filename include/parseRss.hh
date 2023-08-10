#ifndef __PARSERSS__
#define __PARSERSS__

#include <tinyxml2.h>

#include <cppHead>
#include <regex>

using namespace std;
using namespace tinyxml2;

typedef struct __RssItem {
    string title;
    string link;
    string description;
    string content;
} RssItem;

class RssReader {
   public:
    RssReader() {}
    void star(string path);
    vector<RssItem> getData();

   private:
    void parseRss();
    void clearString();

   private:
    string _path;
    vector<RssItem> _rss;
};

#endif