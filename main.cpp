#include "eBPFVerifier.h"

int main(int argc, char* argv[]){
    eBPFVerifier verifier(argc, argv);
    verifier.run();
    verifier.showResults();
    return 0;
}
