#include "testing.h"
#include <iomanip>

Tester::Tester(){
    this->exitos = 0;
    this->pruebas = 0;
}

void Tester::summarize() {
    if(this->pruebas>0){
        std::cout << "\nSe obtuvieron " << this->exitos << " éxitos en " <<
                  this->pruebas << " pruebas ( " << std::fixed <<
                  std::setprecision(2) << (this->exitos/this->pruebas)*100
                  << "% ).\n";
    } else {
        std::cout << "No se realizaron pruebas" << std::endl;
    }

}

void Tester::notifyError(int error_code) {
    std::cout <<"\033[1;31mCODIGO DE ERROR: " << error_code << ".\033[0;0m\n";
}

Tester::~Tester(){
    //do nothing
}

