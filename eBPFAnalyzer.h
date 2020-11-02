#ifndef EBPFPARSER_H
#define EBPFPARSER_H

#include "Graph.h"
#include <map>
#include <utility>
#include <string>
#include <list>

class eBPFAnalyzer{
private:
    Graph graph;
    std::list<std::pair<std::string, std::string>> references;
    int _modeleBPF(std::ifstream& file);
    bool _hasRightFormat(std::string& line);
    void _extractOperation(const std::string& line, int beginning,
                           std::string& operation);
    void _assignReference(std::string line, const std::string& instruction,
                          const std::string& operation,
                          std::string& previous_instr);
    void _parseJumps(std::string line, const std::string& instruction,
                     std::string& previous_instr);
    void _addEdgesToGraph();

public:
    // Crea un eBPFAnalyzer listo para ser utilizado.
    eBPFAnalyzer() {}

    // Parsea las instrucciones del eBPF y lo modela como grafo.
    int parseAndModel(const std::string& file_path);

    // Detecta si hay anomalias en el archivo eBPF.
    // Retorna: 0 si no tiene errores.
    //         -1 si se detectaron ciclos.
    //         -2 si hay instrucciones sin utilizar.
    int detectAnomalies();

    // Libera los recursos utilizados por eBPFAnalyzer.
    ~eBPFAnalyzer();
};

#endif
