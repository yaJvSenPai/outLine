#ifndef __DIRSCANNER__
#define __DIRSCANNER__

#include <func.h>

#include <cppHead>

using namespace std;

class DirScanner {
   public:
    DirScanner() {}
    ~DirScanner() {}
    void traverse(string dirName) {
        DIR* dir = opendir(dirName.c_str());
        ERROR_CHECK(dir, nullptr, "opendir");
        struct dirent* file;
        while ((file = readdir(dir))) {
            if (file->d_name[0] == '.') {
                continue;
            } else if (file->d_type == DT_DIR) {
                traverse(dirName + "/" + file->d_name);
            } else if (file->d_type == DT_REG) {
                _fileName.emplace_back(file->d_name);
            }
        }
        closedir(dir);
    }
    vector<string> getName() { return _fileName; }

   private:
    vector<string> _fileName;
};


#endif