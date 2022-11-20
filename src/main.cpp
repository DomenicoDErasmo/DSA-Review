#include <iostream>
#include "data_structures/graph.tpp"
#include "data_structures/binary_tree.tpp"

int main() {
    Graph<int>* graph = new Graph<int>();
    graphInsertEdge(graph, 4);
    graphInsertNode(graph, 4, 5);
    std::cout << graph->edges->data << std::endl;

    delete graph;
}