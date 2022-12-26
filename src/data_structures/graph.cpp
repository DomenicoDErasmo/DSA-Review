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

    /**
     * @brief Assignment operator for graphs
     * 
     * @param rhs The graph to copy over to the new graph
     * @return const Graph<T>& The copied graph
     */
    const Graph<T>& operator = (Graph<T> rhs) {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Equality operator for graphs
     * 
     * @param lhs The left graph to check
     * @param rhs The right graph to check
     * @return true if the graphs are equal, otherwise false
     */
    friend bool operator == (const Graph<T>& lhs, const Graph<T>& rhs) {
        return *lhs.adjacency_list == *rhs.adjacency_list;
    }

    /**
     * @brief Inequality operator for graphs
     * 
     * @param lhs The left graph to check
     * @param rhs The right graph to check
     * @return true if the graphs are inequal, otherwise false
     */
    friend bool operator != (const Graph<T>& lhs, const Graph<T>& rhs) {
        return *lhs.adjacency_list == *rhs.adjacency_list;
    }

    // Utility Functions
    /**
     * @brief Swaps the given graphs
     * 
     * @param lhs The left graph to swap
     * @param rhs The right graph to swap
     */
    friend void swap(Graph<T>& lhs, Graph<T>& rhs) {
        using std::swap;

        swap(lhs.adjacency_list, rhs.adjacency_list);
    }
};

// TODO: add node, add edge, many other ops

#endif
