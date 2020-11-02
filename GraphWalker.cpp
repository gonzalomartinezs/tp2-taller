#include "GraphWalker.h"
#include <string>
#include <list>

#define NOT_VISITED 0
#define IN_PROCESS 1
#define VISITED 2
#define CYCLE_FOUND -1

int GraphWalker::detectCycleDFS(std::list<Vertex> vertices) {
    int visited_vertices = 0;
    _initializeVisited(vertices);
    (this->to_visit).push(vertices.front());

    while (!((this->to_visit).empty())){
        Vertex current = (this->to_visit).top();
        if ((this->vertices_status).at(current.getName()) == NOT_VISITED){
            (this->vertices_status).at(current.getName()) = IN_PROCESS;
            std::list<std::string> adjacent = current.getAdjacent();
            std::list<std::string>::iterator it;
            for (it = adjacent.begin(); it != adjacent.end(); ++it){
                if ((this->vertices_status).at(*it) == NOT_VISITED){
                    (this->to_visit).push(*_getVertex(vertices,*it));
                } else if ((this->vertices_status).at(*it) == IN_PROCESS){
                    (this->vertices_status).clear();
                    _emptyToVisitStack();
                    return CYCLE_FOUND;
                }
            }
        } else {
            (this->to_visit).pop();
            if ((this->vertices_status).at(current.getName()) == IN_PROCESS) {
                (this->vertices_status).at(current.getName()) = VISITED;
                visited_vertices++;
            }
        }
    }
    return visited_vertices;
}

// Inicializa el map de status de los vértices, marcándolos como no visitados.
void GraphWalker::_initializeVisited(std::list<Vertex>& vertices){
    std::list<Vertex>::iterator it;
    for (it = vertices.begin(); it!=vertices.end(); ++it){
        (this->vertices_status).insert({(*it).getName(), NOT_VISITED});
    }
}

// Vacía la pila de vértices a visitar.
void GraphWalker::_emptyToVisitStack() {
    while (!((this->to_visit).empty())){
        (this->to_visit).pop();
    }
}

// Retorna el vértice correspondiente al nombre recibido.
Vertex* GraphWalker::_getVertex(std::list<Vertex> &vertices,
                                const std::string& name) {
    std::list<Vertex>::iterator it;
    for (it = vertices.begin(); it!=vertices.end(); ++it){
        if ((*it).getName() == name){
            return &(*it);
        }
    }
    return nullptr;
}

