#include "testing.h"
#include "../Graph.h"

#define SUCCESS 0

void seAgreganVerticesAlGrafoCorrectamente(Tester& tester){
    Graph graph = Graph();
    graph.addVertex("Leo Mattioli");
    std::cout << "Agrego el vértice 'Leo Mattioli' y aparece dentro del grafo."
            << std::endl;
    tester.compare(true, graph.isVertexInGraph("Leo Mattioli"));
}

void seIntentaBuscarVerticeQueNoPerteneceAlGrafo(Tester& tester){
    Graph graph = Graph();
    graph.addVertex("Leo Mattioli");
    std::cout << "Agrego el vértice 'Leo Mattioli' y al buscar el vértice "
                 "'Los Charros', este no aparece." << std::endl;
    tester.compare(false, graph.isVertexInGraph("Los Charros"));
}

void seAgregaAristaCorrectamente(Tester& tester){
    Graph graph = Graph();
    graph.addVertex("Leo Mattioli");
    graph.addVertex("Karina");

    std::cout << "Agrego una arista dirigida que va del vértice 'Leo Mattioli' "
                 "al vértice 'Karina' correctamente." << std::endl;
    tester.compare(SUCCESS, graph.addEdge("Leo Mattioli", "Karina"));

    std::cout << "Ahora 'Karina' aparece adyacente a 'Leo Mattioli'." << std::endl;
    tester.compare(true, vertex1.isAdjacentToVertex((std::string)"Karina"));
}


int main(){
    Tester tester = Tester();
    seAgreganVerticesAlGrafoCorrectamente(tester);
    seIntentaBuscarVerticeQueNoPerteneceAlGrafo(tester);
    seAgregaAristaCorrectamente(tester);
    tester.summarize();
    return 0;
}