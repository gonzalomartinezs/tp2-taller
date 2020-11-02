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
    // Crea una instancia del objeto lista para ser utilizada.
    ProtectedResults(){}

    // Agrega el resultado asociado a 'file' al map 'results'.
    void addResult(const std::string& file, const std::string& result);

    // Muestra por pantalla todos los archivos y sus respectivos resultados.
    void showResults();

    // Libera los recursos utilizados por el objeto.
    ~ProtectedResults(){}
};


#endif //TP2_TALLER_PROTECTEDRESULTS_H
