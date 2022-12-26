#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "linked_list.cpp"
#include "edge.cpp"

template <typename T>
struct Graph {
public:
    // Fields
    LinkedList<LinkedList<Edge<T>>*>* adjacency_list;

    // Constructors
    Graph(): adjacency_list(nullptr) {}
    Graph(const Graph<T>& other): 
        adjacency_list(new LinkedList<LinkedList<Edge<T>>*>(
            *other.adjacency_list)) {}

    // Destructor
    ~Graph() {delete adjacency_list;}

    // Operators
    
    // TODO: equality, inequality, assignment

    // Utility Functions
    
    // TODO: swap
};

// TODO: add node, add edge, many other ops

#endif
