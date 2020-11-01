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

    // Devuelve true si la pila de archivos se encuentra vacía, false en
    // caso contrario.
    bool isEmpty();

    // Retorna el nombre del archivo que se encuentra en el topa de la pila,
    // desapilandolo.
    std::string getFile();

    // Libera los recursos utilizados por el monitor.
    ~ProtectedFiles();
};


#endif //TP2_TALLER_PROTECTEDFILES_H
