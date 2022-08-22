#ifndef VERTEX_TPP
#define VERTEX_TPP

#include "binary_tree.tpp"

template <typename T>
class Vertex {
public:
    // Constructors
    Vertex(): data(T()), edges(BinaryTree<Vertex<T>>()) {}
    Vertex(T in_data): data(in_data) {}

    // Getters
    T getData() {return data;}
    BinaryTree<Vertex<T>> getEdges() {return edges;}

    // Setters
    void setData(T in_data) {data = in_data;}
private:
    T data;
    BinaryTree<Vertex<T>> edges;
};

#endif