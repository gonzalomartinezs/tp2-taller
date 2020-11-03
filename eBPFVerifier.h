#ifndef TP2_TALLER_EBPFVERIFIER_H
#define TP2_TALLER_EBPFVERIFIER_H

#include "Thread.h"
#include "ProtectedFiles.h"
#include "ProtectedResults.h"
#include <list>

class eBPFVerifier {
private:
    ProtectedFiles files;
    ProtectedResults results;
    std::list<Thread*> threads;

public:
    // Crea un verificador de eBPF listo para ser utilizado.
    eBPFVerifier(int argc, char** argv);

    // Verifica los archivos introducidos por el usuario.
    void run();

    // Muestra por pantallas los resultados de la verificación de los archivos.
    void showResults();

    // Libera los recursos utilizados por el vefificador.
    ~eBPFVerifier();

    eBPFVerifier(const eBPFVerifier& other) = delete;
    eBPFVerifier& operator=(const eBPFVerifier&) = delete;
};


#endif //TP2_TALLER_EBPFVERIFIER_H
