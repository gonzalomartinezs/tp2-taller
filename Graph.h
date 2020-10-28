#ifndef TP1_GRAFO_H
#define TP1_GRAFO_H

#include <list>
#include <string>
#include "Vertex.h"

class Graph {
private:
    std::list <Vertex*> *vertices;
    Vertex* _getVertex(const std::string&);

public:
    // Crea un grafo listo para ser utilizado.
    Graph():vertices(new std::list<Vertex*>){};

    // Agrega un vértice al grafo.
    void addVertex(Vertex *vertex);

    // Agrega una arista al grafo para conectar 2 vértices ya existentes.
    // Retorna 0 en caso de éxito y -1 si surgió un error.
    int addEdge(const std::string& origin, const std::string& dest);

    // Devuelve un booleano indicando si el vértice requerido se encuentra en
    // el grafo o no.
    bool isVertexInGraph(const std::string& vertex);

    int cycleDetectorDFS();

    // Libera los recursos del grafo.
    ~Graph();
};

#endif //TP1_GRAFO_H
