#ifndef GRAPH_TPP
#define GRAPH_TPP

#include <iostream>
#include "binary_tree.tpp"
#include "linked_list.tpp"

template <typename T>
struct Graph {
public:
    explicit Graph(): edges(nullptr) {}
    BinaryTree<BinaryTree<T>>* edges;

    // Utility Functions
    std::string to_string() const {
        // in-order traversal of outer binary tree
        LinkedList<BinaryTree<T>>* inorder;
        binaryTreeInfixOrder(edges, inorder);
        LinkedList<BinaryTree<T>>* temp = inorder;
        std::string result = "[\n";
        while (temp) {
            result += "    " + temp->data.to_string();
            temp = temp->next;
            result += "\n";
        }
        result += "]";
        return result;
    }

    // Operators
    friend std::ostream& operator << (std::ostream& out, const Graph<T>& root) {
        out << root.to_string();
        return out;
    }
};

template <typename T>
void graphInsertEdge(Graph<T>* graph, T edge_val) {
    binaryTreeInsertNode(graph->edges, BinaryTree<T>(edge_val));
}

#endif