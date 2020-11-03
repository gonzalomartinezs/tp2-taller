#ifndef GRAPHWALKER_H
#define GRAPHWALKER_H

#include <map>
#include <stack>
#include <list>
#include <string>
#include "Vertex.h"

class GraphWalker{
private:
    std::map<std::string,int> vertices_status;
    std::stack<Vertex> to_visit;
    void _initializeVisited(std::list<Vertex>& vertices);
    void _emptyToVisitStack();
    Vertex* _getVertex(std::list<Vertex>& vertices, const std::string& name)
                                                                        const;

public:
    // Crea un GraphWalker listo para ser utilizado.
    GraphWalker(){}

    // Realiza un recorrido DFS del grafo.
    // Retorna -1 si se encontró un ciclo y la cantidad de vértices visitados
    // en caso contrario.
    int detectCycleDFS(std::list<Vertex> vertices);

    // Libera los recursos del objeto.
    ~GraphWalker(){}
};

#endif
