#include "linked_list_tests.hpp"

bool linkedListTestDefaultConstructor() {
    bool result = true;

    LinkedList<int> int_list;
    result &= (int_list.data == 0);
    result &= (!int_list.next);

    return result;
}

bool linkedListTestDataConstructor() {
    bool result = true;

    LinkedList<int> int_list(4);
    result &= (int_list.data == 4);
    result &= (!int_list.next);

    LinkedList<char> char_list('a');
    result &= (char_list.data == 'a');
    result &= (!char_list.next);

    return result;
}

bool linkedListTestFullConstructor() {
    bool result = true;

    // We don't call delete on temp because 
    // temp is deleted when we delete int_list
    LinkedList<int>* temp = new LinkedList<int>(5);
    LinkedList<int>* int_list = new LinkedList<int>(4, temp);
    result &= (int_list->data == 4);
    result &= (int_list->next->data == 5);
    delete int_list;

    return result;
}

bool linkedListTestCopyConstructor() {
    bool result = true;

    LinkedList<int> one_next(4, new LinkedList<int>(5));
    LinkedList<int> one_next_copy(one_next);
    result &= (one_next_copy.data == one_next.data);
    result &= (one_next_copy.next->data == one_next.next->data);
    result &= (&one_next_copy != &one_next);
    result &= (&one_next_copy.next != &one_next.next);

    LinkedList<int> two_next(4, new LinkedList<int>(3, new LinkedList<int>(6)));
    LinkedList<int> two_next_copy(two_next);
    result &= (two_next_copy.data == two_next.data);
    result &= (two_next_copy.next->data == two_next.next->data);

    result &= (&two_next_copy != &two_next);
    result &= (&two_next_copy.next != &two_next.next);

    result &= (two_next_copy.next->data == two_next.next->data);
    result &= (two_next_copy.next->next->data == two_next.next->next->data);

    result &= (&two_next_copy != &two_next);
    result &= (&two_next_copy.next != &two_next.next);
    result &= (&two_next_copy.next->next != &two_next.next->next);

    return result;
}

bool linkedListTestAssignmentOperator() {
    bool result = true;

    LinkedList<int> original(4, new LinkedList<int>(5));
    LinkedList<int> assigned = original;
    result &= (assigned.data == original.data);
    result &= &assigned != &original;
    result &= (assigned.next->data == original.next->data);
    result &= assigned.next != original.next;

    return result;
}

bool linkedListTestEqualityOperator() {
    bool result = true;

    LinkedList<int>* unequal_lhs = new LinkedList<int>(2);
    LinkedList<int>* unequal_rhs = new LinkedList<int>(5);
    result &= !(*unequal_lhs == *unequal_rhs);
    delete unequal_lhs;
    delete unequal_rhs;

    LinkedList<int>* different_size_lhs = new LinkedList<int>(3);
    LinkedList<int>* different_size_rhs = new LinkedList<int>(3);
    linkedListInsertAtTail(&different_size_rhs, 6);
    result &= !(*different_size_lhs == *different_size_rhs);
    delete different_size_lhs;
    delete different_size_rhs;

    LinkedList<int>* equals_lhs = new LinkedList<int>(4);
    LinkedList<int>* equals_rhs = new LinkedList<int>(4);
    linkedListInsertAtTail(&equals_lhs, 6);
    linkedListInsertAtTail(&equals_rhs, 6);
    result &= *equals_lhs == *equals_rhs;
    delete equals_lhs;
    delete equals_rhs;

    return result;
}

bool linkedListTestGetTail() {
    bool result = true;

    LinkedList<int>* empty = nullptr;
    result &= !linkedListGetTail(&empty);

    LinkedList<int>* multiple_nodes = new LinkedList<int>(4,
        new LinkedList<int>(3));
    result &= linkedListGetTail(&multiple_nodes)->data == 3;
    result &= multiple_nodes->data == 4;
    delete multiple_nodes;

    return result;
}

bool linkedListTestInsertAtTail() {
    bool result = true;

    LinkedList<int>* init_as_empty = nullptr;
    result &= !init_as_empty;
    linkedListInsertAtTail(&init_as_empty, 4);
    result &= init_as_empty->data == 4;
    result &= !init_as_empty->next;
    delete init_as_empty;

    LinkedList<int>* not_empty = new LinkedList<int>(4);
    linkedListInsertAtTail(&not_empty, 5);
    result &= not_empty->next->data == 5;
    result &= !not_empty->next->next;
    delete not_empty;

    return result;
}

bool linkedListTestConcatenate() {
    bool result = true;

    LinkedList<int>* empty_head = nullptr;
    LinkedList<int>* empty_concat = nullptr;
    linkedListConcatenate(&empty_head, &empty_concat);
    result &= !empty_head;

    empty_head = nullptr;
    LinkedList<int>* concat = new LinkedList<int>(4);
    linkedListConcatenate(&empty_head, &concat);
    result &= empty_head->data == 4;
    result &= !empty_head->next;
    delete empty_head;

    LinkedList<int>* head = new LinkedList<int>(3);
    linkedListConcatenate(&head, &empty_concat);
    result &= !head->next;

    LinkedList<int>* new_concat = new LinkedList<int>(4);
    linkedListConcatenate(&head, &new_concat);
    result &= head->data == 3;
    result &= head->next->data == 4;
    result &= !head->next->next;
    delete head;

    return result;
}

bool linkedListTestInsertAtHead() {
    bool result = true;

    LinkedList<int>* init_as_empty = nullptr;
    result &= !init_as_empty;
    linkedListInsertAtHead(&init_as_empty, 6);
    result &= (init_as_empty->data == 6);
    result &= !init_as_empty->next;
    delete init_as_empty;

    LinkedList<int>* not_empty = new LinkedList<int>(8);
    linkedListInsertAtHead(&not_empty, 7);
    result &= not_empty->data == 7;
    result &= not_empty->next->data == 8;
    delete not_empty;

    return result;
}

bool linkedListTestGetLength() {
    bool result = true;

    LinkedList<int>* empty_list = nullptr;
    result &= linkedListGetLength(empty_list) == 0;

    LinkedList<int>* non_empty = new LinkedList<int>(5, new LinkedList<int>(2));
    result &= linkedListGetLength(non_empty) == 2;
    delete non_empty;

    return result;
}

bool linkedListTestPositionOfNthOccurrence() {
    bool result = true;

    LinkedList<char>* not_found = new LinkedList<char>('a');
    int not_found_result = linkedListPositionOfNthOccurrence(not_found, 'b', 1);
    result &= not_found_result == -1;
    delete not_found;

    LinkedList<int>* not_enough = new LinkedList<int>(3);
    linkedListInsertAtTail(&not_enough, 3);
    linkedListInsertAtTail(&not_enough, 5);
    int not_enough_result = linkedListPositionOfNthOccurrence(not_enough, 3, 3);
    result &= not_enough_result == -1;
    delete not_enough;

    LinkedList<std::string>* found_one = new LinkedList<std::string>("5");
    linkedListInsertAtTail(&found_one, std::string("4"));
    int found_one_result = linkedListPositionOfNthOccurrence(
        found_one, std::string("5"), 1);
    result &= found_one_result == 0;
    delete found_one;

    LinkedList<std::string>* found_many = new LinkedList<std::string>("5");
    linkedListInsertAtTail(&found_many, std::string("5"));
    int found_many_result = linkedListPositionOfNthOccurrence(
        found_many, std::string("5"), 2);
    result &= found_many_result == 1;
    delete found_many;

    return result;
}

bool linkedListTestGetNthNode() {
    bool result = true;

    LinkedList<int>* not_found = new LinkedList<int>(4);
    linkedListInsertAtHead(&not_found, 3);
    int not_found_position = linkedListPositionOfNthOccurrence(not_found, 5, 1);
    LinkedList<int>* not_found_result = linkedListGetNthNode(
        not_found, not_found_position);
    result &= (!not_found_result);

    LinkedList<int>* found = new LinkedList<int>(3);
    linkedListInsertAtHead(&found, 2);
    int found_position = linkedListPositionOfNthOccurrence(found, 2, 1);
    LinkedList<int>* found_result = linkedListGetNthNode(
        found, found_position);
    result &= (found_result == found);

    return result;
}

bool linkedListTestGetNthOccurrence() {
    bool result = true;

    LinkedList<char>* not_found = new LinkedList<char>('a');
    LinkedList<char>* not_found_result =
        linkedListGetNthOccurrence(not_found, 'b', 1);
    result &= !not_found_result;
    delete not_found;

    LinkedList<int>* not_enough = new LinkedList<int>(3);
    linkedListInsertAtTail(&not_enough, 3);
    linkedListInsertAtTail(&not_enough, 5);
    LinkedList<int>* not_enough_result =
        linkedListGetNthOccurrence(not_enough, 3, 3);
    result &= !not_enough_result;
    delete not_enough;

    LinkedList<std::string>* found_one = new LinkedList<std::string>("5");
    linkedListInsertAtTail(&found_one, std::string("4"));
    LinkedList<std::string>* found_one_result =
        linkedListGetNthOccurrence(found_one, std::string("5"), 1);
    result &= found_one_result == found_one;
    delete found_one;

    LinkedList<std::string>* found_many = new LinkedList<std::string>("5");
    linkedListInsertAtTail(&found_many, std::string("5"));
    LinkedList<std::string>* found_many_result =
        linkedListGetNthOccurrence(found_many, std::string("5"), 2);
    result &= found_many_result == found_many->next;
    delete found_many;

    return result;
}

bool linkedListTestDeleteNthOccurrence() {
    bool result = true;

    LinkedList<int>* not_found = new LinkedList<int>(5);
    linkedListInsertAtTail(&not_found, 3);
    linkedListInsertAtTail(&not_found, 4);
    linkedListDeleteNthOccurrence(&not_found, 2, 1);
    result &= (linkedListGetLength(not_found) == 3);
    delete not_found;

    LinkedList<int>* delete_head = new LinkedList<int>(3);
    linkedListInsertAtTail(&delete_head, 6);
    linkedListInsertAtTail(&delete_head, 7);
    linkedListDeleteNthOccurrence(&delete_head, 3, 1);
    result &= (delete_head->data == 6);
    delete delete_head;

    LinkedList<int>* delete_after_head = new LinkedList<int>(4);
    linkedListInsertAtTail(&delete_after_head, 7);
    linkedListInsertAtTail(&delete_after_head, 8);
    linkedListDeleteNthOccurrence(&delete_after_head, 7, 1);
    result &= (delete_after_head->next->data == 8);
    delete delete_after_head;

    return result;
}

bool linkedListTestGetPredecessorOfNthOccurrence() {
    bool result = true;

    LinkedList<int>* not_found = new LinkedList<int>(4);
    LinkedList<int>* not_found_result = 
        linkedListGetPredecessorOfNthOccurrence(not_found, 3, 1);
    result &= !not_found_result;
    delete not_found;

    LinkedList<int>* first_element = new LinkedList<int>(4);
    LinkedList<int>* first_element_result = 
        linkedListGetPredecessorOfNthOccurrence(first_element, 4, 1);
    result &= !first_element_result;
    delete first_element;

    LinkedList<int>* general_case = new LinkedList<int>(4);
    linkedListInsertAtTail(&general_case, 2);
    LinkedList<int>* general_case_result = 
        linkedListGetPredecessorOfNthOccurrence(general_case, 2, 1);
    result &= general_case_result == general_case;
    delete general_case;

    return result;
}

bool linkedListTestGetSuccessorOfNthOccurrence() {
    bool result = true;

    LinkedList<int>* not_found = new LinkedList<int>(4);
    LinkedList<int>* not_found_result = 
        linkedListGetSuccessorOfNthOccurrence(not_found, 3, 1);
    result &= !not_found_result;
    delete not_found;

    LinkedList<int>* last_element = new LinkedList<int>(4);
    LinkedList<int>* last_element_result = 
        linkedListGetSuccessorOfNthOccurrence(last_element, 4, 1);
    result &= !last_element_result;
    delete last_element;

    LinkedList<int>* general_case = new LinkedList<int>(4);
    linkedListInsertAtTail(&general_case, 2);
    LinkedList<int>* general_case_result = 
        linkedListGetSuccessorOfNthOccurrence(general_case, 4, 1);
    result &= general_case_result == general_case->next;
    delete general_case;

    return result;
}

void linkedListTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("linked list");
    testGroupAddTest(&test_group, UnitTest("default constructor",
        linkedListTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("data constructor",
        linkedListTestDataConstructor));
    testGroupAddTest(&test_group, UnitTest("full constructor",
        linkedListTestFullConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor",
        linkedListTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator",
        linkedListTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator",
        linkedListTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("get tail",
        linkedListTestGetTail));
    testGroupAddTest(&test_group, UnitTest("insert at tail",
        linkedListTestInsertAtTail));
    testGroupAddTest(&test_group, UnitTest("concatenate",
        linkedListTestConcatenate));
    testGroupAddTest(&test_group, UnitTest("insert at head",
        linkedListTestInsertAtHead));
    testGroupAddTest(&test_group, UnitTest("length",
        linkedListTestGetLength));
    testGroupAddTest(&test_group, UnitTest("find position of nth occurrence",
        linkedListTestPositionOfNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("get nth node",
        linkedListTestGetNthNode));
    testGroupAddTest(&test_group, UnitTest("find nth occurrence",
        linkedListTestGetNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("delete nth occurrence",
        linkedListTestDeleteNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("get predecessor of nth occurrence",
        linkedListTestGetPredecessorOfNthOccurrence));
    testGroupAddTest(&test_group, UnitTest("get successor of nth occurrence",
        linkedListTestGetSuccessorOfNthOccurrence));
    testManagerAddTestGroup(test_manager, test_group);
}
