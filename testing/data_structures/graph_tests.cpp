#include "graph_tests.hpp"
#include <data_structures/graph.cpp>

bool graphTestDefaultConstructor() {
    bool result = true;

    Graph<int> empty;
    result &= !empty.adjacency_list;

    return result;
}

// TODO: reimplement all of the below

bool graphTestCopyConstructor() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_list, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_list, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_list, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy(original);
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_list, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_list, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_list, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_list, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_list, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy = original;
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_list, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_list, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestEqualityOperator() {
    bool result = true;

    return result;
}

void graphTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("graph");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        graphTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        graphTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator", 
        graphTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        graphTestEqualityOperator));

    testManagerAddTestGroup(test_manager, test_group);
}
