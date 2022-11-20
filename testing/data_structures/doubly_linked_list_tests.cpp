#include "doubly_linked_list_tests.hpp"

#include <data_structures/doubly_linked_list.cpp>
#include <sstream>

bool doublyLinkedListTestInsertPrev() {
    bool result = true;

    DoublyLinkedList<int>* empty = nullptr;
    doublyLinkedListInsertPrev(empty, 4);
    result &= (empty->data == 4);
    delete empty;

    DoublyLinkedList<int>* non_empty = new DoublyLinkedList<int>(3);
    doublyLinkedListInsertPrev(non_empty, 4);
    result &= (non_empty->prev->data == 4);
    delete non_empty;

    return result;
}

bool doublyLinkedListTestInsertNext() {
    bool result = true;

    DoublyLinkedList<int>* empty = nullptr;
    doublyLinkedListInsertNext(empty, 4);
    result &= (empty->data == 4);
    delete empty;

    DoublyLinkedList<int>* non_empty = new DoublyLinkedList<int>(3);
    doublyLinkedListInsertNext(non_empty, 4);
    result &= (non_empty->next->data == 4);
    delete non_empty;

    return result;
}

bool doublyLinkedListTestDeleteNode() {
    bool result = true;

    DoublyLinkedList<int>* delete_head = new DoublyLinkedList<int>(5);
    doublyLinkedListDeleteNode(delete_head, delete_head);
    result &= !delete_head;

    DoublyLinkedList<int>* delete_next = new DoublyLinkedList<int>(4);
    doublyLinkedListInsertNext(delete_next, 3);
    doublyLinkedListDeleteNode(delete_next, delete_next->next);
    result &= (!delete_next->next);

    return result;
}

bool doublyLinkedListTestToString() {
    bool result = true;

    DoublyLinkedList<int>* head = new DoublyLinkedList<int>(4);
    doublyLinkedListInsertNext(head, 6);
    doublyLinkedListInsertNext(head, 2);
    result &= (head->to_string() == "4 <-> 2 <-> 6");
    delete head;

    return result;
}

bool doublyLinkedListTestOstreamOperator() {
    bool result = true;

    DoublyLinkedList<int>* head = new DoublyLinkedList<int>(4);
    doublyLinkedListInsertNext(head, 6);
    doublyLinkedListInsertNext(head, 2);
    std::stringstream out;
    out << *head;
    result &= (out.str() == "4 <-> 2 <-> 6");
    delete head;

    return result;
}

bool doublyLinkedListTestEqualityOperator() {
    bool result = true;

    DoublyLinkedList<int>* rhs = new DoublyLinkedList<int>(0);
    for (int i = 1; i < 3; i++) {
        doublyLinkedListInsertNext(rhs, i);
    }

    DoublyLinkedList<int>* too_small = new DoublyLinkedList<int>(0);
    result &= (*too_small != *rhs);
    delete too_small;

    DoublyLinkedList<int>* too_big = new DoublyLinkedList<int>(0);
    for (int i = 1; i < 4; i++) {
        doublyLinkedListInsertNext(too_big, i);
    }
    result &= (*too_big != *rhs);
    delete too_big;

    DoublyLinkedList<int>* unequal_value = new DoublyLinkedList<int>(0);
    doublyLinkedListInsertNext(unequal_value, 1);
    doublyLinkedListInsertNext(unequal_value, 2);
    doublyLinkedListInsertNext(unequal_value, 1);
    result &= (*unequal_value != *rhs);
    delete unequal_value;

    DoublyLinkedList<int>* equals = new DoublyLinkedList<int>(0);
    for (int i = 1; i < 3; i++) {
        doublyLinkedListInsertNext(equals, i);
    }
    result &= (*equals == *rhs);
    delete equals;

    delete rhs;
    return result;
}

TestGroup doublyLinkedListRegisterTests() {
    TestGroup test_group("doubly linked lists");
    test_group.addTest(UnitTest(doublyLinkedListTestInsertPrev, "insert previous"));
    test_group.addTest(UnitTest(doublyLinkedListTestInsertNext, "insert next"));
    test_group.addTest(UnitTest(doublyLinkedListTestDeleteNode, "delete node"));
    test_group.addTest(UnitTest(doublyLinkedListTestToString, "to string"));
    test_group.addTest(UnitTest(doublyLinkedListTestOstreamOperator, "ostream operator"));
    test_group.addTest(UnitTest(doublyLinkedListTestEqualityOperator, "equality operator"));
    return test_group;
}