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
public:
    // Fields
    T from;
    LinkedList<Edge<T>>* edges;

    // Constructors
    AdjacencyList(): from(T()), edges(nullptr) {}
    AdjacencyList(T from): from(from), edges(nullptr) {}
    AdjacencyList(const AdjacencyList<T>& other): 
        from(other.from), edges(new LinkedList<Edge<T>>(*other.edges)) {}

    // Destructor
    ~AdjacencyList() {delete edges;}

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom
     * 
     * @param other The adjacency list to copy
     * @return AdjacencyList<T>& A copied adjacency list
     */
    AdjacencyList<T>& operator = (AdjacencyList<T> other) {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Checks equality of two adjacency lists
     * 
     * @param lhs The first adjacency list to check
     * @param rhs The second adjacency list to check
     * @return true if the adjacency lists are equal, otherwise false
     */
    friend bool operator == (
            const AdjacencyList<T>& lhs, 
            const AdjacencyList<T>& rhs) {
        return lhs.from == rhs.from && *lhs.edges == *rhs.edges;
    }

    /**
     * @brief Checks inequality of two adjacency lists
     * 
     * @param lhs The first adjacency list to check
     * @param rhs The second adjacency list to check
     * @return true if the adjacency lists are inequal, otherwise false
     */
    friend bool operator != (
            const AdjacencyList<T>& lhs,
            const AdjacencyList<T>& rhs) {
        return !(lhs == rhs);
    }

    // Utility Functions

    /**
     * @brief Swaps the provided adjacency lists. Used in the copy constructor
     * 
     * @param first The first adjacency list to swap
     * @param second The second adjacency list to swap
     */
    void swap(AdjacencyList<T>& first, AdjacencyList<T>& second) {
        using std::swap;

        swap(first.from, second.from);
        swap(first.edges, second.edges);
    }
};

/**
 * @brief Adds an edge to the adjacency list
 * 
 * @tparam T The type of the list's data
 * @param list The list to add an edge to
 * @param edge The edge to add
 */
template <typename T>
void adjacencyListAddEdge(AdjacencyList<T>& list, Edge<T> edge) {
    linkedListInsertAtTail(&list.edges, edge);
}

/**
 * @brief Deletes an edge from the adjacency list
 * 
 * @tparam T The type of the list's data
 * @param list The list to delete an edge from
 * @param edge The edge to delete
 */
template <typename T>
void adjacencyListDeleteEdge(AdjacencyList<T>& list, Edge<T> edge) {
    linkedListDeleteNthOccurrence(&list.edges, edge, 1);
}

// TODO: delete, search, update

#endif