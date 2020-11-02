#include "Vertex.h"
#include <string>
#include <list>

void Vertex::addEdge(Vertex *dest) {
    if (!isAdjacentToVertex(dest->getName())){
        (this->adjacent).push_back(dest->getName());
    }
}

bool Vertex::isAdjacentToVertex(const std::string& vertex) {
    bool found = false;
    std::list<std::string>::iterator it;
    for (it = (this->adjacent).begin(); it!=(this->adjacent).end() && !found;
         ++it){
        found = (*it == vertex);
    }
    return found;
}

std::list<std::string> Vertex::getAdjacent() {
    return (this->adjacent);
}

std::string Vertex::getName() {
    return this->name;
}

Vertex::~Vertex() {
    //do nothing
}
