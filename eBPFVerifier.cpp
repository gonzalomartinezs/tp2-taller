#include "eBPFVerifier.h"
#include "DetectAnomalies.h"

eBPFVerifier::eBPFVerifier(int argc, char **argv):files(argc,argv) {
    for (int i = 0; i < atoi(argv[1]); i++){
        this->threads.push_back(new DetectAnomalies
                                    (this->files, this->results));
    }
}

void eBPFVerifier::run() {
    std::list<Thread*>::iterator it;
    for (it = this->threads.begin(); it != this->threads.end(); ++it){
        (*it)->start();
    }
    for (it = this->threads.begin(); it != this->threads.end(); ++it){
        (*it)->join();
    }
}

void eBPFVerifier::showResults() {
    this->results.showResults();
}

eBPFVerifier::~eBPFVerifier() {
    std::list<Thread*>::iterator it;
    for (it = threads.begin(); it != threads.end(); ++it){
        delete (*it);
    }
}





