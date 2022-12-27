#include "edge_tests.hpp"
#include <data_structures/edge.cpp>

bool edgeTestDefaultConstructor() {
    bool result = true;

    Edge<int> edge;
    result &= edge.to == 0;
    result &= edge.weight == 0;

    return result;
}

bool edgeTestDataConstructor() {
    bool result = true;

    Edge<int> edge(2, 5);
    result &= edge.from == 2;
    result &= edge.to == 5;
    result &= edge.weight == 0;

    return result;
}

bool edgeTestFullConstructor() {
    bool result = true;

    // note: keeping example weights simple, as double equality can get wonky
    Edge<int> edge(2, 4, 2.5);
    result &= edge.from == 2;
    result &= edge.to == 4;
    result &= edge.weight == 2.5;

    return result;
}

bool edgeTestEqualityOperator() {
    bool result = true;

    Edge<int> inequal_from_lhs(2, 4);
    Edge<int> inequal_from_rhs(3, 4);
    result &= !(inequal_from_lhs == inequal_from_rhs);

    Edge<int> inequal_to_lhs(2, 4);
    Edge<int> inequal_to_rhs(2, 5);
    result &= !(inequal_to_lhs == inequal_to_rhs);

    Edge<int> inequal_weight_lhs(1, 2, 1.4);
    Edge<int> inequal_weight_rhs(1, 2, 1.5);
    result &= !(inequal_weight_lhs == inequal_weight_rhs);

    Edge<int> equal_lhs(2, 1, 1.0001);
    Edge<int> equal_rhs(2, 1, 1);
    result &= equal_lhs == equal_rhs;

    return result;
}

void edgeTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("edge");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        edgeTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor", 
        edgeTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("full constructor", 
        edgeTestFullConstructor));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        edgeTestEqualityOperator));

    testManagerAddTestGroup(test_manager, test_group);
}