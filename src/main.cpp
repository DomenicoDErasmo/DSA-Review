#include <iostream>
#include <type_traits>
#include "data_structures/graph.cpp"
#include "data_structures/binary_tree.cpp"

int main() {
    Graph<int>* graph = new Graph<int>();
    graphInsertEdge(graph, 4);
    std::cout << *graph << std::endl;

    delete graph;
    return 0;
}