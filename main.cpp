#include "Thread.h"
#include "ProtectedFiles.h"
#include "ProtectedResults.h"
#include "DetectAnomalies.h"
#include <list>

int main(int argc, char* argv[]){
    ProtectedFiles files(argc, argv);
    ProtectedResults results;
    std::list<Thread*> threads;

    for (int i = 0; i < atoi(argv[1]); i++){
        threads.push_back(new DetectAnomalies(files, results, i));
    }

    std::list<Thread*>::iterator it;
    for (it = threads.begin(); it != threads.end(); ++it){
        (*it)->start();
    }

    for (it = threads.begin(); it != threads.end(); ++it){
        (*it)->join();
        delete (*it);
    }

    results.showResults();
    return 0;
}
