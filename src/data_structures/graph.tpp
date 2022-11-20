#ifndef GRAPH_TPP
#define GRAPH_TPP

#include "binary_tree.tpp"

template <typename T>
struct Graph {
public:
    Graph(): edges(nullptr) {}
    BinaryTree<BinaryTree<T>>* edges;
};

template <typename T>
void graphAddEdge(Graph<T>* graph, T data) {
    binaryTreeInsertNode(graph->edges, BinaryTree<T>(data));
}

template <typename T>
void graphAddNode(Graph<T>* graph, T edge_val, T data) {
    BinaryTree<BinaryTree<T>>* edge = binaryTreeFindNode(graph->edges, BinaryTree<T>(edge_val));
    if (edge) {binaryTreeInsertNode(edge, BinaryTree<T>(data));}
}

#endif