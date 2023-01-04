#ifndef GRAPH_CPP
#define GRAPH_CPP

#include <fstream>
#include <sstream>
#include <string>

#include "linked_list.cpp"
#include "adjacency_list.cpp"

enum GraphDirection {
    GRAPH_UNDIRECTED,
    GRAPH_DIRECTED
};

template <typename T>
struct Graph {
public:
    // Fields
    LinkedList<AdjacencyList<T>>* adjacency_matrix;

    // Constructors
    Graph(): adjacency_matrix(nullptr) {}

    /**
     * @brief Constructs a new Graph object with zero-indexed nodes from a 
     * filepath. The filepath should be structred as follows:
     * 
     * First line has the number of nodes.
     * Every subsequent line has "from to weight", where weight is optional.
     * 
     * This project stores its example graphs in the resources folder
     * 
     * @param filepath The path of the text file detailing the graph
     * @param is_directed A flag to determine if the graph is directed
     */
    Graph(std::string filepath, GraphDirection direction): 
            adjacency_matrix(nullptr) {
        std::ifstream reader(filepath);
        std::string line;
        std::getline(reader, line);
        int size = std::stoi(line);
        for (int i = 0; i < size; i++) {graphAddNode(*this, i);}

        while (std::getline(reader, line)) {
            std::istringstream iss(line);
            std::string token;
            double vals[3] = {0, 0, 1};
            int i = 0;
            while (std::getline(iss, token, ' ')) {
                vals[i] = std::stod(token);
                i++;
            }
            graphAddEdge(*this, Edge<int>(vals[0], vals[1], vals[2]));
            if (direction == GRAPH_UNDIRECTED) {
                graphAddEdge(*this, Edge<int>(vals[1], vals[0], vals[2]));
            }
        }
        reader.close();
    }

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

// TODO: consider how to add equality operators in

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
        1,
        adjacencyListWeakEquality);
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
 * @brief Gets the edge from the list if it exists
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to get the edge from
 * @param edge The edge to search for. Only needs from and to values
 * @return LinkedList<Edge<T>>* The edge in the graph, or null
 */
template <typename T>
LinkedList<Edge<T>>* graphGetEdge(Graph<T>& graph, Edge<T> edge) {
    if (!graphHasNode(graph, edge.from)) {
        throw std::logic_error("Can't add an edge if the graph doesn't exist.");
    }

    LinkedList<AdjacencyList<T>>* adj_list = graphGetNode(graph, edge.from);
    return linkedListGetNthOccurrence(
        adj_list->data.edges, 
        edge, 
        1, 
        edgeWeakEquality);
}

/**
 * @brief Checks if the graph has the given edge
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to get the edge from
 * @param edge The edge to search for. Only needs from and to values
 * @return true if the edge is in the graph, otherwise false
 */
template <typename T>
bool graphHasEdge(Graph<T>& graph, Edge<T> edge) {
    try {
        return graphGetEdge(graph, edge) != nullptr;
    } catch (std::logic_error) {
        return false;
    }
}

/**
 * @brief Adds an edge to the graph
 * 
 * @tparam T The type of the graph's data
 * @param graph The graph to add an edge to
 * @param edge The edge to add
 */
template <typename T>
void graphAddEdge(Graph<T>& graph, Edge<T> edge) {
    if (!graphHasNode(graph, edge.from)) {
        throw std::logic_error("Can't add an edge if the graph doesn't exist.");
    }

    if (graphHasEdge(graph, edge)) {
        throw std::logic_error(
            "Can't add an edge if the edge already exists."
            "Instead use graphUpdateNode.");
    }

    LinkedList<AdjacencyList<T>>* adj_list = graphGetNode(graph, edge.from);
    linkedListInsertAtTail(&adj_list->data.edges, edge);
}

// TODO: add many other ops - CRUD for adjacency lists and edges
// has/add/get/delete/update for node/edge


#endif
