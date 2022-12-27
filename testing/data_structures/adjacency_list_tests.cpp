#include "adjacency_list_tests.hpp"
#include <data_structures/adjacency_list.cpp>

bool adjacencyListTestDefaultConstructor() {
    bool result = true;
    
    AdjacencyList<int> empty;
    result &= empty.from == 0;
    result &= !empty.edges;

    return result;
}

bool adjacencyListTestDataConstructor() {
    bool result = true;

    AdjacencyList<int> has_from(2);
    result &= has_from.from == 2;
    result &= !has_from.edges;

    return result;
}

bool adjacencyListTestCopyConstructor() {
    bool result = true;

    AdjacencyList<int> original(3);
    linkedListInsertAtTail(&original.edges, Edge<int>(3, 4));
    linkedListInsertAtTail(&original.edges, Edge<int>(3, 5));
    AdjacencyList<int> copy(original);
    result &= copy.from == original.from;
    result &= *copy.edges == *original.edges;
    result &= copy.edges != original.edges;

    return result;
}

bool adjacencyListTestAssignmentOperator() {
    bool result = true;

    AdjacencyList<int> original(3);
    linkedListInsertAtTail(&original.edges, Edge<int>(3, 4));
    linkedListInsertAtTail(&original.edges, Edge<int>(3, 5));
    AdjacencyList<int> copy = original;
    result &= copy.from == original.from;
    result &= *copy.edges == *original.edges;
    result &= copy.edges != original.edges;

    return result;
}

bool adjacencyListTestEqualityOperator() {
    bool result = true;

    AdjacencyList<int> inequal_data_lhs(3);
    AdjacencyList<int> inequal_data_rhs(2);
    result &= !(inequal_data_lhs == inequal_data_rhs);

    AdjacencyList<int> inequal_edges_lhs(2);
    linkedListInsertAtTail(&inequal_edges_lhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&inequal_edges_lhs.edges, Edge<int>(2, 5));
    AdjacencyList<int> inequal_edges_rhs(2);
    linkedListInsertAtTail(&inequal_edges_rhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&inequal_edges_rhs.edges, Edge<int>(2, 6));
    result &= !(inequal_edges_lhs == inequal_edges_rhs);

    AdjacencyList<int> equal_lhs(2);
    linkedListInsertAtTail(&equal_lhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&equal_lhs.edges, Edge<int>(2, 5));
    AdjacencyList<int> equal_rhs(2);
    linkedListInsertAtTail(&equal_rhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&equal_rhs.edges, Edge<int>(2, 5));
    result &= equal_lhs == equal_rhs;

    return result;
}

void adjacencyListTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("adjaceny list");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        adjacencyListTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor", 
        adjacencyListTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        adjacencyListTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator", 
        adjacencyListTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        adjacencyListTestEqualityOperator));

    testManagerAddTestGroup(test_manager, test_group);
}