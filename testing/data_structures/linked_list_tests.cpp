#include "linked_list_tests.hpp"

#include <data_structures/linked_list.tpp>
#include <iostream>
#include <sstream>

bool testDefaultConstructor() {
    bool result = true;

    LinkedList<int> list;
    result &= (list.getData() == 0);
    result &= (!list.getNext());

    return result;
}

bool testDataConstructor() {
    bool result = true;

    LinkedList<int> list(4);
    result &= (list.getData() == 4);
    result &= (!list.getNext());

    return result;
}

bool testFullConstructor() {
    bool result = true;

    LinkedList<int> next(5);
    LinkedList<int> list(4, &next);

    result &= (list.getData() == 4);
    result &= (list.getNext() == &next);

    return result;
}

bool testCopyConstructor() {
    bool result = true;

    LinkedList<int> next(7);
    LinkedList<int> original(5, &next);
    LinkedList<int> list(original);

    result &= (list.getData() == original.getData());
    result &= (list.getNext() == original.getNext());

    return result;
}

bool testDestructor() {
    try {
        LinkedList<int>* head = new LinkedList<int>(4);
        head->setNext(new LinkedList<int>(4));
        delete head;
        return true;
    } catch (...) {
        return false;
    }
}

bool testToString() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    head->setNext(new LinkedList<int>(6));
    result &= (head->toString() == "4, 6");
    delete head;

    return result;
}

bool testOstreamOperator() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    head->setNext(new LinkedList<int>(6));

    std::stringstream out;
    out << *head;
    result &= (out.str() == "4, 6");
    delete head;

    return result;
}

bool testInsertAtHead() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    result &= (head->getData() == 4);
    linkedListInsertAtHead(head, 5);
    result &= (head->getData() == 5);

    delete head;
    return result;
}

bool testInsertAtTail() {
    bool result = true;

    LinkedList<int>* head = new LinkedList<int>(4);
    result &= (head->getData() == 4);
    linkedListInsertAtTail(head, 6);
    result &= (head->getNext()->getData() == 6);

    delete head;
    return result;
}

bool testGetSize() {
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

bool testGetMiddle() {
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

void registerLinkedListTests(TestManager& test_manager) {
    test_manager.addTest(UnitTest(testDefaultConstructor, "default constructor"));
    test_manager.addTest(UnitTest(testDataConstructor, "data constructor"));
    test_manager.addTest(UnitTest(testFullConstructor, "full constructor"));
    test_manager.addTest(UnitTest(testCopyConstructor, "copy constructor"));
    test_manager.addTest(UnitTest(testDestructor, "destructor"));
    test_manager.addTest(UnitTest(testToString, "to string"));
    test_manager.addTest(UnitTest(testOstreamOperator, "ostream operator"));
    test_manager.addTest(UnitTest(testInsertAtHead, "insert at head"));
    test_manager.addTest(UnitTest(testInsertAtTail, "insert at tail"));
    test_manager.addTest(UnitTest(testGetSize, "get size"));
    test_manager.addTest(UnitTest(testGetMiddle, "get middle"));
}