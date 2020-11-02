#ifndef GRAPHWALKER_H
#define GRAPHWALKER_H

#include <map>
#include <stack>
#include <list>
#include <string>
#include "Vertex.h"

class GraphWalker{
private:
    std::map<std::string,int> visited;
    std::stack<Vertex> to_visit;
    void _initializeVisited(std::list<Vertex>& vertices);
    void _emptyToVisitStack();
    Vertex* _getVertex(std::list<Vertex>& vertices, const std::string& name);

public:
    GraphWalker():visited(),to_visit(){}

    // Realiza un recorrido DFS del grafo.
    // Retorna -1 si se encontró un ciclo y la cantidad de vértices visitados
    // en caso contrario.
    int detectCycleDFS(std::list<Vertex> vertices);

    ~GraphWalker();
};

#endif
