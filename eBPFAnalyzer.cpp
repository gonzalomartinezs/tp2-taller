#include "eBPFAnalyzer.h"
#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#define SUCCESS 0
#define ERROR -1
#define HAS_CYCLES -1
#define UNUSED_INSTRUCTIONS -2
#define NONE std::string::npos
#define RETURN "ret"

int eBPFAnalyzer::parseAndModel(const std::string& file_path) {
    this->graph.clear();
    bool succeeded = false;
    std::ifstream file(file_path);
    if (!file) return ERROR;
    if (_modeleBPF(file) == SUCCESS){
        _addEdgesToGraph();
        succeeded = true;
    }
    this->references.clear();
    file.close();
    return succeeded? SUCCESS : ERROR;
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


eBPFAnalyzer::~eBPFAnalyzer() {
    //do nothing;
}


int eBPFAnalyzer::_modeleBPF(std::ifstream &file) {
    std::string line, previous_instr, instruction, operation;
    while(std::getline(file, line)){
        if (!line.empty()) {
            if (_hasRightFormat(line)){
                int beginning;
                size_t colon = line.find(':');
                if (colon == NONE) {    // no tiene etiqueta
                    beginning = 0;
                    _extractOperation(line, beginning, operation);
                    instruction = line.substr(line.find_first_not_of(' '));
                } else {
                    beginning = line.find_first_not_of(' ', colon + 1);
                    _extractOperation(line, beginning, operation);
                    instruction = line.substr(0, colon);
                }
                graph.addVertex(instruction);
                _assignReference(line, instruction, operation, previous_instr);
            } else return ERROR;
        }
    }
    return SUCCESS;
}

// Verifica si el formato de la instrucción es correcto.
bool eBPFAnalyzer::_hasRightFormat(std::string &line) {
    size_t first_space = (line.find(' '));
    size_t colon = line.find(':');
    if (first_space == NONE) return false;
    if (colon == NONE) {
        if (first_space > line.find_first_not_of(' ')) return false;
    } else if (first_space < colon || line[colon+1] != ' ') return false;
    size_t commas = std::count(line.begin(), line.end(), ',');
    size_t commas_and_spaces = 0;
    size_t pos = line.find(", ");
    while (pos != NONE) {
        commas_and_spaces++;
        pos += 2;
        pos = line.find(", ", pos);
    }
    if (commas != commas_and_spaces) return false;
    return true;
}



// Extrae la operación a realizar (jmp, ret, ldh, ...) de la instrucción.
void eBPFAnalyzer::_extractOperation(const std::string& line, int beginning,
                                     std::string& operation){
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
    for(it = (this->references).begin(); it != (this->references).end(); ++it){
        graph.addEdge(it->first, it->second);
    }
}

