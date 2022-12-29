#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "linked_list.cpp"
#include "adjacency_list.cpp"

template <typename T>
struct Graph {
public:
    // Fields
    LinkedList<AdjacencyList<T>>* adjacency_matrix;

    // Constructors
    Graph(): adjacency_matrix(nullptr) {}
    Graph(const Graph<T>& other): 
        adjacency_matrix(new LinkedList<AdjacencyList<T>>(
            *other.adjacency_matrix)) {}

    // Destructor
    ~Graph() {delete adjacency_matrix;}

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
     * @brief Equality operator for graphs.
     * 
     * @param lhs The left graph to check
     * @param rhs The right graph to check
     * @return true if the graphs are equal, otherwise false
     */
    friend bool operator == (const Graph<T>& lhs, const Graph<T>& rhs) {
        return *lhs.adjacency_matrix == *rhs.adjacency_matrix;
    }

    /**
     * @brief Inequality operator for graphs
     * 
     * @param lhs The left graph to check
     * @param rhs The right graph to check
     * @return true if the graphs are inequal, otherwise false
     */
    friend bool operator != (const Graph<T>& lhs, const Graph<T>& rhs) {
        return !(*lhs.adjacency_matrix == *rhs.adjacency_matrix);
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

        swap(lhs.adjacency_matrix, rhs.adjacency_matrix);
    }
};

/**
 * @brief Gets the adjacency list in the graph
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to search
 * @param data The node to search for in the graph
 * @return LinkedList<AdjacencyList<T>>* The node if it exists
 */
template <typename T>
LinkedList<AdjacencyList<T>>* graphGetNode(Graph<T>& graph, T data) {
    return linkedListGetNthOccurrence(
        graph.adjacency_matrix, 
        AdjacencyList<T>(data), 
        1);
}

/**
 * @brief Checks if the graph has the given node
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to search
 * @param data The node to search for in the graph
 * @return true if the node is found, otherwise false
 */
template <typename T>
bool graphHasNode(Graph<T>& graph, T data) {
    return graphGetNode(graph, data) != nullptr;
}

/**
 * @brief Adds an adjacency list to the graph if none exists
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to add an adjacency list to
 * @param data The data to add to the graph
 */
template <typename T>
void graphAddNode(Graph<T>& graph, T data) {
    if (!graphHasNode(graph, data)) {
        linkedListInsertAtTail(&graph.adjacency_matrix, AdjacencyList<T>(data));
    }
}

/**
 * @brief Adds an edge to the graph
 * 
 * @tparam T 
 * @param graph 
 * @param edge 
 */
template <typename T>
void graphAddEdge(Graph<T>& graph, Edge<T> edge) {
    LinkedList<AdjacencyList<T>>* adj_list = graphGetNode(graph, edge.from);
    if (!adj_list) {
        throw std::logic_error("Can't add an edge if the graph doesn't exist.");
    }

    LinkedList<Edge<T>>* found = linkedListGetNthOccurrence(
        adj_list->data.edges, 
        edge,
        1);

    if (found != nullptr) {
        throw std::logic_error(
            "Can't add an edge if the edge already exists."
            "Instead use graphUpdateNode.");
    }

    linkedListInsertAtTail(&adj_list->data.edges, edge);
}

// TODO: add many other ops - CRUD for adjacency lists and edges


#endif
