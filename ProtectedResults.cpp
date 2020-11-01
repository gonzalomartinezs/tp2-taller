#include "ProtectedResults.h"
#include "Lock.h"
#include <iostream>

void ProtectedResults::addResult(std::string file, std::string result) {
    Lock lock(this->m);
    this->results.insert({file, result});
}

void ProtectedResults::showResults() {
    Lock lock(this->m);
    std::map<std::string, std::string>::iterator it;
    for (it = (this->results).begin(); it != (this->results).end(); ++it){
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }
}
