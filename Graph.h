#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <string>
#include "Vertex.h"

class Graph {
private:
    std::list <Vertex> vertices;
    Vertex* _getVertex(const std::string&);

public:
    // Crea un grafo listo para ser utilizado.
    Graph(){}

    // Agrega un vértice al grafo.
    void addVertex(std::string name);

    // Agrega una arista al grafo para conectar 2 vértices ya existentes.
    // Retorna 0 en caso de éxito y -1 si surgió un error.
    int addEdge(const std::string& origin, const std::string& dest);

    // Devuelve un booleano indicando si el vértice requerido se encuentra en
    // el grafo o no.
    bool isVertexInGraph(const std::string& vertex);

    // Realiza un recorrido DFS del grafo.
    // Retorna -1 si se encontró un ciclo y la cantidad de vértices visitados
    // en caso contrario.
    int cycleDetectorDFS() const;

    // Vacia el grafo.
    void clear();

    // Retorna la cantidad de vértices del grafo.
    int getVerticesAmount() const;

    // Libera los recursos del grafo.
    ~Graph(){}
};

#endif
