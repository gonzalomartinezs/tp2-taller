#ifndef TESTING_H
#define TESTING_H

#include <string>
#include <iostream>

class Tester{
private:
    int exitos;
    int pruebas;

public:
    Tester();

    template <typename T> void compare (T expected, T obtained){
        if (expected == obtained){
            std::cout <<("\033[1;32mEXITO\033[0;0m\n");
            this->exitos++;
        } else {
            std::cout << "\033[1;31mFALLO: Se esperaba " << expected <<
                      " y se obtuvo " << obtained << "\033[0;0m\n";
        }
        this->pruebas++;
    };

    void summarize();

    void notifyError(int error_code);

    ~Tester();

};
#endif //TP1_TESTING_H
