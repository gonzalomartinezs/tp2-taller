#include <iostream>
#include "GraphWalker.h"

#define NOT_VISITED 0
#define IN_PROCESS 1
#define VISITED 2
#define CYCLE_FOUND -1

int GraphWalker::detectCycleDFS(std::list<Vertex> vertices) {
    int visited_vertices = 0;
    _initializeVisited(vertices);
    (this->to_visit).push(vertices.front());

    while(!((this->to_visit).empty())){
        Vertex current = (this->to_visit).top();
        if ((this->visited).at(current.getName()) != IN_PROCESS){
            (this->visited).at(current.getName()) = IN_PROCESS;
            std::list<std::string> adjacent = current.getAdjacent();
            std::list<std::string>::iterator it;
            for (it = adjacent.begin(); it != adjacent.end(); ++it){
                if((this->visited).at(*it) == NOT_VISITED){
                    (this->to_visit).push(*_getVertex(vertices,*it));
                } else if ((this->visited).at(*it) == IN_PROCESS){
                    (this->visited).clear();
                    _emptyToVisitStack();
                    return CYCLE_FOUND;
                }
            }
        } else {
            (this->to_visit).pop();
            (this->visited).at(current.getName()) = VISITED;
            visited_vertices++;
        }
    }
    return visited_vertices;
}

void GraphWalker::_initializeVisited(std::list<Vertex>& vertices){
    std::list<Vertex>::iterator it;
    for (it = vertices.begin(); it!=vertices.end(); ++it){
        (this->visited).insert({(*it).getName(), NOT_VISITED});
    }
}

void GraphWalker::_emptyToVisitStack() {
    while(!((this->to_visit).empty())){
        (this->to_visit).pop();
    }
}

Vertex* GraphWalker::_getVertex(std::list<Vertex> &vertices,
                                std::string name) {
    std::list<Vertex>::iterator it;
    for (it = vertices.begin(); it!=vertices.end(); ++it){
        if((*it).getName() == name){
            return &(*it);
        }
    }
    return nullptr;
}

GraphWalker::~GraphWalker() {
    //do nothing
}

