#include "queue_tests.hpp"

#include <data_structures/queue.cpp>

bool queueTestPush() {
    bool result = true;

    Queue<int> empty;
    queuePush(empty, 4);
    result &= (empty.head->data == 4);
    result &= (empty.tail->data == 4);

    Queue<int> not_empty(4);
    queuePush(not_empty, 5);
    result &= (not_empty.head->data == 4);
    result &= (not_empty.tail->data == 5);

    return result;
}

bool queueTestPop() {
    bool result = true;

    Queue<int> empty;
    queuePop(empty);
    result &= (!empty.head);

    Queue<int> pop_head(4);
    queuePop(pop_head);
    result &= (!pop_head.head);
    result &= (!pop_head.tail);

    Queue<int> two_elements(4);
    queuePush(two_elements, 5);
    queuePop(two_elements);
    result &= (two_elements.head->data == 5);
    result &= (two_elements.tail->data == 5);

    return result;
}

bool queueTestFront() {
    bool result = true;

    Queue<int> queue(4);
    result &= (queueFront(queue) == 4);

    return result;
}

bool queueTestEmpty() {
    bool result = true;

    Queue<int> empty;
    result &= (queueIsEmpty(empty));

    Queue<int> not_empty(4);
    result &= (!queueIsEmpty(not_empty));

    return result;
}

TestGroup queueRegisterTests() {
    TestGroup test_group("queues");
    test_group.addTest(UnitTest(queueTestPush, "push"));
    test_group.addTest(UnitTest(queueTestPop, "pop"));
    test_group.addTest(UnitTest(queueTestFront, "front"));
    test_group.addTest(UnitTest(queueTestEmpty, "is empty"));
    return test_group;
}