#include <data_structures/binary_tree_tests.hpp>
#include <string>

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
    LinkedList<int>* empty_preorder = nullptr;
    binaryTreeGetPreorder(empty, &empty_preorder);
    result &= !empty_preorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_preorder = nullptr;
    binaryTreeGetPreorder(leaf_root, &leaf_root_preorder);
    result &= linkedListGetLength(leaf_root_preorder) == 1;
    result &= leaf_root_preorder->data == 4;
    delete leaf_root;
    delete leaf_root_preorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_preorder = nullptr;
    binaryTreeGetPreorder(has_left_child, &has_left_child_preorder);
    result &= linkedListGetLength(has_left_child_preorder) == 2;
    result &= has_left_child_preorder->data == 4;
    result &= has_left_child_preorder->next->data == 3;
    delete has_left_child;
    delete has_left_child_preorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_preorder = nullptr;
    binaryTreeGetPreorder(has_right_child, &has_right_child_preorder);
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
    LinkedList<int>* has_grandchildren_preorder = nullptr;
    binaryTreeGetPreorder(has_grandchildren, &has_grandchildren_preorder);

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
    LinkedList<int>* empty_inorder = nullptr;
    binaryTreeGetInorder(empty, &empty_inorder);
    result &= !empty_inorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_inorder = nullptr;
    binaryTreeGetInorder(leaf_root, &leaf_root_inorder);
    result &= linkedListGetLength(leaf_root_inorder) == 1;
    result &= leaf_root_inorder->data == 4;
    delete leaf_root;
    delete leaf_root_inorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_inorder = nullptr;
    binaryTreeGetInorder(has_left_child, &has_left_child_inorder);
    result &= linkedListGetLength(has_left_child_inorder) == 2;
    result &= has_left_child_inorder->data == 3;
    result &= has_left_child_inorder->next->data == 4;
    delete has_left_child;
    delete has_left_child_inorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_inorder = nullptr;
    binaryTreeGetInorder(has_right_child, &has_right_child_inorder);
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
    LinkedList<int>* has_grandchildren_inorder = nullptr;
    binaryTreeGetInorder(has_grandchildren, &has_grandchildren_inorder);

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
    LinkedList<int>* empty_postorder = nullptr;
    binaryTreeGetPostorder(empty, &empty_postorder);
    result &= !empty_postorder;

    BinaryTree<int>* leaf_root = new BinaryTree<int>(4);
    LinkedList<int>* leaf_root_postorder = nullptr;
    binaryTreeGetPostorder(leaf_root, &leaf_root_postorder);
    result &= linkedListGetLength(leaf_root_postorder) == 1;
    result &= leaf_root_postorder->data == 4;
    delete leaf_root;
    delete leaf_root_postorder;

    BinaryTree<int>* has_left_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_left_child, 3);
    LinkedList<int>* has_left_child_postorder = nullptr;
    binaryTreeGetPostorder(has_left_child, &has_left_child_postorder);
    result &= linkedListGetLength(has_left_child_postorder) == 2;
    result &= has_left_child_postorder->data == 3;
    result &= has_left_child_postorder->next->data == 4;
    delete has_left_child;
    delete has_left_child_postorder;

    BinaryTree<int>* has_right_child = new BinaryTree<int>(4);
    binaryTreeInsertNode(&has_right_child, 5);
    LinkedList<int>* has_right_child_postorder = nullptr;
    binaryTreeGetPostorder(has_right_child, &has_right_child_postorder);
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
    LinkedList<int>* has_grandchildren_postorder = nullptr;
    binaryTreeGetPostorder(has_grandchildren, &has_grandchildren_postorder);

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

bool binaryTreeTestFindNode() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    BinaryTree<int>* empty_result = binaryTreeFindNode(empty, 4);
    result &= !empty_result;

    BinaryTree<int>* not_found = new BinaryTree<int>(4);
    BinaryTree<int>* not_found_result = binaryTreeFindNode(empty, 3);
    result &= !not_found_result;
    delete not_found;

    BinaryTree<int>* in_left = new BinaryTree<int>(4);
    binaryTreeInsertNode(&in_left, 3);
    BinaryTree<int>* in_left_result = binaryTreeFindNode(in_left, 3);
    result &= in_left_result == in_left->left;
    delete in_left;

    BinaryTree<int>* in_right = new BinaryTree<int>(4);
    binaryTreeInsertNode(&in_right, 5);
    BinaryTree<int>* in_right_result = binaryTreeFindNode(in_right, 5);
    result &= in_right_result == in_right->right;
    delete in_right;

    BinaryTree<int>* recursive_test = new BinaryTree<int>(4);
    binaryTreeInsertNode(&recursive_test, 3);
    binaryTreeInsertNode(&recursive_test, 2);
    BinaryTree<int>* recursive_test_result = binaryTreeFindNode(
        recursive_test, 2);
    result &= recursive_test_result == recursive_test->left->left;
    delete recursive_test;

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
        UnitTest("find node", binaryTreeTestFindNode));
    test_manager->test_groups.push_back(test_group);
}
