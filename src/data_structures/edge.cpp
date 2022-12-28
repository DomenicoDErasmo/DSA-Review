#ifndef EDGE_CPP
#define EDGE_CPP

/**
 * @brief Implementation of an "edge" - a destination object and a weight
 * 
 * @tparam T The type of the destination object
 */
template <typename T>
struct Edge {
public:
    // Fields
    T from;
    T to;
    double weight;

    // Constructors
    Edge(): from(T()), to(T()), weight(0) {}
    Edge(T from, T to): from(from), to(to), weight(0) {}
    Edge(T from, T to, double weight): from(from), to(to), weight(weight) {}

    // Operators

    /**
     * @brief Checks equality of the two edges. Ignores differences in weight
     * 
     * @param lhs The left edge to check
     * @param rhs The right edge to check
     * @return true if the edges are equal, otherwise false
     */
    friend bool operator == (const Edge<T>& lhs, const Edge<T>& rhs) {
        return lhs.from == rhs.from 
        && lhs.to == rhs.to;
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