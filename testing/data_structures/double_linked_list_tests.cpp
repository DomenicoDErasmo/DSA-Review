#include "double_linked_list_tests.hpp"
#include <data_structures/double_linked_list.cpp>

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

    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetHead(&empty);

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
    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetTail(&empty);

    DoubleLinkedList<int>* has_next = new DoubleLinkedList<int>(4,
        nullptr,
        new DoubleLinkedList<int>(2));
    result &= doubleLinkedListGetTail(&has_next) == has_next->next;
    delete has_next;

    return result;
}

bool doubleLinkedListTestGetFromForwardPosition() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetFromForwardPosition(&empty, 1);

    DoubleLinkedList<int>* list_too_small = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&list_too_small, 6);
    doubleLinkedListInsertAtTail(&list_too_small, 4);
    result &= !doubleLinkedListGetFromForwardPosition(&list_too_small, 4);
    delete list_too_small;

    DoubleLinkedList<int>* big_enough = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&big_enough, 6);
    doubleLinkedListInsertAtTail(&big_enough, 4);
    result &= doubleLinkedListGetFromForwardPosition(
        &big_enough, 
        2) == big_enough->next->next;
    delete big_enough;

    return result;
}

bool doubleLinkedListTestGetFromBackwardPosition() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetFromBackwardPosition(&empty, 1);

    DoubleLinkedList<int>* list_too_small = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&list_too_small, 6);
    doubleLinkedListInsertAtHead(&list_too_small, 4);
    result &= !doubleLinkedListGetFromBackwardPosition(&list_too_small, 4);
    delete list_too_small;

    DoubleLinkedList<int>* big_enough = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&big_enough, 6);
    doubleLinkedListInsertAtHead(&big_enough, 4);
    result &= doubleLinkedListGetFromBackwardPosition(
        &big_enough, 
        2) == big_enough->prev->prev;
    big_enough = big_enough->prev->prev;
    delete big_enough;

    return result;
}

bool doubleLinkedListTestDeleteFromForwardPosition() {
    bool result = true;

    DoubleLinkedList<int>* invalid_n = nullptr;
    doubleLinkedListDeleteFromForwardPosition(&invalid_n, -1);
    result &= !invalid_n;

    DoubleLinkedList<int>* empty = nullptr;
    doubleLinkedListDeleteFromForwardPosition(&empty, 0);
    result &= !empty;

    DoubleLinkedList<int>* delete_head_when_not_node = 
        new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&delete_head_when_not_node, 2);
    doubleLinkedListDeleteFromForwardPosition(&delete_head_when_not_node, 0);
    result &= !delete_head_when_not_node->prev;
    delete delete_head_when_not_node;

    DoubleLinkedList<int>* delete_head_when_node = new DoubleLinkedList<int>(4);
    doubleLinkedListDeleteFromForwardPosition(&delete_head_when_node, 0);
    result &= !delete_head_when_node;

    DoubleLinkedList<int>* delete_head_when_next = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&delete_head_when_next, 2);
    doubleLinkedListDeleteFromForwardPosition(&delete_head_when_next, 0);
    result &= delete_head_when_next->data == 2;
    result &= !delete_head_when_next->prev;
    delete delete_head_when_next;

    DoubleLinkedList<int>* too_small = new DoubleLinkedList<int>(4);
    doubleLinkedListDeleteFromForwardPosition(
        &too_small, 
        doubleLinkedListGetLength(too_small) + 1);
    result &= too_small->data == 4;
    result &= !too_small->prev;
    result &= !too_small->next;
    delete too_small;

    DoubleLinkedList<int>* delete_when_not_node = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&delete_when_not_node, 2);
    doubleLinkedListDeleteFromForwardPosition(&delete_when_not_node, 1);
    result &= delete_when_not_node->data == 4;
    result &= !delete_when_not_node->prev;
    result &= !delete_when_not_node->next;
    delete delete_when_not_node;

    DoubleLinkedList<int>* delete_when_node = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&delete_when_node, 2);
    doubleLinkedListDeleteFromForwardPosition(&delete_when_node, 1);
    result &= delete_when_node->data == 2;
    result &= !delete_when_node->prev;
    result &= !delete_when_node->next;
    delete delete_when_node;

    DoubleLinkedList<int>* delete_when_next = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&delete_when_next, 2);
    doubleLinkedListInsertAtTail(&delete_when_next, 3);
    doubleLinkedListDeleteFromForwardPosition(&delete_when_next, 1);
    result &= delete_when_next->data == 4;
    result &= !delete_when_next->prev;
    result &= delete_when_next->next->data == 3;
    delete delete_when_next;

    return result;
}

bool doubleLinkedListTestDeleteFromBackwardPosition() {
    bool result = true;

    DoubleLinkedList<int>* invalid_n = nullptr;
    doubleLinkedListDeleteFromBackwardPosition(&invalid_n, -1);
    result &= !invalid_n;

    DoubleLinkedList<int>* empty = nullptr;
    doubleLinkedListDeleteFromBackwardPosition(&empty, 0);
    result &= !empty;

    DoubleLinkedList<int>* delete_tail_when_not_node = 
        new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&delete_tail_when_not_node, 2);
    doubleLinkedListDeleteFromBackwardPosition(&delete_tail_when_not_node, 0);
    result &= !delete_tail_when_not_node->prev;
    delete delete_tail_when_not_node;

    DoubleLinkedList<int>* delete_tail_when_node = new DoubleLinkedList<int>(4);
    doubleLinkedListDeleteFromBackwardPosition(&delete_tail_when_node, 0);
    result &= !delete_tail_when_node;

    DoubleLinkedList<int>* delete_tail_when_prev = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&delete_tail_when_prev, 2);
    doubleLinkedListDeleteFromBackwardPosition(&delete_tail_when_prev, 0);
    result &= delete_tail_when_prev->data == 2;
    result &= !delete_tail_when_prev->next;
    delete delete_tail_when_prev;

    DoubleLinkedList<int>* too_small = new DoubleLinkedList<int>(4);
    doubleLinkedListDeleteFromBackwardPosition(
        &too_small, 
        doubleLinkedListGetLength(too_small) + 1);
    result &= too_small->data == 4;
    result &= !too_small->prev;
    result &= !too_small->next;
    delete too_small;

    DoubleLinkedList<int>* delete_when_not_node = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&delete_when_not_node, 2);
    doubleLinkedListDeleteFromBackwardPosition(&delete_when_not_node, 1);
    result &= delete_when_not_node->data == 4;
    result &= !delete_when_not_node->prev;
    result &= !delete_when_not_node->next;
    delete delete_when_not_node;

    DoubleLinkedList<int>* delete_when_node = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&delete_when_node, 2);
    doubleLinkedListDeleteFromBackwardPosition(&delete_when_node, 1);
    result &= delete_when_node->data == 2;
    result &= !delete_when_node->prev;
    result &= !delete_when_node->next;
    delete delete_when_node;

    DoubleLinkedList<int>* delete_when_prev = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&delete_when_prev, 2);
    doubleLinkedListInsertAtHead(&delete_when_prev, 3);
    doubleLinkedListDeleteFromBackwardPosition(&delete_when_prev, 1);
    result &= delete_when_prev->data == 4;
    result &= !delete_when_prev->next;
    result &= delete_when_prev->prev->data == 3;
    delete_when_prev = delete_when_prev->prev;
    delete delete_when_prev;

    return result;
}

bool doubleLinkedListTestInsertAtHead() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    doubleLinkedListInsertAtHead(&empty, 4);
    result &= empty->data == 4;
    delete empty;

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

bool doubleLinkedListTestGetLength() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    result &= doubleLinkedListGetLength(empty) == 0;

    DoubleLinkedList<int>* single_element = new DoubleLinkedList<int>(4);
    result &= doubleLinkedListGetLength(single_element) == 1;
    delete single_element;

    DoubleLinkedList<int>* multiple_elements = new DoubleLinkedList<int>(5);
    doubleLinkedListInsertAtTail(&multiple_elements, 6);
    result &= doubleLinkedListGetLength(multiple_elements) == 2;
    delete multiple_elements;

    DoubleLinkedList<int>* not_at_head = new DoubleLinkedList<int>(5);
    doubleLinkedListInsertAtHead(&not_at_head, 3);
    result &= doubleLinkedListGetLength(not_at_head) == 2;
    delete not_at_head;

    return result;
}

bool doubleLinkedListTestGetForwardPositionOfNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(4);
    result &= doubleLinkedListGetForwardPositionOfNthOccurrence(
        not_found, 
        5, 
        1) == -1;
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&not_enough, 5);
    doubleLinkedListInsertAtTail(&not_enough, 6);
    result &= doubleLinkedListGetForwardPositionOfNthOccurrence(
        not_enough,
        4,
        2) == -1;
    delete not_enough;

    DoubleLinkedList<int>* found_for_one = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&found_for_one, 5);
    doubleLinkedListInsertAtTail(&found_for_one, 6);
    result &= doubleLinkedListGetForwardPositionOfNthOccurrence(
        found_for_one,
        4,
        1) == 0;
    delete found_for_one;

    DoubleLinkedList<int>* found_for_multiple = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&found_for_multiple, 5);
    doubleLinkedListInsertAtTail(&found_for_multiple, 4);
    doubleLinkedListInsertAtTail(&found_for_multiple, 4);
    result &= doubleLinkedListGetForwardPositionOfNthOccurrence(
        found_for_multiple,
        4,
        2) == 2;
    delete found_for_multiple;

    return result;
}

bool doubleLinkedListTestGetBackwardPositionOfNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(4);
    result &= doubleLinkedListGetBackwardPositionOfNthOccurrence(
        not_found, 
        5, 
        1) == -1;
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&not_enough, 5);
    doubleLinkedListInsertAtHead(&not_enough, 6);
    result &= doubleLinkedListGetBackwardPositionOfNthOccurrence(
        not_enough,
        4,
        2) == -1;
    delete not_enough;

    DoubleLinkedList<int>* found_for_one = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&found_for_one, 5);
    doubleLinkedListInsertAtHead(&found_for_one, 6);
    result &= doubleLinkedListGetBackwardPositionOfNthOccurrence(
        found_for_one,
        4,
        1) == 0;
    delete found_for_one;

    DoubleLinkedList<int>* found_for_multiple = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&found_for_multiple, 5);
    doubleLinkedListInsertAtHead(&found_for_multiple, 4);
    doubleLinkedListInsertAtHead(&found_for_multiple, 4);
    result &= doubleLinkedListGetBackwardPositionOfNthOccurrence(
        found_for_multiple,
        4,
        2) == 2;
    delete found_for_multiple;

    return result;
}

bool doubleLinkedListTestGetForwardNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetForwardNthOccurrence(&empty, 5, 2);

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&not_found, 5);
    doubleLinkedListInsertAtTail(&not_found, 6);
    result &= !doubleLinkedListGetForwardNthOccurrence(&not_found, 7, 1);
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&not_enough, 5);
    doubleLinkedListInsertAtTail(&not_enough, 6);
    result &= !doubleLinkedListGetForwardNthOccurrence(&not_enough, 6, 2);
    delete not_enough;

    DoubleLinkedList<int>* found = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtTail(&found, 5);
    doubleLinkedListInsertAtTail(&found, 6);
    result &= doubleLinkedListGetForwardNthOccurrence(
        &found, 
        6, 
        1) == found->next->next;
    delete found;

    DoubleLinkedList<int>* not_at_head = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&not_at_head, 2);
    doubleLinkedListInsertAtHead(&not_at_head, 2);
    doubleLinkedListInsertAtHead(&not_at_head, 3);
    result &= doubleLinkedListGetForwardNthOccurrence(
        &not_at_head,
        3,
        2) == not_at_head;
    not_at_head = not_at_head->prev->prev->prev;
    delete not_at_head;

    return result;
}

bool doubleLinkedListTestGetBackwardNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* empty = nullptr;
    result &= !doubleLinkedListGetBackwardNthOccurrence(&empty, 5, 2);

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&not_found, 5);
    doubleLinkedListInsertAtHead(&not_found, 6);
    result &= !doubleLinkedListGetBackwardNthOccurrence(&not_found, 7, 1);
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&not_enough, 5);
    doubleLinkedListInsertAtHead(&not_enough, 6);
    result &= !doubleLinkedListGetBackwardNthOccurrence(&not_enough, 6, 2);
    delete not_enough;

    DoubleLinkedList<int>* found = new DoubleLinkedList<int>(4);
    doubleLinkedListInsertAtHead(&found, 5);
    doubleLinkedListInsertAtHead(&found, 6);
    result &= doubleLinkedListGetBackwardNthOccurrence(
        &found, 
        6, 
        1) == found->prev->prev;
    delete found;

    DoubleLinkedList<int>* not_at_tail = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&not_at_tail, 2);
    doubleLinkedListInsertAtTail(&not_at_tail, 2);
    doubleLinkedListInsertAtTail(&not_at_tail, 3);
    result &= doubleLinkedListGetBackwardNthOccurrence(
        &not_at_tail,
        3,
        2) == not_at_tail;
    delete not_at_tail;

    return result;
}

bool doubleLinkedListTestDeleteForwardNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* empty =  nullptr;
    doubleLinkedListDeleteForwardNthOccurrence(&empty, 0, 1);
    result &= !empty;

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&not_found, 4);
    doubleLinkedListInsertAtTail(&not_found, 5);
    doubleLinkedListDeleteForwardNthOccurrence(&not_found, 6, 1);
    result &= doubleLinkedListGetLength(not_found) == 3;
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&not_enough, 4);
    doubleLinkedListInsertAtTail(&not_enough, 5);
    doubleLinkedListDeleteForwardNthOccurrence(&not_enough, 5, 2);
    result &= doubleLinkedListGetLength(not_enough) == 3;
    delete not_enough;

    DoubleLinkedList<int>* delete_first_instance = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&delete_first_instance, 4);
    doubleLinkedListInsertAtTail(&delete_first_instance, 5);
    doubleLinkedListDeleteForwardNthOccurrence(&delete_first_instance, 4, 1);
    result &= delete_first_instance->next->data == 5;
    delete delete_first_instance;

    DoubleLinkedList<int>* delete_not_first_instance = 
        new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtTail(&delete_not_first_instance, 4);
    doubleLinkedListInsertAtTail(&delete_not_first_instance, 4);
    doubleLinkedListInsertAtTail(&delete_not_first_instance, 5);
    doubleLinkedListDeleteForwardNthOccurrence(
        &delete_not_first_instance, 
        4, 
        2);
    result &= delete_not_first_instance->next->next->data == 5;
    delete delete_not_first_instance;

    return result;
}

bool doubleLinkedListTestDeleteBackwardNthOccurrence() {
    bool result = true;

    DoubleLinkedList<int>* empty =  nullptr;
    doubleLinkedListDeleteBackwardNthOccurrence(&empty, 0, 1);
    result &= !empty;

    DoubleLinkedList<int>* not_found = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&not_found, 4);
    doubleLinkedListInsertAtHead(&not_found, 5);
    doubleLinkedListDeleteBackwardNthOccurrence(&not_found, 6, 1);
    result &= doubleLinkedListGetLength(not_found) == 3;
    delete not_found;

    DoubleLinkedList<int>* not_enough = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&not_enough, 4);
    doubleLinkedListInsertAtHead(&not_enough, 5);
    doubleLinkedListDeleteBackwardNthOccurrence(&not_enough, 5, 2);
    result &= doubleLinkedListGetLength(not_enough) == 3;
    delete not_enough;

    DoubleLinkedList<int>* delete_first_instance = new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&delete_first_instance, 4);
    doubleLinkedListInsertAtHead(&delete_first_instance, 5);
    doubleLinkedListDeleteBackwardNthOccurrence(&delete_first_instance, 4, 1);
    result &= delete_first_instance->prev->data == 5;
    delete delete_first_instance;

    DoubleLinkedList<int>* delete_not_first_instance = 
        new DoubleLinkedList<int>(3);
    doubleLinkedListInsertAtHead(&delete_not_first_instance, 4);
    doubleLinkedListInsertAtHead(&delete_not_first_instance, 4);
    doubleLinkedListInsertAtHead(&delete_not_first_instance, 5);
    doubleLinkedListDeleteBackwardNthOccurrence(
        &delete_not_first_instance, 
        4, 
        2);
    result &= delete_not_first_instance->prev->prev->data == 5;
    delete delete_not_first_instance;

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
    testGroupAddTest(&test_group, UnitTest("get forward position",
        doubleLinkedListTestGetFromForwardPosition));
    testGroupAddTest(&test_group, UnitTest("get backward position",
        doubleLinkedListTestGetFromBackwardPosition));
    testGroupAddTest(&test_group, UnitTest("delete from forward position",
        doubleLinkedListTestDeleteFromForwardPosition));
    testGroupAddTest(&test_group, UnitTest("delete from backward position",
        doubleLinkedListTestDeleteFromBackwardPosition));
    testGroupAddTest(&test_group, UnitTest("insert at head",
        doubleLinkedListTestInsertAtHead));
    testGroupAddTest(&test_group, UnitTest("insert at tail",
        doubleLinkedListTestInsertAtTail));
    testGroupAddTest(&test_group, UnitTest("get length",
        doubleLinkedListTestGetLength));
    testGroupAddTest(&test_group, UnitTest(
        "get forward position of nth occurrence", 
        doubleLinkedListTestGetForwardPositionOfNthOccurrence));
    testGroupAddTest(&test_group, UnitTest(
        "get backward position of nth occurrence", 
        doubleLinkedListTestGetBackwardPositionOfNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("get forward nth occurrence", 
        doubleLinkedListTestGetForwardNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("get backward nth occurrence", 
        doubleLinkedListTestGetBackwardNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("delete forward nth occurrence",
        doubleLinkedListTestDeleteForwardNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("delete backward nth occurrence",
        doubleLinkedListTestDeleteBackwardNthOccurrence));
    testManagerAddTestGroup(test_manager, test_group);
}
