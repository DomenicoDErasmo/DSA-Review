#include "queue_tests.hpp"
#include <data_structures/queue.cpp>

bool queueTestDefaultConstructor() {
    bool result = true;

    Queue<int> queue;
    result &= !queue.head;
    result &= !queue.tail;

    return result;
}

bool queueTestDataConstructor() {
    bool result = true;

    Queue<int> queue(4);
    result &= queue.head->data == 4;
    result &= queue.head == queue.tail;

    return result;
}

bool queueTestCopyConstructor() {
    bool result = true;

    Queue<int> queue(4);
    linkedListInsertAtTail(&queue.head, 5);
    linkedListInsertAtTail(&queue.head, 6);
    queue.tail = queue.head->next->next;
    Queue<int> copy(queue);
    result &= copy.head->data == queue.head->data;
    result &= copy.head != queue.head;
    result &= copy.tail->data == queue.tail->data;
    result &= copy.tail != queue.tail;

    return result;
}

bool queueTestAssignmentOperator() {
    bool result = true;

    Queue<int> original(4);
    linkedListInsertAtTail(&original.head, 2);
    original.tail = original.head->next;
    Queue<int> assigned = original;
    result &= assigned.head->data == original.head->data;
    result &= assigned.head != original.head;
    result &= assigned.tail->data == original.tail->data;
    result &= assigned.tail != original.tail;

    return result;
}

bool queueTestEqualityOperator() {
    bool result = true;

    Queue<int> different_head_lhs(4);
    linkedListInsertAtTail(&different_head_lhs.head, 2);
    Queue<int> different_head_rhs(2);
    linkedListInsertAtTail(&different_head_rhs.head, 2);
    result &= !(different_head_lhs == different_head_rhs);

    Queue<int> different_tail_lhs(4);
    linkedListInsertAtTail(&different_tail_lhs.tail, 2);
    Queue<int> different_tail_rhs(4);
    linkedListInsertAtTail(&different_tail_rhs.tail, 3);
    result &= !(different_tail_lhs == different_tail_rhs);

    Queue<int> equals_lhs(4);
    linkedListInsertAtTail(&equals_lhs.tail, 2);
    Queue<int> equals_rhs(4);
    linkedListInsertAtTail(&equals_rhs.tail, 2);
    result &= equals_lhs == equals_rhs;

    return result;
}

bool queueTestEmpty() {
    bool result = true;

    Queue<int> empty;
    result &= queueEmpty(empty);
    
    Queue<int> not_empty(4);
    result &= !queueEmpty(not_empty);

    return result;
}

bool queueTestLength() {
    bool result = true;

    Queue<int> empty;
    result &= queueLength(empty) == 0;

    Queue<int> one_element(4);
    result &= queueLength(one_element) == 1;

    Queue<int> many_elements(4);
    linkedListInsertAtTail(&many_elements.head, 2);
    linkedListInsertAtTail(&many_elements.head, 3);
    many_elements.tail = linkedListGetTail(&many_elements.head);
    result &= queueLength(many_elements) == 3;

    return result;
}

bool queueTestPush() {
    bool result = true;

    Queue<char> empty;
    queuePush(empty, 'h');
    result &= queueFront(empty) == 'h';
    result &= queueLength(empty) == 1;
    result &= empty.tail->data == 'h';

    Queue<int> not_empty(4);
    queuePush(not_empty, 1);
    result &= queueLength(not_empty) == 2;
    result &= not_empty.tail->data == 1;

    return result;
}

bool queueTestFront() {
    bool result = true;

    Queue<int> empty;
    try {
        queueFront(empty);
    } catch (std::logic_error) {
        result &= true;
    } catch (...) {
        result &= false;
    }

    Queue<char> many_characters('a');
    linkedListInsertAtTail(&many_characters.head, '2');
    linkedListInsertAtTail(&many_characters.head, 'f');
    many_characters.tail = linkedListGetTail(&many_characters.head);
    result &= queueFront(many_characters) == 'a';

    return result;
}

bool queueTestPop() {
    bool result = true;

    Queue<int> empty;
    try {
        queuePop(empty);
    } catch (std::logic_error) {
        result &= true;
    } catch (...) {
        result &= false;
    }

    Queue<int> one_element(4);
    queuePop(one_element);
    result &= queueEmpty(one_element);

    return result;
}

void queueTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("queue");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        queueTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor",
        queueTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor",
        queueTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator",
        queueTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator",
        queueTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("empty", queueTestEmpty));
    testGroupAddTest(&test_group, UnitTest("length", queueTestLength));
    testGroupAddTest(&test_group, UnitTest("push", queueTestPush));
    testGroupAddTest(&test_group, UnitTest("front", queueTestFront));
    testGroupAddTest(&test_group, UnitTest("pop", queueTestPop));

    testManagerAddTestGroup(test_manager, test_group);
}
