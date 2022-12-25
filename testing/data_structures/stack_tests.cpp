#include "stack_tests.hpp"
#include <data_structures/stack.cpp>

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

bool stackTestSize() {
    bool result = true;

    Stack<int> empty;
    result &= stackSize(empty) == 0;

    Stack<int> one_element(4);
    result &= stackSize(one_element) == 1;

    return result;
}

bool stackTestEmpty() {
    bool result = true;

    Stack<char> empty;
    result &= stackEmpty(empty);

    Stack<char> not_empty('4');
    result &= !stackEmpty(not_empty);

    return result;
}

bool stackTestPush() {
    bool result = true;

    Stack<int> empty;
    stackPush(empty, 4);
    result &= empty.top->data == 4;

    Stack<int> not_empty(3);
    stackPush(not_empty, 5);
    result &= not_empty.top->data == 5;

    return result;
}

bool stackTestTop() {
    bool result = true;

    Stack<int> empty;
    try {
        int top = stackTop(empty);
        result &= (top == 0);
    } catch (std::logic_error) {
        result &= true;
    } catch (...) {
        result &= false;
    }

    Stack<int> not_empty(4);
    int top = stackTop(not_empty);
    result &= top == 4;

    Stack<int> two_elements(5);
    stackPush(two_elements, 2);
    result &= stackTop(two_elements) == 2;

    return result;
}

bool stackTestPop() {
    bool result = true;

    Stack<int> empty;
    try {
        stackPop(empty);
    } catch (std::logic_error) {
        result &= true;
    } catch (...) {
        result &= false;
    }

    Stack<int> one_element(4);
    stackPop(one_element);
    result &= stackEmpty(one_element);

    Stack<int> two_elements(4);
    stackPush(two_elements, 6);
    stackPop(two_elements);
    result &= stackTop(two_elements) == 4;

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
    testGroupAddTest(&test_group, UnitTest("size", stackTestSize));
    testGroupAddTest(&test_group, UnitTest("empty", stackTestEmpty));
    testGroupAddTest(&test_group, UnitTest("push", stackTestPush));
    testGroupAddTest(&test_group, UnitTest("top", stackTestTop));
    testGroupAddTest(&test_group, UnitTest("pop", stackTestPop));
    

    testManagerAddTestGroup(test_manager, test_group);
}