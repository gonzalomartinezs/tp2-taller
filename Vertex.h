#ifndef TP1_VERTEX_H
#define TP1_VERTEX_H

#include <list>
#include <string>

class Vertex{
private:
    std::list<std::string> *adjacent;
    const std::string name;

public:
    // Crea un vértice listo para ser utilizado.
    Vertex(std::string name):name(name),adjacent(new std::list<std::string>){};

    // Agrega el vértice 'dest' a la lista de adyacentes.
    // Devuelve 0 en caso de éxito, y -1 en caso contrario.
    void addEdge(Vertex* dest);

    // Devuelve un booleano indicando si el vértice actual es adyacente a
    // 'vertex' o no.
    bool isAdjacentToVertex(const std::string& vertex);

    // Devuelve la lista de visited adyacentes.
    std::list<std::string> getAdjacent();

    // Devuelve el nombre del vértice.
    std::string getName();

    // Libera los recursos del vértice.
    ~Vertex();
};


#endif //TP1_VERTEX_H
