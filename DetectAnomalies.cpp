#include "DetectAnomalies.h"
#include <string>

#define ERROR -1
#define HAS_CYCLES -1
#define UNUSED_INSTRUCTIONS -2

void DetectAnomalies::run() {
    std::string file;
    while (!(file = this->files.getFile()).empty()){
        if (this->analyzer.parseAndModel(file) == ERROR){
            this->results.addResult(file, "FAIL: Bad file");
        } else {
            int result = this->analyzer.detectAnomalies();
            if (result == HAS_CYCLES){
                this->results.addResult(file, "FAIL: cycle detected");
            } else if (result == UNUSED_INSTRUCTIONS){
                this->results.addResult(file, "FAIL: unused instructions"
                                                    " detected");
            } else {
                this->results.addResult(file, "GOOD");
            }
        }
    }
}
