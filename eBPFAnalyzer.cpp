#include "eBPFAnalyzer.h"
#include <fstream>
#include <algorithm>
#include <utility>
#include <string>
#include <list>

#define SUCCESS 0
#define ERROR -1
#define HAS_CYCLES -1
#define UNUSED_INSTRUCTIONS -2
#define NONE std::string::npos
#define RETURN "ret"

int eBPFAnalyzer::parseAndModel(const std::string& file_path) {
    this->graph.clear();
    this->references.clear();
    std::ifstream file(file_path);
    if (!file) return ERROR;
    _modeleBPF(file);
    _addEdgesToGraph();
    file.close();
    return SUCCESS;
}

int eBPFAnalyzer::detectAnomalies() {
    int visited_vertices = this->graph.cycleDetectorDFS();
    if (visited_vertices == HAS_CYCLES){
        return HAS_CYCLES;
    } else if (visited_vertices != this->graph.getVerticesAmount()){
        return UNUSED_INSTRUCTIONS;
    }
    return SUCCESS;
}

// Modela las instrucciones del eBPF adaptandolo al formato de un grafo.
void eBPFAnalyzer::_modeleBPF(std::ifstream &file) {
    int line_number = 0;    // para instrucciones repetidas
    std::string line, previous_instr, instruction, operation;
    while (std::getline(file, line)){
        if (!line.empty()) {
                int beginning;
                size_t colon = line.find(':');
                if (colon == NONE) {    // no tiene etiqueta
                    beginning = 0;
                    _extractOperation(line, beginning, operation);
                    instruction = line.substr(line.find_first_not_of(' '))
                                    + " " + std::to_string(line_number);
                } else {
                    beginning = line.find_first_not_of(' ', colon + 1);
                    _extractOperation(line, beginning, operation);
                    instruction = line.substr(0, colon);
                }
                graph.addVertex(instruction);
                _assignReference(line, instruction, operation, previous_instr);
        }
        line_number++;
    }
}


// Extrae la operación a realizar (jmp, ret, ldh, ...) de la instrucción.
void eBPFAnalyzer::_extractOperation(const std::string& line, int beginning,
                                     std::string& operation) {
    int beginning_op = line.find_first_not_of(' ', beginning);
    int end_op = line.find(' ', beginning_op);
    operation = line.substr(beginning_op, end_op - beginning_op);
}



// Asigna a una instrucción la o las instrucciones que le siguen en la
// ejecución y agrega dicho/s par/es a 'references'.
void eBPFAnalyzer::_assignReference(std::string line,
                                    const std::string& instruction,
                                    const std::string& operation,
                                    std::string& previous_instr){
    if (!previous_instr.empty()) {
        (this->references).emplace_back(previous_instr, instruction);
    }
    if (operation == RETURN) {
        previous_instr = "";
    } else if (operation.find('j') == 0) {    // jump
        _parseJumps(line, instruction, previous_instr);
    } else {
        previous_instr = instruction;
    }
}



// Parsea y asigna las referencias correspondientes a cada tipo de salto.
void eBPFAnalyzer::_parseJumps(std::string line, const std::string& instruction,
                               std::string& previous_instr){
    int commas = std::count(line.begin(), line.end(), ',');
    std::string label = line.substr(line.rfind(' ') + 1);
    (this->references).emplace_back(instruction, label);
    if (commas == 0) {                      // salto incondicional
        previous_instr = "";
    } else if (commas == 1) {               // salto condicional 1 label
        previous_instr = instruction;
    } else {                                // salto condicional 2 labels
        int first_comma = line.find(',');
        int second_comma = line.find(',', first_comma+1);
        std::string second_label = line.substr(first_comma+2,
                                               second_comma-first_comma-2);
        (this->references).emplace_back(instruction, second_label);
        previous_instr = "";
    }
}


// Convierte todos los elementos de 'references' en aristas del grafo.
void eBPFAnalyzer::_addEdgesToGraph(){
    std::list<std::pair<std::string, std::string>>::iterator it;
    for (it = (this->references).begin(); it != (this->references).end(); ++it){
        graph.addEdge(it->first, it->second);
    }
}

