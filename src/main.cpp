#include <iostream>
#include <type_traits>
#include "data_structures/graph.cpp"
#include "data_structures/binary_tree.cpp"

int main() {
    std::cout << "Running\n";
    std::cout << "Running\n";
    Graph<int>* graph = new Graph<int>();
    graphInsertEdge(graph, 4);
    std::cout << *graph << std::endl;

    delete graph;
    return 0;
}