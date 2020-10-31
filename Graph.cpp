#include <iostream>
#include "Graph.h"
#include "GraphWalker.h"

#define SUCCESS 0
#define ERROR -1

void Graph::addVertex(std::string name){
    if (!isVertexInGraph(name)){
        Vertex vertex = Vertex(name);
        (this->vertices).push_back(vertex);
    }
}

int Graph::addEdge(const std::string& origin, const std::string& dest) {
    Vertex* origin_vertex = _getVertex(origin);
    Vertex* dest_vertex = _getVertex(dest);
    if (origin_vertex && dest_vertex){
        if (!(origin_vertex->isAdjacentToVertex(dest_vertex->getName()))) {
            origin_vertex->addEdge(dest_vertex);
        }
        return SUCCESS;
    }
    return ERROR;
}

bool Graph::isVertexInGraph(const std::string& vertex){
    bool found = false;
    std::list<Vertex>::iterator it;
    for (it = (this->vertices).begin(); it!=(this->vertices).end() && !found;
            ++it){
        found = (((*it).getName()) == vertex);
    }
    return found;
}

Vertex* Graph::_getVertex(const std::string& vertex){
    Vertex* searched_vertex = nullptr;
    bool found = false;
    std::list<Vertex>::iterator it;
    for (it = (this->vertices).begin(); it!=(this->vertices).end() && !found;
         ++it){
        found = ((*it).getName() == vertex);
        if(found){
            searched_vertex = &(*it);
        }
    }
    return searched_vertex;
}

int Graph::cycleDetectorDFS() {
    GraphWalker walker = GraphWalker();
    return walker.detectCycleDFS((this->vertices));
}

void Graph::showAdjacencies() {
    std::list<Vertex>::iterator it;
    std::list<std::string>::iterator adj;
    for (it = (this->vertices).begin(); it != (this->vertices).end(); ++it){
        std::cout << (*it).getName() << " -> ";
        std::list<std::string> adjacent = (*it).getAdjacent();
        for (adj = adjacent.begin(); adj != adjacent.end(); ++adj){
                std::cout << "(" << (*adj) << ") - ";
        }
        std::cout << "." << std::endl;
    }
}


Graph::~Graph(){
    //do nothing
}


