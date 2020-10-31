#include "../eBPFAnalyzer.h"
#include <list>
#include <iostream>
int main(){
    Graph graph = Graph();
    eBPFAnalyzer analyzer = eBPFAnalyzer(graph);
    analyzer.parseAndModel("../Tests/test_files/arp.bpf");
    graph.showAdjacencies();
    return 0;
}