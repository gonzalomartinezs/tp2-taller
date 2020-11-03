#ifndef TP2_TALLER_PROTECTEDFILES_H
#define TP2_TALLER_PROTECTEDFILES_H

#include <stack>
#include <string>
#include <mutex>

class ProtectedFiles {
private:
    std::stack<std::string> files;
    std::mutex m;

public:
    // Deja el monitor listo para ser utilizado.
    ProtectedFiles(int argc, char**argv);

    // Retorna el nombre del archivo que se encuentra en el tope de la pila,
    // desapilandolo, o un string vacío si la pila se encuentra vacía.
    std::string getFile();

    // Libera los recursos utilizados por el monitor.
    ~ProtectedFiles(){}
};


#endif //TP2_TALLER_PROTECTEDFILES_H
