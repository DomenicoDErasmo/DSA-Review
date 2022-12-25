#ifndef EDGE_CPP
#define EDGE_CPP

#include <cmath>

/**
 * @brief Implementation of an "edge" - a destination object and a weight
 * 
 * @tparam T The type of the destination object
 */
template <typename T>
struct Edge {
public:
    // Fields
    T to;
    double weight;

    // Constructors
    Edge(): to(T()), weight(0) {}
    Edge(T to): to(to), weight(0) {}
    Edge(T to, double weight): to(to), weight(weight) {}

    // Operators

    /**
     * @brief Checks equality of the two edges
     * 
     * @param lhs The left edge to check
     * @param rhs The right edge to check
     * @return true if the edges are equal, otherwise false
     */
    friend bool operator == (const Edge<T>& lhs, const Edge<T>& rhs) {
        return lhs.to == rhs.to && std::abs(lhs.weight - rhs.weight) < 0.001;
    }

    /**
     * @brief Checks inequality of the two edges
     * 
     * @param lhs The left edge to check
     * @param rhs The right edge to check
     * @return true if the edges are inequal, otherwise false
     */
    friend bool operator != (const Edge<T>& lhs, const Edge<T>& rhs) {
        return !(lhs == rhs);
    }
};

#endif