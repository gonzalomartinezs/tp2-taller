#include "testing.h"
#include "../Vertex.h"

void verticeSeInicializaCorrectamente(Tester& tester){
    std::string name = "Mabel";
    Vertex vertex = Vertex(name);
    std::cout << "Se inicializa vértice con nombre 'Mabel' correctamente.\n";
    tester.compare(name, vertex.getName());
    std::cout << "Se inicializa vértice con lista de adyacentes vacía.\n";
    tester.compare((size_t)0, vertex.getAdjacent().size());
}

void seAgregaAdyacenteCorrectamente(Tester& tester){
    Vertex vertex1 = Vertex("Mabel");
    Vertex vertex2 = Vertex("Duraznito");
    std::cout << "Se agrega un vértice a la lista de adyacentes "
                 "correctamente.\n";
    vertex1.addEdge(&vertex2);
    tester.compare((size_t)1, vertex1.getAdjacent().size());
}

void seBuscaVerticeAdyacenteCorrectamente(Tester &tester){
    Vertex vertex1 = Vertex("Mabel");
    Vertex vertex2 = Vertex("Duraznito");
    std::cout << "Se agrega el vértice 'Duraznito' como adyacente a 'Mabel',"
                 " cuando se consulta si es adyacente se obtiene true.\n";
    vertex1.addEdge(&vertex2);
    tester.compare(true, vertex1.isAdjacentToVertex((std::string)"Duraznito"));
}

void seIntentaBuscarVerticeAdyacente(Tester &tester){
    Vertex vertex1 = Vertex("Mabel");
    Vertex vertex2 = Vertex("Duraznito");
    std::cout << "Se agrega el vértice 'Duraznito' como adyacente a 'Mabel',"
                 " cuando se consulta si el vértice 'Cachin' es adyacente "
                 "se obtiene false.\n";
    vertex1.addEdge(&vertex2);
    tester.compare(false, vertex1.isAdjacentToVertex((std::string)"Chachin"));
}

int main(){
    Tester tester = Tester();
    verticeSeInicializaCorrectamente(tester);
    seAgregaAdyacenteCorrectamente(tester);
    seBuscaVerticeAdyacenteCorrectamente(tester);
    seIntentaBuscarVerticeAdyacente(tester);
    tester.summarize();
    return 0;
}