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

    AdjacencyList<int> inequal_from_lhs(3);
    AdjacencyList<int> inequal_from_rhs(2);
    result &= !(inequal_from_lhs == inequal_from_rhs);

    AdjacencyList<int> equal_lhs(2);
    linkedListInsertAtTail(&equal_lhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&equal_lhs.edges, Edge<int>(2, 5));
    AdjacencyList<int> equal_rhs(2);
    linkedListInsertAtTail(&equal_rhs.edges, Edge<int>(2, 4));
    linkedListInsertAtTail(&equal_rhs.edges, Edge<int>(2, 5));
    result &= equal_lhs == equal_rhs;

    return result;
}

bool adjacencyListTestAddEdge() {
    bool result = true;

    AdjacencyList<int> list(4);
    result &= !list.edges;
    adjacencyListAddEdge(list, Edge<int>(4, 5));
    result &= linkedListGetLength(list.edges) == 1;
    result &= list.edges->data == Edge<int>(4, 5);
    adjacencyListAddEdge(list, Edge<int>(4, 6, 1.2));
    result &= linkedListGetLength(list.edges) == 2;
    result &= list.edges->next->data == Edge<int>(4, 6, 1.2);

    return result;
}

bool adjacencyListTestDeleteEdge() {
    bool result = true;

    AdjacencyList<int> list(4);
    result &= !list.edges;
    adjacencyListAddEdge(list, Edge<int>(4, 5));
    adjacencyListAddEdge(list, Edge<int>(4, 6, 1.2));
    adjacencyListDeleteEdge(list, Edge<int>(4, 5));
    result &= list.edges->data == Edge<int>(4, 6, 1.2);
    result &= linkedListGetLength(list.edges) == 1;

    return result;
}

bool adjacencyListTestGetEdge() {
    bool result = true;

    AdjacencyList<int> list(4);
    result &= !list.edges;
    adjacencyListAddEdge(list, Edge<int>(4, 5));
    adjacencyListAddEdge(list, Edge<int>(4, 6, 1.2));
    LinkedList<Edge<int>>* not_found = adjacencyListGetEdge(list, 3);
    result &= !not_found;
    LinkedList<Edge<int>>* found = adjacencyListGetEdge(list, 5);
    result &= found == list.edges;

    return result;
}

bool adjacencyListTestUpdateEdge() {
    bool result = true;

    AdjacencyList<int> list(4);
    result &= !list.edges;
    adjacencyListAddEdge(list, Edge<int>(4, 5));
    adjacencyListAddEdge(list, Edge<int>(4, 6, 1.2));
    adjacencyListUpdateEdge(list, 5, Edge<int>(4, 5, 2.2));
    result &= list.edges->data.weight == 2.2;

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
    testGroupAddTest(&test_group, UnitTest("add edge", 
        adjacencyListTestAddEdge));
    testGroupAddTest(&test_group, UnitTest("delete edge", 
        adjacencyListTestDeleteEdge));
    testGroupAddTest(&test_group, UnitTest("get edge", 
        adjacencyListTestGetEdge));
    testGroupAddTest(&test_group, UnitTest("update edge", 
        adjacencyListTestUpdateEdge));

    testManagerAddTestGroup(test_manager, test_group);
}