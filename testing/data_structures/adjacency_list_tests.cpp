#include "adjacency_list_tests.hpp"
#include <data_structures/adjacency_list.cpp>

bool adjacencyListTestDefaultConstructor() {
    bool result = true;

    AdjacencyList<int> list;
    result &= list.from == 0;
    result &= !list.nodes;

    return result;
}

bool adjacencyListTestDataConstructor() {
    bool result = true;

    AdjacencyList<int> list(3);
    result &= list.from == 3;
    result &= !list.nodes;

    return result;
}

bool adjacencyListTestFullConstructor() {
    bool result = true;

    LinkedList<Edge<int>>* nodes = new LinkedList<Edge<int>>(Edge<int>(2));
    linkedListInsertAtTail(&nodes, Edge<int>(5));
    AdjacencyList<int> list(3, nodes);
    result &= list.from == 3;
    result &= *list.nodes == *nodes;

    return result;
}

bool adjacencyListTestCopyConstructor() {
    bool result = true;

    LinkedList<Edge<int>>* nodes = new LinkedList<Edge<int>>(Edge<int>(2));
    linkedListInsertAtTail(&nodes, Edge<int>(5));
    AdjacencyList<int> original(3, nodes);
    AdjacencyList<int> copy(original);
    result &= copy.from == original.from;
    result &= *copy.nodes == *original.nodes;
    result &= copy.nodes != original.nodes;

    return result;
}

void adjacencyListTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("adjacency list");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        adjacencyListTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor", 
        adjacencyListTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("full constructor", 
        adjacencyListTestFullConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        adjacencyListTestCopyConstructor));

    testManagerAddTestGroup(test_manager, test_group);
}
