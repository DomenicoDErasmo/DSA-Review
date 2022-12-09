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

bool binaryTreeTestGetSize() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= binaryTreeGetSize(empty) == 0;

    BinaryTree<int>* leaf = new BinaryTree<int>(4);
    result &= binaryTreeGetSize(leaf) == 1;
    delete leaf;

    BinaryTree<int>* children = new BinaryTree<int>(5,
        new BinaryTree<int>(2),
        new BinaryTree<int>(6));
    result &= binaryTreeGetSize(children) == 3;
    delete children;

    BinaryTree<int>* grandchildren = new BinaryTree<int>(5,
        new BinaryTree<int>(2,
            new BinaryTree<int>(1),
            nullptr),
        new BinaryTree<int>(7));
    result &= binaryTreeGetSize(grandchildren) == 4;
    result &= binaryTreeGetSize(grandchildren->left) == 2;
    delete grandchildren;

    return result;
}

void binaryTreeTestsRegisterTests(TestManager* test_manager) {
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
        UnitTest("get size", binaryTreeTestGetSize));
    test_manager->test_groups.push_back(test_group);
;}
