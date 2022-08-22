#ifndef GRAPH_TPP
#define GRAPH_TPP

#include "binary_tree.tpp"
#include "vertex.tpp"

template <typename T>
class Graph {
public:
    // Constructors
    Graph() {}
    
    // Getters

    // Setters

    // Utility Functions

private:
    BinaryTree<Vertex<T>> vertices;
};

#endif