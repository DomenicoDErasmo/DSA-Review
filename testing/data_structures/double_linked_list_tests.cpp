#include "double_linked_list_tests.hpp"

bool doubleLinkedListTestDefaultConstructor() {
    bool result = true;

    DoubleLinkedList<int> int_list;
    result &= int_list.data == 0;
    result &= !int_list.prev;
    result &= !int_list.next;

    return result;
}

bool doubleLinkedListTestDataConstructor() {
    bool result = true;

    DoubleLinkedList<int> int_list(4);
    result &= int_list.data == 4;
    result &= !int_list.prev;
    result &= !int_list.next;

    return result;
}

bool doubleLinkedListTestFullConstructor() {
    bool result = true;

    // We only want to delete from the leftmost node
    // Otherwise we can corrupt the heap
    DoubleLinkedList<int>* int_list = new DoubleLinkedList<int>(4,
        new DoubleLinkedList<int>(6),
        new DoubleLinkedList<int>(7));
    result &= int_list->data == 4;
    result &= int_list->prev->data == 6;
    result &= int_list->next->data == 7;
    int_list = int_list->prev;
    delete int_list;

    return result;
}

bool doubleLinkedListTestCopyConstructor() {
    bool result = true;

    DoubleLinkedList<int> one_next(4,
        nullptr,
        new DoubleLinkedList<int>(2));

    DoubleLinkedList<int> one_next_copy(one_next);
    result &= one_next_copy.data == one_next.data;
    result &= !one_next_copy.prev;
    result &= one_next_copy.next->data == one_next.next->data;

    // Hacky way of constructing before we make our insert function
    DoubleLinkedList<int> two_next(4,
        nullptr,
        new DoubleLinkedList<int>(2,
            nullptr,
            new DoubleLinkedList<int>(5)));
    two_next.next->prev = &two_next;
    two_next.next->next->prev = two_next.next;

    DoubleLinkedList<int> two_next_copy(two_next);
    result &= two_next_copy.data == two_next.data;
    result &= !two_next_copy.prev;
    result &= two_next_copy.next->data == two_next.next->data;
    result &= two_next_copy.next->prev == &two_next_copy;

    return result;
}

bool doubleLinkedListTestAssignmentOperator() {
    bool result = true;

    DoubleLinkedList<int> original(4,
        nullptr,
        new DoubleLinkedList<int>(3, 
            nullptr,
            new DoubleLinkedList<int>(5)));
    original.next->prev = &original;
    original.next->next->prev = original.next;
    DoubleLinkedList<int> assigned = original;
    result &= assigned.data == original.data;
    result &= assigned.next->data == original.next->data;
    result &= assigned.next->prev->data == original.next->prev->data;
    result &= assigned.next->next->data == original.next->next->data;
    result &= assigned.next->next->prev->data 
              == original.next->next->prev->data;

    return result;
}

bool doubleLinkedListTestEqualityOperator() {
    bool result = true;

    DoubleLinkedList<int>* unequal_lhs = new DoubleLinkedList<int>(3);
    DoubleLinkedList<int>* unequal_rhs = new DoubleLinkedList<int>(4);
    result &= !(*unequal_lhs == *unequal_rhs);
    delete unequal_lhs;
    delete unequal_rhs;

    DoubleLinkedList<int>* lhs_too_big = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4,
            nullptr,
            new DoubleLinkedList<int>(5)));
    DoubleLinkedList<int>* rhs_too_small = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4));
    result &= !(*lhs_too_big == *rhs_too_small);
    delete lhs_too_big;
    delete rhs_too_small;

    DoubleLinkedList<int>* lhs_too_small = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4));
    DoubleLinkedList<int>* rhs_too_big = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4,
            nullptr,
            new DoubleLinkedList<int>(5)));
    result &= !(*lhs_too_small == *rhs_too_big);
    delete lhs_too_small;
    delete rhs_too_big;

    DoubleLinkedList<int>* equal_lhs = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4));
    DoubleLinkedList<int>* equal_rhs = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(4));
    result &= *equal_lhs == *equal_rhs;
    delete equal_lhs;
    delete equal_rhs;

    return result;
}

bool doubleLinkedListTestInsertPrev() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    doubleLinkedListInsertPrev(&empty, 2);
    result &= empty->data == 2;
    result &= !empty->prev;
    result &= !empty->next;
    delete empty;

    DoubleLinkedList<int>* no_prev = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertPrev(&no_prev, 4);
    result &= no_prev->prev->data == 4;
    result &= no_prev->prev->next == no_prev;
    no_prev = no_prev->prev;
    delete no_prev;

    DoubleLinkedList<int>* has_prev = new DoubleLinkedList<int>(3,
        new DoubleLinkedList<int>(2),
        nullptr);
    DoubleLinkedList<int>* original_prev = has_prev->prev;
    doubleLinkedListInsertPrev(&has_prev, 1);
    result &= has_prev->prev->data == 1;
    result &= has_prev->prev->prev == original_prev;
    result &= has_prev->prev->next == has_prev;
    has_prev = has_prev->prev->prev;
    delete has_prev;

    return result;
}

bool doubleLinkedListTestInsertNext() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    doubleLinkedListInsertNext(&empty, 2);
    result &= empty->data == 2;
    result &= !empty->prev;
    result &= !empty->next;
    delete empty;

    DoubleLinkedList<int>* no_next = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertNext(&no_next, 4);
    result &= no_next->next->data == 4;
    result &= no_next->next->prev == no_next;
    delete no_next;

    DoubleLinkedList<int>* has_next = new DoubleLinkedList<int>(3,
        nullptr,
        new DoubleLinkedList<int>(5));
    DoubleLinkedList<int>* original_next = has_next->next;
    doubleLinkedListInsertNext(&has_next, 6);
    result &= has_next->next->data == 6;
    result &= has_next->next->next == original_next;
    result &= has_next->next->prev == has_next;
    delete has_next;

    return result;
}

bool doubleLinkedListTestGetHead() {
    bool result = true;

    DoubleLinkedList<int>* has_prev = new DoubleLinkedList<int>(4,
        new DoubleLinkedList<int>(2),
        nullptr);
    result &= doubleLinkedListGetHead(&has_prev) == has_prev->prev;
    has_prev = has_prev->prev;
    delete has_prev;

    return result;
}

bool doubleLinkedListTestGetTail() {
    bool result = true;

    DoubleLinkedList<int>* has_next = new DoubleLinkedList<int>(4,
        nullptr,
        new DoubleLinkedList<int>(2));
    result &= doubleLinkedListGetTail(&has_next) == has_next->next;
    delete has_next;

    return result;
}

bool doubleLinkedListTestInsertAtHead() {
    bool result = true;

    DoubleLinkedList<int> *at_head = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&at_head, 2);
    result &= at_head->prev->data == 2;
    result &= !at_head->prev->prev;
    result &= at_head->prev->next == at_head;
    at_head = at_head->prev; // need to delete from beginning
    delete at_head;

    DoubleLinkedList<int> *not_at_head = new DoubleLinkedList<int>(4,
        new DoubleLinkedList<int>(3),
        nullptr);
    doubleLinkedListInsertAtHead(&not_at_head, 2);
    result &= not_at_head->prev->prev->data == 2;
    result &= !not_at_head->prev->prev->prev;
    result &= not_at_head->prev->prev->next == not_at_head->prev;
    not_at_head = not_at_head->prev->prev; // need to delete from beginning
    delete not_at_head;

    return result;
}

bool doubleLinkedListTestInsertAtTail() {
    bool result = true;

    DoubleLinkedList<int> *at_tail = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&at_tail, 2);
    result &= at_tail->next->data == 2;
    result &= !at_tail->next->next;
    result &= at_tail->next->prev == at_tail;
    delete at_tail;

    DoubleLinkedList<int> *not_at_tail = new DoubleLinkedList<int>(4,
        nullptr,
        new DoubleLinkedList<int>(3));
    doubleLinkedListInsertAtTail(&not_at_tail, 2);
    result &= not_at_tail->next->next->data == 2;
    result &= !not_at_tail->next->next->next;
    result &= not_at_tail->next->next->prev == not_at_tail->next;
    delete not_at_tail;

    return result;
}

void doubleLinkedListTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("double linked list");
    testGroupAddTest(&test_group, UnitTest("default constructor", 
        doubleLinkedListTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor",
        doubleLinkedListTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("full constructor",
        doubleLinkedListTestFullConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor",
        doubleLinkedListTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator",
        doubleLinkedListTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator",
        doubleLinkedListTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("insert prev",
        doubleLinkedListTestInsertPrev));
    testGroupAddTest(&test_group, UnitTest("insert next",
        doubleLinkedListTestInsertNext));
    testGroupAddTest(&test_group, UnitTest("get head",
        doubleLinkedListTestGetHead));
    testGroupAddTest(&test_group, UnitTest("get tail",
        doubleLinkedListTestGetTail));
    testGroupAddTest(&test_group, UnitTest("insert at head",
        doubleLinkedListTestInsertAtHead));
    testGroupAddTest(&test_group, UnitTest("insert at tail",
        doubleLinkedListTestInsertAtTail));
    test_manager->test_groups.push_back(test_group);
}
