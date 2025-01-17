#include "ProtectedFiles.h"
#include "Lock.h"
#include <string>

ProtectedFiles::ProtectedFiles(int argc, char **argv) {
    for (int i=2; i<argc; i++){
        this->files.push(std::string(argv[i]));
    }
}

std::string ProtectedFiles::getFile() {
    Lock lock(this->m);
    std::string file;
    if (!(this->files.empty())){
        file = this->files.top();
        this->files.pop();
    }
    return file;
}

