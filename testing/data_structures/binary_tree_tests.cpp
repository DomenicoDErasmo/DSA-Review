#include "binary_tree_tests.hpp"
#include <data_structures/binary_tree.cpp>

bool binaryTreeTestDefaultConstructor() {
    bool result = true;

    BinaryTree<int>* default_tree = new BinaryTree<int>();
    result &= default_tree->data == 0;
    result &= !default_tree->left;
    result &= !default_tree->right;
    delete default_tree;

    return result;
}

bool binaryTreeTestDataConstructor() {
    bool result = true;
    
    BinaryTree<int>* int_list = new BinaryTree<int>(5);
    result &= (int_list->data == 5);
    result &= (!int_list->left);
    result &= (!int_list->right);
    delete int_list;

    return result;
}

bool binaryTreeTestFullConstructor() {
    bool result = true;

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* right = new BinaryTree<int>(6);
    BinaryTree<int>* int_list = new BinaryTree<int>(5, left, right);
    result &= int_list->data == 5;
    result &= int_list->left->data == 3;
    result &= int_list->right->data == 6;
    delete int_list;

    return result;
}

bool binaryTreeTestCopyConstructor() {
    bool result = true;

    BinaryTree<int>* no_children = new BinaryTree<int>(5);
    BinaryTree<int>* no_children_copy = new BinaryTree<int>(*no_children);
    result &= no_children_copy->data == 5;
    result &= !no_children_copy->left;
    result &= !no_children_copy->right;
    result &= no_children != no_children_copy;
    delete no_children;
    delete no_children_copy;

    BinaryTree<int>* left_child = new BinaryTree<int>(
        3,
        new BinaryTree<int>(2),
        nullptr);
    BinaryTree<int>* left_child_copy = new BinaryTree<int>(*left_child);
    result &= left_child_copy->data == left_child->data;
    result &= left_child_copy != left_child;
    result &= left_child_copy->left->data == left_child->left->data;
    result &= left_child_copy->left != left_child->left;
    result &= !left_child_copy->right;
    delete left_child;
    delete left_child_copy;

    BinaryTree<int>* right_child = new BinaryTree<int>(
        3,
        nullptr,
        new BinaryTree<int>(4));
    BinaryTree<int>* right_child_copy = new BinaryTree<int>(*right_child);
    result &= right_child_copy->data == right_child->data;
    result &= right_child_copy != right_child;
    result &= right_child_copy->right->data == right_child->right->data;
    result &= right_child_copy->right != right_child->right;
    result &= !right_child_copy->left;
    delete right_child;
    delete right_child_copy;

    return result;
}

bool binaryTreeTestAssignmentOperator() {
    bool result = true;
    
    BinaryTree<int>* original = new BinaryTree<int>(4,
        new BinaryTree<int>(3,
            new BinaryTree<int>(2),
            nullptr),
        new BinaryTree<int>(5));
    BinaryTree<int> assigned = *original;
    result &= assigned.data == original->data;
    result &= assigned.left->data == original->left->data;
    result &= assigned.left->left->data == original->left->left->data;
    result &= assigned.right->data == original->right->data;
    delete original;

    return result;
}

bool binaryTreeTestEqualityOperator() {
    bool result = true;

    BinaryTree<int> data_mismatch_lhs(4);
    BinaryTree<int> data_mismatch_rhs(5);
    result &= !(data_mismatch_lhs == data_mismatch_rhs);

    BinaryTree<int> left_mismatch_lhs(4, new BinaryTree<int>(3), nullptr);
    BinaryTree<int> left_mismatch_rhs(4, nullptr, nullptr);
    result &= !(left_mismatch_lhs == left_mismatch_rhs);

    BinaryTree<int> left_mismatch_lhs_2(4, nullptr, nullptr);
    BinaryTree<int> left_mismatch_rhs_2(4, new BinaryTree<int>(3), nullptr);
    result &= !(left_mismatch_lhs_2 == left_mismatch_rhs_2);

    BinaryTree<int> right_mismatch_lhs(4, nullptr, new BinaryTree<int>(5));
    BinaryTree<int> right_mismatch_rhs(4, nullptr, nullptr);
    result &= !(right_mismatch_lhs == right_mismatch_rhs);

    BinaryTree<int> right_mismatch_lhs_2(4, nullptr, nullptr);
    BinaryTree<int> right_mismatch_rhs_2(4, nullptr, new BinaryTree<int>(5));
    result &= !(right_mismatch_lhs_2 == right_mismatch_rhs_2);
    
    BinaryTree<int> left_val_mismatch_lhs(4, 
        new BinaryTree<int>(3), 
        new BinaryTree<int>(5));
    BinaryTree<int> left_val_mismatch_rhs(4,
        new BinaryTree<int>(2),
        new BinaryTree<int>(5));
    result &= !(left_val_mismatch_lhs == left_val_mismatch_rhs);
    
    BinaryTree<int> right_val_mismatch_lhs(4, 
        new BinaryTree<int>(3), 
        new BinaryTree<int>(5));
    BinaryTree<int> right_val_mismatch_rhs(4,
        new BinaryTree<int>(3),
        new BinaryTree<int>(6));
    result &= !(left_val_mismatch_lhs == left_val_mismatch_rhs);
    
    BinaryTree<int> equals_lhs(4, 
        new BinaryTree<int>(2,
            new BinaryTree<int>(1),
            nullptr), 
        new BinaryTree<int>(6,
            nullptr,
            new BinaryTree<int>(7)));
    BinaryTree<int> equals_rhs(4,
        new BinaryTree<int>(2,
            new BinaryTree<int>(1),
            nullptr),
        new BinaryTree<int>(6,
            nullptr,
            new BinaryTree<int>(7)));
    result &= equals_lhs == equals_rhs;
    result &= &equals_lhs != &equals_rhs;

    return result;
}

bool binaryTreeTestGetHeight() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= binaryTreeGetHeight(empty) == 0;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(7);
    result &= binaryTreeGetHeight(leaf_root) == 1;
    delete leaf_root;

    BinaryTree<int>* left_child = new BinaryTree<int>(5,
        new BinaryTree<int>(3),
        nullptr);
    result &= binaryTreeGetHeight(left_child) == 2;
    delete left_child;

    BinaryTree<int>* right_child = new BinaryTree<int>(5,
        nullptr,
        new BinaryTree<int>(6));
    result &= binaryTreeGetHeight(right_child) == 2;
    delete right_child;

    return result;
}

bool binaryTreeTestGetNumNodes() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= binaryTreeGetNumNodes(empty) == 0;

    BinaryTree<int>* leaf = new BinaryTree<int>(4);
    result &= binaryTreeGetNumNodes(leaf) == 1;
    delete leaf;

    BinaryTree<int>* children = new BinaryTree<int>(5,
        new BinaryTree<int>(2),
        new BinaryTree<int>(6));
    result &= binaryTreeGetNumNodes(children) == 3;
    delete children;

    BinaryTree<int>* grandchildren = new BinaryTree<int>(5,
        new BinaryTree<int>(2,
            new BinaryTree<int>(1),
            nullptr),
        new BinaryTree<int>(7));
    result &= binaryTreeGetNumNodes(grandchildren) == 4;
    result &= binaryTreeGetNumNodes(grandchildren->left) == 2;
    delete grandchildren;

    return result;
}

bool binaryTreeTestInsertNode() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    binaryTreeInsertNode(&empty, 4);
    result &= empty->data == 4;
    delete empty;

    BinaryTree<int>* insert_lower = new BinaryTree<int>(4);
    binaryTreeInsertNode(&insert_lower, 3);
    result &= insert_lower->left->data == 3;
    result &= !insert_lower->right;
    delete insert_lower;

    BinaryTree<int>* insert_greater = new BinaryTree<int>(4);
    binaryTreeInsertNode(&insert_greater, 6);
    result &= insert_greater->right->data == 6;
    result &= !insert_greater->left;
    delete insert_greater;

    return result;
}

bool binaryTreeTestGetPreorder() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    LinkedList<int>* empty_preorder = binaryTreeGetPreorder(empty);
    result &= !empty_preorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_preorder = binaryTreeGetPreorder(leaf_root);
    result &= linkedListGetLength(leaf_root_preorder) == 1;
    result &= leaf_root_preorder->data == 4;
    delete leaf_root;
    delete leaf_root_preorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_preorder = 
        binaryTreeGetPreorder(has_left_child);
    result &= linkedListGetLength(has_left_child_preorder) == 2;
    result &= has_left_child_preorder->data == 4;
    result &= has_left_child_preorder->next->data == 3;
    delete has_left_child;
    delete has_left_child_preorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_preorder = 
        binaryTreeGetPreorder(has_right_child);
    result &= linkedListGetLength(has_right_child_preorder) == 2;
    result &= has_right_child_preorder->data == 4;
    result &= has_right_child_preorder->next->data == 5;
    delete has_right_child;
    delete has_right_child_preorder;

    BinaryTree<int>* has_grandchildren = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_grandchildren, 2);
    binaryTreeInsertNode(&has_grandchildren, 1);
    binaryTreeInsertNode(&has_grandchildren, 3);
    binaryTreeInsertNode(&has_grandchildren, 6);
    binaryTreeInsertNode(&has_grandchildren, 5);
    binaryTreeInsertNode(&has_grandchildren, 7);
    LinkedList<int>* has_grandchildren_preorder = 
        binaryTreeGetPreorder(has_grandchildren);

    LinkedList<int>* has_grandchildren_preorder_expected = nullptr;
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 4);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 2);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 1);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 3);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 6);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 5);
    linkedListInsertAtTail(&has_grandchildren_preorder_expected, 7);
    result &= *has_grandchildren_preorder == *has_grandchildren_preorder_expected;
    delete has_grandchildren;
    delete has_grandchildren_preorder;
    delete has_grandchildren_preorder_expected;

    return result;
}

bool binaryTreeTestGetInorder() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    LinkedList<int>* empty_inorder = binaryTreeGetInorder(empty);
    result &= !empty_inorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_inorder = binaryTreeGetInorder(leaf_root);
    result &= linkedListGetLength(leaf_root_inorder) == 1;
    result &= leaf_root_inorder->data == 4;
    delete leaf_root;
    delete leaf_root_inorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_inorder = 
        binaryTreeGetInorder(has_left_child);
    result &= linkedListGetLength(has_left_child_inorder) == 2;
    result &= has_left_child_inorder->data == 3;
    result &= has_left_child_inorder->next->data == 4;
    delete has_left_child;
    delete has_left_child_inorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_inorder = 
        binaryTreeGetInorder(has_right_child);
    result &= linkedListGetLength(has_right_child_inorder) == 2;
    result &= has_right_child_inorder->data == 4;
    result &= has_right_child_inorder->next->data == 5;
    delete has_right_child;
    delete has_right_child_inorder;

    BinaryTree<int>* has_grandchildren = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_grandchildren, 2);
    binaryTreeInsertNode(&has_grandchildren, 1);
    binaryTreeInsertNode(&has_grandchildren, 3);
    binaryTreeInsertNode(&has_grandchildren, 6);
    binaryTreeInsertNode(&has_grandchildren, 5);
    binaryTreeInsertNode(&has_grandchildren, 7);
    LinkedList<int>* has_grandchildren_inorder = 
        binaryTreeGetInorder(has_grandchildren);

    LinkedList<int>* has_grandchildren_inorder_expected = nullptr;
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 1);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 2);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 3);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 4);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 5);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 6);
    linkedListInsertAtTail(&has_grandchildren_inorder_expected, 7);
    result &= *has_grandchildren_inorder == *has_grandchildren_inorder_expected;
    delete has_grandchildren;
    delete has_grandchildren_inorder;
    delete has_grandchildren_inorder_expected;

    return result;
}

bool binaryTreeTestGetPostorder() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    LinkedList<int>* empty_postorder = binaryTreeGetPostorder(empty);
    result &= !empty_postorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_postorder = binaryTreeGetPostorder(leaf_root);
    result &= linkedListGetLength(leaf_root_postorder) == 1;
    result &= leaf_root_postorder->data == 4;
    delete leaf_root;
    delete leaf_root_postorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_postorder = 
        binaryTreeGetPostorder(has_left_child);
    result &= linkedListGetLength(has_left_child_postorder) == 2;
    result &= has_left_child_postorder->data == 3;
    result &= has_left_child_postorder->next->data == 4;
    delete has_left_child;
    delete has_left_child_postorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_postorder = 
        binaryTreeGetPostorder(has_right_child);
    result &= linkedListGetLength(has_right_child_postorder) == 2;
    result &= has_right_child_postorder->data == 5;
    result &= has_right_child_postorder->next->data == 4;
    delete has_right_child;
    delete has_right_child_postorder;

    BinaryTree<int>* has_grandchildren = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_grandchildren, 2);
    binaryTreeInsertNode(&has_grandchildren, 1);
    binaryTreeInsertNode(&has_grandchildren, 3);
    binaryTreeInsertNode(&has_grandchildren, 6);
    binaryTreeInsertNode(&has_grandchildren, 5);
    binaryTreeInsertNode(&has_grandchildren, 7);
    LinkedList<int>* has_grandchildren_postorder = 
        binaryTreeGetPostorder(has_grandchildren);

    LinkedList<int>* has_grandchildren_postorder_expected = nullptr;
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 1);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 3);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 2);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 5);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 7);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 6);
    linkedListInsertAtTail(&has_grandchildren_postorder_expected, 4);
    result &= *has_grandchildren_postorder 
              == *has_grandchildren_postorder_expected;
    delete has_grandchildren;
    delete has_grandchildren_postorder;
    delete has_grandchildren_postorder_expected;

    return result;
}

bool binaryTreeTestGetLevelOrder() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= !binaryTreeGetLevelOrder(empty);

    BinaryTree<int>* leaf_root = new BinaryTree<int>(3);
    LinkedList<int>* leaf_root_bfs = binaryTreeGetLevelOrder(leaf_root);
    result &= linkedListGetLength(leaf_root_bfs) == 1;
    delete leaf_root;
    delete leaf_root_bfs;

    BinaryTree<int>* left_child = new BinaryTree<int>(3);
    binaryTreeInsertNode(&left_child, 2);
    LinkedList<int>* left_child_bfs = binaryTreeGetLevelOrder(left_child);
    LinkedList<int>* left_child_bfs_expected = new LinkedList<int>(3);
    linkedListInsertAtTail(&left_child_bfs_expected, 2);
    result &= *left_child_bfs == *left_child_bfs_expected;
    delete left_child;
    delete left_child_bfs;
    delete left_child_bfs_expected;

    BinaryTree<int>* right_child = new BinaryTree<int>(3);
    binaryTreeInsertNode(&right_child, 4);
    LinkedList<int>* right_child_bfs = binaryTreeGetLevelOrder(right_child);
    LinkedList<int>* right_child_bfs_expected = new LinkedList<int>(3);
    linkedListInsertAtTail(&right_child_bfs_expected, 4);
    result &= *right_child_bfs == *right_child_bfs_expected;
    delete right_child;
    delete right_child_bfs;
    delete right_child_bfs_expected;

    BinaryTree<int>* both_children = new BinaryTree<int>(6);
    binaryTreeInsertNode(&both_children, 3);
    binaryTreeInsertNode(&both_children, 8);
    LinkedList<int>* both_children_bfs = binaryTreeGetLevelOrder(both_children);
    LinkedList<int>* both_children_bfs_expected = new LinkedList<int>(6);
    linkedListInsertAtTail(&both_children_bfs_expected, 3);
    linkedListInsertAtTail(&both_children_bfs_expected, 8);
    result &= *both_children_bfs == *both_children_bfs_expected;
    delete both_children;
    delete both_children_bfs;
    delete both_children_bfs_expected;

    return result;
}

bool binaryTreeTestFindNode() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    BinaryTree<int>* empty_result = binaryTreeGetNode(empty, 4);
    result &= !empty_result;

    BinaryTree<int>* not_found = new BinaryTree<int>(4);
    BinaryTree<int>* not_found_result = binaryTreeGetNode(empty, 3);
    result &= !not_found_result;
    delete not_found;

    BinaryTree<int>* in_left = new BinaryTree<int>(4);
    binaryTreeInsertNode(&in_left, 3);
    BinaryTree<int>* in_left_result = binaryTreeGetNode(in_left, 3);
    result &= in_left_result == in_left->left;
    delete in_left;

    BinaryTree<int>* in_right = new BinaryTree<int>(4);
    binaryTreeInsertNode(&in_right, 5);
    BinaryTree<int>* in_right_result = binaryTreeGetNode(in_right, 5);
    result &= in_right_result == in_right->right;
    delete in_right;

    BinaryTree<int>* recursive_test = new BinaryTree<int>(4);
    binaryTreeInsertNode(&recursive_test, 3);
    binaryTreeInsertNode(&recursive_test, 2);
    BinaryTree<int>* recursive_test_result = binaryTreeGetNode(
        recursive_test, 2);
    result &= recursive_test_result == recursive_test->left->left;
    delete recursive_test;

    return result;
}

bool binaryTreeTestGetOrderCessor() {
    bool result = true;

    BinaryTree<int>* preorder_predecessor = new BinaryTree<int>(4);
    binaryTreeInsertNode(&preorder_predecessor, 2);
    result &= binaryTreeGetOrderCessor(
        preorder_predecessor, 
        2, 
        binaryTreeGetPreorder, 
        linkedListGetPredecessorOfNthOccurrence) == preorder_predecessor;
    delete preorder_predecessor;

    BinaryTree<int>* inorder_predecessor = new BinaryTree<int>(4);
    binaryTreeInsertNode(&inorder_predecessor, 2);
    result &= binaryTreeGetOrderCessor(
        inorder_predecessor, 
        4, 
        binaryTreeGetInorder, 
        linkedListGetPredecessorOfNthOccurrence) == inorder_predecessor->left;
    delete inorder_predecessor;

    BinaryTree<int>* postorder_successor = new BinaryTree<int>(4);
    binaryTreeInsertNode(&postorder_successor, 2);
    binaryTreeInsertNode(&postorder_successor, 5);
    result &= binaryTreeGetOrderCessor(
        postorder_successor, 
        5, 
        binaryTreeGetPostorder, 
        linkedListGetSuccessorOfNthOccurrence) == postorder_successor;
    delete postorder_successor;

    return result;
}

bool binaryTreeTestGetParentOf() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= !binaryTreeGetParentOf(empty, 2);
    
    BinaryTree<int>* leaf_root = new BinaryTree<int>(5);
    result &= !binaryTreeGetParentOf(leaf_root, 5);
    delete leaf_root;

    BinaryTree<int>* parent_of_left = new BinaryTree<int>(4);
    binaryTreeInsertNode(&parent_of_left, 2);
    result &= binaryTreeGetParentOf(parent_of_left, 2) == parent_of_left;
    delete parent_of_left;

    BinaryTree<int>* parent_of_right = new BinaryTree<int>(5);
    binaryTreeInsertNode(&parent_of_right, 7);
    result &= binaryTreeGetParentOf(parent_of_right, 7) == parent_of_right;
    delete parent_of_right;

    BinaryTree<int>* left_is_parent = new BinaryTree<int>(4);
    binaryTreeInsertNode(&left_is_parent, 3);
    binaryTreeInsertNode(&left_is_parent, 2);
    result &= binaryTreeGetParentOf(left_is_parent, 2) == left_is_parent->left;
    delete left_is_parent;

    return result;
}

bool binaryTreeTestDeleteNode() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    binaryTreeDeleteNode(&empty, 2);
    result &= !empty;

    BinaryTree<int>* delete_root = new BinaryTree<int>(4);
    binaryTreeDeleteNode(&delete_root, 4);

    BinaryTree<int>* delete_head_left_leaf = new BinaryTree<int>(5);
    binaryTreeInsertNode(&delete_head_left_leaf, 2);
    binaryTreeDeleteNode(&delete_head_left_leaf, 5);
    result &= delete_head_left_leaf->data == 2;
    delete delete_head_left_leaf;

    BinaryTree<int>* delete_head_left_non_leaf = new BinaryTree<int>(6);
    binaryTreeInsertNode(&delete_head_left_non_leaf, 3);
    binaryTreeInsertNode(&delete_head_left_non_leaf, 5);
    binaryTreeInsertNode(&delete_head_left_non_leaf, 4);
    binaryTreeDeleteNode(&delete_head_left_non_leaf, 6);
    result &= delete_head_left_non_leaf->data == 5;
    result &= delete_head_left_non_leaf->left->right->data == 4;
    delete delete_head_left_non_leaf;

    BinaryTree<int>* delete_head_right_leaf = new BinaryTree<int>(5);
    binaryTreeInsertNode(&delete_head_right_leaf, 4);
    binaryTreeDeleteNode(&delete_head_right_leaf, 5);
    result &= delete_head_right_leaf->data == 4;
    delete delete_head_right_leaf;

    BinaryTree<int>* delete_head_right_non_leaf = new BinaryTree<int>(4);
    binaryTreeInsertNode(&delete_head_right_non_leaf, 7);
    binaryTreeInsertNode(&delete_head_right_non_leaf, 5);
    binaryTreeInsertNode(&delete_head_right_non_leaf, 6);
    binaryTreeDeleteNode(&delete_head_right_non_leaf, 4);
    result &= delete_head_right_non_leaf->data == 5;
    result &= delete_head_right_non_leaf->right->left->data == 6;
    delete delete_head_right_non_leaf;

    BinaryTree<int>* delete_left = new BinaryTree<int>(4);
    binaryTreeInsertNode(&delete_left, 2);
    binaryTreeInsertNode(&delete_left, 1);
    binaryTreeDeleteNode(&delete_left, 2);
    result &= delete_left->left->data == 1;
    delete delete_left;

    return result;
}

void binaryTreeTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("binary tree");
    testGroupAddTest(&test_group, 
        UnitTest("default constructor", binaryTreeTestDefaultConstructor));
    testGroupAddTest(&test_group,
        UnitTest("data constructor", binaryTreeTestDataConstructor));
    testGroupAddTest(&test_group,
        UnitTest("full constructor", binaryTreeTestFullConstructor));
    testGroupAddTest(&test_group,
        UnitTest("copy constructor", binaryTreeTestCopyConstructor));
    testGroupAddTest(&test_group,
        UnitTest("assignment operator", binaryTreeTestAssignmentOperator));
    testGroupAddTest(&test_group,
        UnitTest("equality operator", binaryTreeTestEqualityOperator));
    testGroupAddTest(&test_group, 
        UnitTest("get height", binaryTreeTestGetHeight));
    testGroupAddTest(&test_group,
        UnitTest("get size", binaryTreeTestGetNumNodes));
    testGroupAddTest(&test_group, 
        UnitTest("insert node", binaryTreeTestInsertNode));
    testGroupAddTest(&test_group,
        UnitTest("get preorder", binaryTreeTestGetPreorder));
    testGroupAddTest(&test_group,
        UnitTest("get inorder", binaryTreeTestGetInorder));
    testGroupAddTest(&test_group,
        UnitTest("get postorder", binaryTreeTestGetPostorder));
    testGroupAddTest(&test_group,
        UnitTest("get level order", binaryTreeTestGetLevelOrder));
    testGroupAddTest(&test_group,
        UnitTest("find node", binaryTreeTestFindNode));
    testGroupAddTest(&test_group,
        UnitTest("get order cessor", binaryTreeTestGetOrderCessor));
    testGroupAddTest(&test_group,
        UnitTest("get parent of", binaryTreeTestGetParentOf));
    testGroupAddTest(&test_group,
        UnitTest("delete node", binaryTreeTestDeleteNode));
    testManagerAddTestGroup(test_manager, test_group);
}
