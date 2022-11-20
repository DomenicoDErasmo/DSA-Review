#include "linked_list_tests.hpp"

#include <data_structures/linked_list.cpp>
#include <iostream>
#include <sstream>

bool linkedListTestToString() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    head->next = new LinkedList<int>(6);
    result &= (head->to_string() == "4, 6");
    delete head;

    return result;
}

bool linkedListTestOstreamOperator() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    head->next = new LinkedList<int>(6);

    std::stringstream out;
    out << *head;
    result &= (out.str() == "4, 6");
    delete head;

    return result;
}

bool linkedListTestEqualityOperator() {
    bool result = true;

    LinkedList<int>* rhs = new LinkedList<int>(0);
    for (int i = 1; i < 3; i++) {
        linkedListInsertAtTail(rhs, i);
    }

    LinkedList<int>* too_small = new LinkedList<int>(0);
    result &= (*too_small != *rhs);

    LinkedList<int>* too_big = new LinkedList<int>(0);
    for (int i = 1; i < 4; i++) {
        linkedListInsertAtTail(too_big, i);
    }
    result &= (*too_big != *rhs);

    LinkedList<int>* unequal_value = new LinkedList<int>(0);
    linkedListInsertAtTail(unequal_value, 1);
    linkedListInsertAtTail(unequal_value, 2);
    linkedListInsertAtTail(unequal_value, 1);
    result &= (*unequal_value != *rhs);

    LinkedList<int>* equals = new LinkedList<int>(0);
    for (int i = 1; i < 3; i++) {
        linkedListInsertAtTail(equals, i);
    }
    result &= (*equals == *rhs);

    delete equals;
    delete unequal_value;
    delete too_big;
    delete too_small;
    delete rhs;
    return result;
}

bool linkedListTestInsertAtHead() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    result &= (head->data == 4);
    linkedListInsertAtHead(head, 5);
    result &= (head->data == 5);

    delete head;
    return result;
}

bool linkedListTestInsertAtTail() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    result &= (head->data == 4);
    linkedListInsertAtTail(head, 6);
    result &= (head->next->data == 6);

    delete head;
    return result;
}

bool linkedListTestGetSize() {
    bool result = true;

    LinkedList<int>* empty = nullptr;
    result &= (linkedListGetSize(empty) == 0);

    LinkedList<int>* head = new LinkedList<int>(4);
    linkedListInsertAtHead(head, 3);
    linkedListInsertAtHead(head, 2);
    result &= (linkedListGetSize(head) == 3);

    delete head;
    return result;
}

bool linkedListTestGetMiddle() {
    bool result = true;

    LinkedList<int>* odd_size_list = new LinkedList<int>(4);
    for (int i = 3; i > 1; i--) {
        linkedListInsertAtHead(odd_size_list, i);
    }
    result &= (linkedListGetMiddle(odd_size_list) == 3);
    
    LinkedList<int>* even_size_list = new LinkedList<int>(1, odd_size_list);
    result &= (linkedListGetMiddle(even_size_list) == 3);

    delete even_size_list;
    return result;
}

bool testGetNodeAtIndex() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(0);
    for (int i = 1; i < 4; i++) {
        linkedListInsertAtTail(head, i);
    }

    LinkedList<int>* node_index_1 = linkedListGetNodeAtIndex(head, 1);
    result &= (node_index_1 == head->next);
    
    LinkedList<int>* out_of_bounds = linkedListGetNodeAtIndex(head, 5);
    result &= (!out_of_bounds);

    delete head;
    return result;
}

bool testFindNthOccurrence() {
    bool result = true;

    LinkedList<int>* not_in_list = new LinkedList<int>(0);
    result &= (linkedListFindNthOccurrence(not_in_list, 1, 1) == -1);

    LinkedList<int>* not_enough_found = new LinkedList<int>(2);
    linkedListInsertAtHead(not_enough_found, 4);
    linkedListInsertAtHead(not_enough_found, 3);
    linkedListInsertAtHead(not_enough_found, 4);
    result &= (linkedListFindNthOccurrence(not_enough_found, 4, 3) == -1);

    LinkedList<int>* found = new LinkedList<int>(4);
    linkedListInsertAtHead(found, 2);
    linkedListInsertAtHead(found, 3);
    linkedListInsertAtHead(found, 4);
    result &= (linkedListFindNthOccurrence(found, 4, 2) == 3);

    delete not_in_list;
    delete not_enough_found;
    delete found;
    return result;
}

// TODO: make new test case: delete head, delete head next, delete something in middle, delete last
bool testDeleteNodeAtIndex() {
    bool result = true;

    LinkedList<int>* empty = nullptr;
    linkedListDeleteNodeAtIndex(empty, 1);
    result &= !empty;

    LinkedList<int>* delete_first = new LinkedList<int>(4);
    linkedListInsertAtTail(delete_first, 5);
    linkedListDeleteNodeAtIndex(delete_first, 0);
    result &= (delete_first->data == 5);

    LinkedList<int>* delete_second = new LinkedList<int>(4);
    linkedListInsertAtTail(delete_second, 5);
    linkedListInsertAtTail(delete_second, 6);
    linkedListDeleteNodeAtIndex(delete_second, 1);
    result &= (delete_second->data == 4);
    result &= (delete_second->next->data == 6);


    return result;
}

bool testDeleteNthOccurrence() {
    bool result = true;

    LinkedList<int>* not_in_list = new LinkedList<int>(0);
    linkedListInsertAtHead(not_in_list, 2);
    int original_size = linkedListGetSize(not_in_list);
    linkedListDeleteNthOccurrence(not_in_list, 3, 1);
    result &= (linkedListGetSize(not_in_list) == original_size);

    LinkedList<int>* not_enough_found = new LinkedList<int>(2);
    linkedListInsertAtHead(not_enough_found, 4);
    linkedListInsertAtHead(not_enough_found, 3);
    linkedListInsertAtHead(not_enough_found, 4);
    original_size = linkedListGetSize(not_enough_found);
    linkedListDeleteNthOccurrence(not_enough_found, 4, 3);
    result &= (linkedListGetSize(not_enough_found) == original_size);

    LinkedList<int>* found = new LinkedList<int>(4);
    linkedListInsertAtHead(found, 2);
    linkedListInsertAtHead(found, 3);
    linkedListInsertAtHead(found, 4);
    original_size = linkedListGetSize(found);
    linkedListDeleteNthOccurrence(found, 4, 2);
    result &= (linkedListGetSize(found) == original_size - 1);

    delete not_in_list;
    delete not_enough_found;
    delete found;
    return result;
}

bool testReverse() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(0);
    for (int i = 1; i < 4; i++) {
        linkedListInsertAtTail(head, i);
    }
    linkedListReverse(head);

    LinkedList<int>* reverse = new LinkedList<int>(3);
    for (int i = 2; i >= 0; i--) {
        linkedListInsertAtTail(head, i);
    }

    linkedListReverse(head);
    result &= (head == reverse);

    return result;
}

TestGroup linkedListRegisterTests() {
    TestGroup test_group("linked lists");
    test_group.addTest(UnitTest(linkedListTestToString, "to string"));
    test_group.addTest(UnitTest(linkedListTestOstreamOperator, "ostream operator"));
    test_group.addTest(UnitTest(linkedListTestEqualityOperator, "equality operator"));
    test_group.addTest(UnitTest(linkedListTestInsertAtHead, "insert at head"));
    test_group.addTest(UnitTest(linkedListTestInsertAtTail, "insert at tail"));
    test_group.addTest(UnitTest(linkedListTestGetSize, "get size"));
    test_group.addTest(UnitTest(linkedListTestGetMiddle, "get middle"));
    test_group.addTest(UnitTest(testGetNodeAtIndex, "get node at index"));
    test_group.addTest(UnitTest(testFindNthOccurrence, "find nth occurrence"));
    test_group.addTest(UnitTest(testDeleteNodeAtIndex, "delete node at index"));
    test_group.addTest(UnitTest(testDeleteNthOccurrence, "delete nth occurrence"));
    test_group.addTest(UnitTest(testReverse, "reverse"));
    return test_group;
}