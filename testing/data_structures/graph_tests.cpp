#include "graph_tests.hpp"
#include <data_structures/graph.cpp>

bool graphTestDefaultConstructor() {
    bool result = true;

    Graph<int> empty;
    result &= !empty.adjacency_list;

    return result;
}

bool graphTestCopyConstructor() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtHead(&original.adjacency_list, 
        new LinkedList<Edge<int>>(Edge<int>(4)));
    linkedListInsertAtHead(&original.adjacency_list, 
        new LinkedList<Edge<int>>(Edge<int>(5)));
    Graph<int> copy(original);
    result &= *copy.adjacency_list == *original.adjacency_list;
    result &= copy.adjacency_list != original.adjacency_list;

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtHead(&original.adjacency_list, 
        new LinkedList<Edge<int>>(Edge<int>(4)));
    linkedListInsertAtHead(&original.adjacency_list, 
        new LinkedList<Edge<int>>(Edge<int>(5)));
    Graph<int> assigned = original;

    result &= *original.adjacency_list == *assigned.adjacency_list;
    result &= original.adjacency_list != assigned.adjacency_list;

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

    testManagerAddTestGroup(test_manager, test_group);
}
