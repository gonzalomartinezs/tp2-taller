#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include <string>

class Vertex{
private:
    std::list<std::string> adjacent;
    const std::string name;

public:
    // Crea un vértice listo para ser utilizado.
    explicit Vertex(std::string name):name(name){}

    // Agrega el vértice 'dest' a la lista de adyacentes.
    // Devuelve 0 en caso de éxito, y -1 en caso contrario.
    void addEdge(Vertex* dest);

    // Devuelve un booleano indicando si el vértice actual es adyacente a
    // 'vertex' o no.
    bool isAdjacentToVertex(const std::string& vertex);

    // Devuelve la lista de visited adyacentes.
    std::list<std::string> getAdjacent() const;

    // Devuelve el nombre del vértice.
    std::string getName() const;

    // Libera los recursos del vértice.
    ~Vertex(){}
};

#endif
