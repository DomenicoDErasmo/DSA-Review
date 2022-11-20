#include <iostream>
#include "data_structures/graph.tpp"

int main() {
    Graph<int> graph;
    graphAddEdge(&graph, 4);
    std::cout << "graph.edges->data: " << graph.edges->data << std::endl;
    graphAddNode(&graph, 4, 5);
    std::cout << "graph.edges->data: " << graph.edges->right->data << std::endl;
}