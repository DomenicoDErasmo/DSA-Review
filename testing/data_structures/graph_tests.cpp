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

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

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
