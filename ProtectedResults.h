#ifndef TP2_TALLER_PROTECTEDRESULTS_H
#define TP2_TALLER_PROTECTEDRESULTS_H

#include <mutex>
#include <map>
#include <string>

class ProtectedResults {
private:
    std::map<std::string,std::string> results;
    std::mutex m;

public:
    ProtectedResults() {}

    void addResult(std::string file, std::string result);

    void showResults();

    ~ProtectedResults(){}
};


#endif //TP2_TALLER_PROTECTEDRESULTS_H
