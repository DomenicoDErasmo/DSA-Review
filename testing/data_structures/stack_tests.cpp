#include "stack_tests.hpp"

#include <data_structures/stack.tpp>

bool stackTestTop() {
    bool result = true;

    Stack<int> stack(4);
    result &= (stackTop(stack) == 4);

    return result;
}

bool stackTestPush() {
    bool result = true;

    Stack<int> stack;
    stackPush(stack, 5);
    result &= (stackTop(stack) == 5);

    stackPush(stack, 6);
    result &= (stackTop(stack) == 6);

    return result;
}

bool stackTestPop() {
    bool result = true;

    Stack<int> empty;
    stackPop(empty);
    result &= (!empty.head);

    Stack<int> stack(5);
    stackPush(stack, 6);
    stackPop(stack);
    result &= (stackTop(stack) == 5);

    return result;
}

TestGroup stackRegisterTests() {
    TestGroup test_group("stacks");
    test_group.addTest(UnitTest(stackTestTop, "top"));
    test_group.addTest(UnitTest(stackTestPush, "push"));
    test_group.addTest(UnitTest(stackTestPop, "pop"));
    return test_group;
}