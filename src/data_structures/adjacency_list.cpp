#ifndef ADJACENCY_LIST_CPP
#define ADJACENCY_LIST_CPP

#include "linked_list.cpp"
#include "edge.cpp"

/**
 * @brief Implementation of adjacency list
 * 
 * @tparam T The type of the adjacency list's data
 */
template <typename T>
struct AdjacencyList {
    // Fields
    T from;
    LinkedList<Edge<T>>* nodes;

    // Constructors
    AdjacencyList(): from(T()), nodes(nullptr) {}
    AdjacencyList(T from): from(from), nodes(nullptr) {}
    AdjacencyList(
        T from, 
        LinkedList<Edge<T>>* nodes): from(from), nodes(nodes) {}
    AdjacencyList(const AdjacencyList<T>& other): 
        from(other.from), 
        nodes(new LinkedList<Edge<T>>(*other.nodes)) {}

    // Destructor
    ~AdjacencyList() {delete nodes;}

    // Operators
    // TODO: equality, inequality, copy assignment

    // Utility Functions
    // TODO: copy and swap
};

#endif