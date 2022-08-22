#include "linked_list_tests.hpp"

/**
 * @brief Tests if the equality operator works between the two lists.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testListEquality() {
    bool result = true;

    LinkedList<char> base_list('a');
    base_list.insertAtHead('c');

    // first inequality case: first list is longer
    LinkedList<char> smaller_list('c');
    result &= (base_list != smaller_list);

    // second inequality case: second list is longer
    LinkedList<char> larger_list('b');
    larger_list.insertAtHead('a');
    larger_list.insertAtHead('c');
    result &= (base_list != larger_list);

    // third inequailty case: we have a different value somewhere in the lists
    LinkedList<char> different_value_list('b');
    different_value_list.insertAtHead('c');
    result &= (base_list != different_value_list);

    // equality case: same size and all values match
    LinkedList<char> equal_list('a');
    equal_list.insertAtHead('c');
    result &= (base_list == equal_list);

    return result;
}

/**
 * @brief Tests that we can add nodes to the linked list.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testInsertAtHead() {
    bool result = true;

    LinkedList<int> list(10);
    list.insertAtHead(5);
    result &= (list.getHead()->getData() == 5);

    list.insertAtHead(-4);
    result &= (list.getHead()->getData() == -4);

    list.insertAtHead(6);
    result &= (list.getHead()->getData() == 6);

    return result;
}

/**
 * @brief Tests that we can return the linked list length.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testLength() {
    bool result = true;

    LinkedList<char> list('r');
    result &= (list.length() == 1);

    list.insertAtHead('t');
    result &= (list.length() == 2);

    list.insertAtHead('n');
    result &= (list.length() == 3);

    return result;
}

/**
 * @brief Tests that we can reverse the linked list.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testReverseList() {
    bool result = true;

    LinkedList<std::string> list("hello");              // "hello"
    list.insertAtHead("world");                         // "world, hello"

    reverseList(&list);                                 // "hello, world"
    LinkedList<std::string> expected_list("world");
    expected_list.insertAtHead("hello");
    result &= (list == expected_list);

    return result;
}

/**
 * @brief Tests that we can remove the specified node from the list.
 * 
 * @return true if all tests succed, otherwise false.
 */
bool testRemoveNode() {
    bool result = true;

    // init
    LinkedList<int> list(1);
    list.insertAtHead(2);
    list.insertAtHead(3);

    removeNode(list.getHead(), list.getHead()->getNext());
    LinkedList<int> expected_list(1);
    expected_list.insertAtHead(3);
    result &= (list == expected_list);

    return result;
}

/**
 * @brief Tests that we can remove duplicate values from the list.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testRemoveDuplicates() {
    bool result = true;

    LinkedList<char> list ('a');
    list.insertAtHead('b');
    list.insertAtHead('b');
    list.insertAtHead('c');
    list.insertAtHead('b');
    list.insertAtHead('d');

    removeDuplicates(&list);

    LinkedList<char> expected_list('a');
    expected_list.insertAtHead('c');
    expected_list.insertAtHead('b');
    expected_list.insertAtHead('d');

    result &= (list == expected_list);

    return result;
}

/**
 * @brief Tests that we can insert nodes at the tail of the list.
 * 
 * @return true if all tests succeed, otherwise false.
 */
bool testInsertAtTail() {
    bool result = true;

    LinkedList<std::string> list("hello");
    list.insertAtTail(std::string("world"));

    LinkedList<std::string> expected_list("world");
    expected_list.insertAtHead("hello");

    result &= (list == expected_list);

    return result;
}

/**
 * @brief Adds all tests defined in this file to the provided test manager
 * 
 * @param test_manager The test manager that will run all tests
 */
void registerLinkedListTests(TestManager& test_manager) {
    test_manager.addTest(Test(testListEquality, "Test list equality"));
    test_manager.addTest(Test(testInsertAtHead, "Test insert at head"));
    test_manager.addTest(Test(testLength, "Test length"));
    test_manager.addTest(Test(testReverseList, "Test reverse list"));
    test_manager.addTest(Test(testRemoveNode, "Test remove node"));
    test_manager.addTest(Test(testRemoveDuplicates, "Test remove duplicates"));
    test_manager.addTest(Test(testInsertAtTail, "Test insert at tail"));
}