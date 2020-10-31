#include "testing.h"
#include "../Graph.h"

void seRecorreGrafoCorrectamenteA(Tester& tester){
    Graph graph = Graph();

    graph.addVertex("A");
    graph.addVertex("B");

    graph.addEdge("A","B");
    graph.addEdge("A","C");

    std::cout << "Se recorre grafo de 2 vértices y una arista correctamente"
                 " (A->B)." << std::endl;

    graph.showAdjacencies();

    tester.compare(2,graph.cycleDetectorDFS());
}

void seRecorreGrafoCorrectamenteB(Tester& tester){
    Graph graph = Graph();

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");

    graph.addEdge("A","B");
    graph.addEdge("A","C");
    graph.addEdge("B","D");
    graph.addEdge("C","D");

    std::cout << "Al hacer DFS en un grafo sin vértices/instrucciones no "
                 "accedidas, recorro los 4 vértices." << std::endl;

    graph.showAdjacencies();

    tester.compare(4,graph.cycleDetectorDFS());
}

void seRecorreGrafoCorrectamenteC(Tester& tester){
    Graph graph = Graph();

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");

    graph.addEdge("A","C");
    graph.addEdge("B","C");
    graph.addEdge("C","D");

    std::cout << "Al hacer DFS en un grafo con un vértice/instrucción no "
                 "accedidas, recorro 3 de los 4 vértices." << std::endl;

    graph.showAdjacencies();

    tester.compare(3,graph.cycleDetectorDFS());
}

void seDetectaCicloCorrectamente(Tester& tester){
    Graph graph = Graph();

    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");

    graph.addEdge("A","B");
    graph.addEdge("B","C");
    graph.addEdge("C","A");
    graph.addEdge("C","D");

    std::cout << "Al hacer DFS en un grafo con un ciclo, este es detectado."
            << std::endl;

    graph.showAdjacencies();

    tester.compare(-1,graph.cycleDetectorDFS());
}


int main(){
    Tester tester = Tester();
    seRecorreGrafoCorrectamenteA(tester);
    seRecorreGrafoCorrectamenteB(tester);
    seRecorreGrafoCorrectamenteC(tester);
    seDetectaCicloCorrectamente(tester);
    tester.summarize();
    return 0;
}