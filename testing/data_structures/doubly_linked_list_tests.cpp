#include "doubly_linked_list_tests.hpp"

#include <data_structures/doubly_linked_list.tpp>

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

    std::cout << (result ? "true" : "false") << std::endl;

    DoublyLinkedList<int>* non_empty = new DoublyLinkedList<int>(3);
    doublyLinkedListInsertNext(non_empty, 4);
    result &= (non_empty->next->data == 4);
    delete non_empty;

    std::cout << (result ? "true" : "false") << std::endl;

    return result;
}

TestGroup doublyLinkedListRegisterTests() {
    TestGroup test_group("doubly linked lists");
    test_group.addTest(UnitTest(doublyLinkedListTestInsertPrev, "insert previous"));
    test_group.addTest(UnitTest(doublyLinkedListTestInsertNext, "insert next"));
    return test_group;
}