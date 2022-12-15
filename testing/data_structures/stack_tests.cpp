#include "stack_tests.hpp"

bool stackTestEmptyConstructor() {
    bool result = true;
    
    Stack<int> empty;
    result &= !empty.top;

    return result;
}

bool stackTestDataConstructor() {
    bool result = true;

    Stack<int> data(4);
    result &= data.top->data == 4;

    return result;
}

bool stackTestCopyConstructor() {
    bool result = true;

    Stack<int> original(4);
    Stack<int> copy(original);
    result &= *copy.top == *original.top;
    result &= copy.top != original.top;

    return result;
}

bool stackTestAssignmentOperator() {
    bool result = true;

    Stack<int> original(4);
    Stack<int> copy = original;
    result &= *copy.top == *original.top;

    return result;
}

bool stackTestEqualityOperator() {
    bool result = true;

    Stack<int> inequal_lhs(5);
    Stack<int> inequal_rhs(3);
    result &= !(inequal_lhs == inequal_rhs);

    Stack<int> equal_lhs(4);
    Stack<int> equal_rhs(4);
    result &= equal_lhs == equal_rhs;

    return result;
}

void stackTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("stack");

    testGroupAddTest(&test_group, UnitTest("empty constructor",
        stackTestEmptyConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor",
        stackTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor",
        stackTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator",
        stackTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator",
        stackTestEqualityOperator));

    testManagerAddTestGroup(test_manager, test_group);
}