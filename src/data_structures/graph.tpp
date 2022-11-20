#ifndef GRAPH_TPP
#define GRAPH_TPP

#include "binary_tree.tpp"

template <typename T>
struct Graph {
public:
    explicit Graph(): edges(nullptr) {}
    BinaryTree<BinaryTree<T>>* edges;
};

template <typename T>
void graphInsertEdge(Graph<T>* graph, T edge_val) {
    binaryTreeInsertNode(graph->edges, BinaryTree<T>(edge_val));
}

template <typename T>
BinaryTree<BinaryTree<T>>* graphFindEdge(Graph<T>* graph, T edge_val) {
    return binaryTreeFindNode(graph->edges, BinaryTree<T>(edge_val));
}

template <typename T>
void graphInsertNode(Graph<T>* graph, T edge_val, T node_val) {
    BinaryTree<BinaryTree<T>>* edge = graphFindEdge(graph, edge_val);
    if (edge) {
        BinaryTree<T>* data = &edge->data;
        binaryTreeInsertNode(data, node_val);
    }
}

template <typename T>
void graphDeleteEdge(Graph<T>* graph, T edge_val) {
    binaryTreeDeleteNode(graph->edges, BinaryTree<T>(edge_val));
}

#endif