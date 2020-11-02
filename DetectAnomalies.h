#ifndef TP2_TALLER_DETECTANOMALIES_H
#define TP2_TALLER_DETECTANOMALIES_H

#include "Thread.h"
#include "eBPFAnalyzer.h"
#include "ProtectedFiles.h"
#include "ProtectedResults.h"

class DetectAnomalies: public Thread{
private:
    eBPFAnalyzer analyzer;
    ProtectedFiles& files;
    ProtectedResults& results;

public:
    // Crear el objeto, listo para ser utilizado.
    DetectAnomalies(ProtectedFiles& files, ProtectedResults& results):
                                            files(files), results(results){}

    // Analiza los archivos en 'files' y carga en 'results' un mensaje que
    // indica si el mismo se encuentra mal generado, contiene ciclos o
    // instrucciones sin utilizar, o si el archivo el correcto.
    virtual void run() override;

    // Destruye el objeto.
    ~DetectAnomalies() override{}
};

#endif //TP2_TALLER_DETECTANOMALIES_H
