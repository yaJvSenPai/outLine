#include "parseRss.hh"


void RssReader::star(string path) {
    _path = path;
    parseRss();
    clearString();
}

vector<RssItem> RssReader::getData()  {
    vector<RssItem> tmp;
    tmp.swap(_rss);
    return tmp;
}

void RssReader::parseRss() {
    XMLDocument doc;              // 创建一个xml对象
    doc.LoadFile(_path.c_str());  // 打开xml文件并读取分析

    XMLElement *root = doc.FirstChildElement("rss");  // 指定根节点为rss标签
    if (root == nullptr) {
        cout << "null root is rss" << endl;
        return;
    }

    XMLElement *channel = root->FirstChildElement("channel");  // 选择频道
    while (channel) {
        XMLElement *item = channel->FirstChildElement("item");  // 选择一个项目
        while (item) {
            XMLElement *title = item->FirstChildElement("title");  // 选择标题
            XMLElement *link = item->FirstChildElement("link");
            XMLElement *description = item->FirstChildElement("description");
            XMLElement *content = item->FirstChildElement("content:encoded");
            if(content == nullptr) {
                content = item->FirstChildElement("content");
            }
            RssItem tmp;
            if (title) {
                tmp.title = title->GetText();  // 标题指针非空则获取其内容
            }
            if (link) {
                tmp.link = link->GetText();
            }
            if (description) {
                tmp.description = description->GetText();
            }
            if (content) {
                tmp.content = content->GetText();
            }
            _rss.push_back(tmp);
            item = item->NextSiblingElement();  // 寻找下一个项目
        }

        channel = channel->NextSiblingElement();  // 寻找下一个频道
    }
}

void RssReader::clearString() {
    for (auto &rss : _rss) {
        rss.description = regex_replace(rss.description, regex("<[\\s\\S]*?>"),
                                        "");  // 清理标签
        rss.description = regex_replace(rss.description, regex("-->"), "");
        rss.description = regex_replace(rss.description, regex("&nbsp;"), "");

        rss.content = regex_replace(rss.content, regex("<[\\s\\S]*?>"), "");
        rss.content = regex_replace(rss.content, regex("-->"), "");
        rss.content = regex_replace(rss.content, regex("&nbsp;"), "");
    }
}