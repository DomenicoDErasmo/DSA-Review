#include "binary_tree_tests.hpp"

#include <data_structures/binary_tree.tpp>
#include <data_structures/linked_list.tpp>
#include <iostream>
#include <sstream>

bool binaryTreeTestDefaultConstructor() {
    bool result = true;

    BinaryTree<int>* root = new BinaryTree<int>();
    result &= (root->getData() == 0);
    result &= (root->getLeft() == nullptr);
    result &= (root->getRight() == nullptr);

    delete root;
    return result;
}

bool binaryTreeTestDataConstructor() {
    bool result = true;

    BinaryTree<int>* root = new BinaryTree<int>(5);
    result &= (root->getData() == 5);
    result &= (root->getLeft() == nullptr);
    result &= (root->getRight() == nullptr);

    delete root;
    return result;
}

bool binaryTreeTestAllParamConstructor() {
    bool result = true;

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* right = new BinaryTree<int>(5);
    BinaryTree<int>* root = new BinaryTree<int>(4, left, right);
    result &= (root->getData() == 4);
    result &= (root->getLeft() == left);
    result &= (root->getRight() == right);

    delete root;
    return result;
}

bool binaryTreeTestCopyConstructor() {
    bool result = true;

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* right = new BinaryTree<int>(5);
    BinaryTree<int>* other = new BinaryTree<int>(4, left, right);
    BinaryTree<int>* root = new BinaryTree<int>(*other);
    result &= (root->getData() == 4);
    result &= (root->getLeft() == left);
    result &= (root->getRight() == right);

    return result;
}

bool binaryTreeTestDestructor() {
    bool result = true;

    BinaryTree<int>* no_children = new BinaryTree<int>(4);
    try {
        delete no_children;
    } catch(...) {
        return false;
    }

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* left_child = new BinaryTree<int>(4, left, nullptr);
    try {
        delete left_child;
    } catch(...) {
        return false;
    }

    BinaryTree<int>* right = new BinaryTree<int>(5);
    BinaryTree<int>* right_child = new BinaryTree<int>(4, nullptr, right);
    try {
        delete right_child;
    } catch(...) {
        return false;
    }

    BinaryTree<int>* left_1 = new BinaryTree<int>(3);
    BinaryTree<int>* right_1 = new BinaryTree<int>(5);
    BinaryTree<int>* both_children = new BinaryTree<int>(4, left_1, right_1);
    try {
        delete both_children;
    } catch(...) {
        return false;
    }

    return result;
}

bool binaryTreeTestInsert() {
    bool result = true;

    BinaryTree<int>* root = new BinaryTree<int>(5);
    binaryTreeInsertNode(root, 2);
    result &= (root->getLeft()->getData() == 2);
    binaryTreeInsertNode(root, 1);
    result &= (root->getLeft()->getLeft()->getData() == 1);
    binaryTreeInsertNode(root, 4);
    result &= (root->getLeft()->getRight()->getData() == 4);
    binaryTreeInsertNode(root, 8);
    result &= (root->getRight()->getData() == 8);
    binaryTreeInsertNode(root, 6);
    result &= (root->getRight()->getLeft()->getData() == 6);
    binaryTreeInsertNode(root, 9);
    result &= (root->getRight()->getRight()->getData() == 9);
    binaryTreeInsertNode(root, 5);
    result &= (root->getCount() == 2);

    return result;
}

bool binaryTreeTestGetPreOrderPredecessor() {
    bool result = true;

    BinaryTree<int>* no_left_children = new BinaryTree<int>(5);
    result &= (!binaryTreeGetPreOrderPredecessor(no_left_children));
    delete no_left_children;

    BinaryTree<int>* left_children = new BinaryTree<int>(5);
    binaryTreeInsertNode(left_children, 3);
    binaryTreeInsertNode(left_children, 2);
    binaryTreeInsertNode(left_children, 4);
    result &= (binaryTreeGetPreOrderPredecessor(left_children) == left_children->getLeft()->getRight());
    delete left_children;

    return true;
}

bool binaryTreeTestGetPreOrderSuccessor() {
    bool result = true;

    BinaryTree<int>* no_right_children = new BinaryTree<int>(5);
    result &= !binaryTreeGetPreOrderSuccessor(no_right_children);
    delete no_right_children;

    BinaryTree<int>* right_children = new BinaryTree<int>(5);
    binaryTreeInsertNode(right_children, 7);
    binaryTreeInsertNode(right_children, 6);
    binaryTreeInsertNode(right_children, 8);
    result &= (binaryTreeGetPreOrderSuccessor(right_children) == right_children->getRight()->getLeft());
    delete right_children;

    return true;
}

bool binaryTreeTestAssignmentOperator() {
    bool result = true;

    BinaryTree<int>* root = new BinaryTree<int>(3,
        new BinaryTree<int>(-5),
        new BinaryTree<int>(6));
    root->setCount(6);
    BinaryTree<int>* test = new BinaryTree<int>();
    *test = *root;

    result &= (test->getData() == root->getData());
    result &= (test->getCount() == root->getCount());
    result &= (test->getLeft()->getData() == root->getLeft()->getData());
    result &= (test->getRight()->getData() == root->getRight()->getData());
    delete root;
    delete test;

    return result;
}

bool binaryTreeTestDelete() {
    bool result = true;

    BinaryTree<int>* root_count_above_one = new BinaryTree<int>(12);
    binaryTreeInsertNode(root_count_above_one, 12);
    binaryTreeDeleteNode(root_count_above_one, 12);
    result &= (root_count_above_one->getCount() == 1);
    delete root_count_above_one;

    BinaryTree<int>* left_count_above_one = new BinaryTree<int>(12);
    binaryTreeInsertNode(left_count_above_one, 8);
    binaryTreeInsertNode(left_count_above_one, 8);
    binaryTreeDeleteNode(left_count_above_one, 8);
    result &= (left_count_above_one->getCount() == 1);
    delete left_count_above_one;

    BinaryTree<int>* right_count_above_one = new BinaryTree<int>(12);
    binaryTreeInsertNode(right_count_above_one, 15);
    binaryTreeInsertNode(right_count_above_one, 15);
    binaryTreeDeleteNode(right_count_above_one, 15);
    result &= (right_count_above_one->getCount() == 1);
    delete right_count_above_one;

    BinaryTree<int>* delete_root_no_children = new BinaryTree<int>(6);
    binaryTreeDeleteNode(delete_root_no_children, 6);
    result &= (delete_root_no_children->getCount() == 0);
    delete delete_root_no_children;

    BinaryTree<int>* delete_root_with_left_child = new BinaryTree<int>(10);
    binaryTreeInsertNode(delete_root_with_left_child, 5);
    binaryTreeInsertNode(delete_root_with_left_child, 5);
    binaryTreeDeleteNode(delete_root_with_left_child, 10);
    result &= (delete_root_with_left_child->getData() == 5);
    result &= (delete_root_with_left_child->getCount() == 2);
    result &= !delete_root_with_left_child->getLeft();
    delete delete_root_with_left_child;

    BinaryTree<int>* delete_root_with_right_child = new BinaryTree<int>(10);
    binaryTreeInsertNode(delete_root_with_right_child, 12);
    binaryTreeInsertNode(delete_root_with_right_child, 12);
    binaryTreeDeleteNode(delete_root_with_right_child, 10);
    result &= (delete_root_with_right_child->getData() == 12);
    result &= (delete_root_with_right_child->getCount() == 2);
    result &= !delete_root_with_right_child->getLeft();
    delete delete_root_with_right_child;

    BinaryTree<int>* delete_left_child = new BinaryTree<int>(10);
    binaryTreeInsertNode(delete_left_child, 5);
    binaryTreeDeleteNode(delete_left_child, 5);
    result &= !delete_left_child->getLeft();
    delete delete_left_child;

    BinaryTree<int>* delete_right_child = new BinaryTree<int>(10);
    binaryTreeInsertNode(delete_right_child, 12);
    binaryTreeDeleteNode(delete_right_child, 12);
    result &= !delete_right_child->getRight();
    delete delete_right_child;

    return result;
}

bool binaryTreeTestGetParentValueOf() {
    bool result = true;

    BinaryTree<int>* empty = nullptr;
    result &= !binaryTreeGetParentValueOf(empty, 1);

    BinaryTree<int>* equals_value = new BinaryTree<int>(5);
    result &= !binaryTreeGetParentValueOf(equals_value, 5);
    delete equals_value;

    BinaryTree<int>* root_is_parent = new BinaryTree<int>(5,
        new BinaryTree<int>(3),
        new BinaryTree<int>(7));
    result &= (binaryTreeGetParentValueOf(root_is_parent, 3) == root_is_parent);
    result &= (binaryTreeGetParentValueOf(root_is_parent, 7) == root_is_parent);
    delete root_is_parent;

    BinaryTree<int>* not_found_in_left_half = new BinaryTree<int>(5,
        new BinaryTree<int>(3),
        nullptr);
    result &= !binaryTreeGetParentValueOf(not_found_in_left_half, 4);
    delete not_found_in_left_half;

    BinaryTree<int>* not_found_in_right_half = new BinaryTree<int>(5,
        nullptr,
        new BinaryTree<int>(7));
    result &= !binaryTreeGetParentValueOf(not_found_in_right_half, 6);
    delete not_found_in_right_half;

    BinaryTree<int>* found_in_left_half = new BinaryTree<int>(5,
        new BinaryTree<int>(3, 
            new BinaryTree<int>(2),
            new BinaryTree<int>(4)),
        nullptr);
    result &= (binaryTreeGetParentValueOf(found_in_left_half, 2) == found_in_left_half->getLeft());
    delete found_in_left_half;
    BinaryTree<int>* found_in_right_half = new BinaryTree<int>(10,
        nullptr,
        new BinaryTree<int>(12, 
            new BinaryTree<int>(11),
            new BinaryTree<int>(13)));
    result &= (binaryTreeGetParentValueOf(found_in_right_half, 11) == found_in_right_half->getRight());
    delete found_in_right_half;

    return result;
}

bool binaryTreeTestToString() {
    bool result = true;

    BinaryTree<int>* no_children = new BinaryTree<int>(4);
    result += no_children->toString() == "[4]";
    delete no_children;

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* left_child = new BinaryTree<int>(4, left, nullptr);
    result += left_child->toString() == "[4, [3]]";
    delete left_child;

    BinaryTree<int>* right = new BinaryTree<int>(5);
    BinaryTree<int>* right_child = new BinaryTree<int>(4, nullptr, right);
    result += right_child->toString() == "[4, [5]]";
    delete right_child;

    BinaryTree<int>* left_1 = new BinaryTree<int>(3);
    BinaryTree<int>* right_1 = new BinaryTree<int>(5);
    BinaryTree<int>* both_children = new BinaryTree<int>(4, left_1, right_1);
    result += both_children->toString() == "[4, [3], [5]]";
    delete both_children;

    return result;
}

bool binaryTreeTestOstreamOperator() {
    bool result = true;

    BinaryTree<int>* left = new BinaryTree<int>(3);
    BinaryTree<int>* right = new BinaryTree<int>(5);
    BinaryTree<int>* root = new BinaryTree<int>(4, left, right);

    std::stringstream out;
    out << *root;
    result &= (out.str() == "[4, [3], [5]]");
    delete root;

    return result;
}

bool binaryTreeTestDifferentChildren() {
    bool result = true;
    
    BinaryTree<int>* has_left = new BinaryTree<int>(4, new BinaryTree<int>(3), nullptr);
    BinaryTree<int>* other_missing_left = new BinaryTree<int>(4, nullptr, nullptr);
    result &= (has_left->diffrentChildren(*other_missing_left));
    delete has_left;
    delete other_missing_left;
    
    BinaryTree<int>* missing_left = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(5));
    BinaryTree<int>* other_has_left = new BinaryTree<int>(4, new BinaryTree<int>(3), nullptr);
    result &= (missing_left->diffrentChildren(*other_has_left));
    delete missing_left;
    delete other_has_left;

    BinaryTree<int>* has_right = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(5));
    BinaryTree<int>* other_missing_right = new BinaryTree<int>(4, nullptr, nullptr);
    result &= (has_right->diffrentChildren(*other_missing_right));
    delete has_right;
    delete other_missing_right;
    
    BinaryTree<int>* missing_right = new BinaryTree<int>(4, nullptr, nullptr);
    BinaryTree<int>* other_has_right = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(5));
    result &= (missing_right->diffrentChildren(*other_has_right));
    delete missing_right;
    delete other_has_right;

    return result;
}

bool binaryTreeTestEqualityOperator() {
    bool result = true;

    BinaryTree<int>* different_data = new BinaryTree<int>(4);
    BinaryTree<int>* other_different_data = new BinaryTree<int>(3);
    result &= (*different_data != *other_different_data);
    delete different_data;
    delete other_different_data;

    BinaryTree<int>* different_children = new BinaryTree<int>(4, new BinaryTree<int>(3), nullptr);
    BinaryTree<int>* other_different_children = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(5));
    result &= (*different_children != *other_different_children);
    delete different_children;
    delete other_different_children;

    BinaryTree<int>* no_children = new BinaryTree<int>(4);
    BinaryTree<int>* other_no_children = new BinaryTree<int>(4);
    result &= (*no_children == *other_no_children);
    delete no_children;
    delete other_no_children;

    BinaryTree<int>* has_left = new BinaryTree<int>(4, new BinaryTree<int>(3), nullptr);
    BinaryTree<int>* other_has_left = new BinaryTree<int>(4, new BinaryTree<int>(3), nullptr);
    result &= (*has_left == *other_has_left);
    delete has_left;
    delete other_has_left;

    BinaryTree<int>* has_right = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(5));
    BinaryTree<int>* other_has_right = new BinaryTree<int>(4, nullptr, new BinaryTree<int>(6));
    result &= (*has_right != *other_has_right);
    delete has_right;
    delete other_has_right;

    return result;
}

bool binaryTreeTestPrefixOrder() {
    bool result = true;

    BinaryTree<int>* single_root = new BinaryTree<int>(6);
    LinkedList<int>* single_root_prefix = nullptr;
    binaryTreePrefixOrder(single_root, single_root_prefix);
    result &= (single_root_prefix->toString() == "6");
    delete single_root;
    delete single_root_prefix;

    BinaryTree<int>* duplicate_root = new BinaryTree<int>(6);
    binaryTreeInsertNode(duplicate_root, 6);
    LinkedList<int>* duplicate_root_prefix = nullptr;
    binaryTreePrefixOrder(duplicate_root, duplicate_root_prefix);
    result &= (duplicate_root_prefix->toString() == "6, 6");
    delete duplicate_root;
    delete duplicate_root_prefix;

    BinaryTree<int>* has_left = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left, 4);
    LinkedList<int>* has_left_prefix = nullptr;
    binaryTreePrefixOrder(has_left, has_left_prefix);
    result &= (has_left_prefix->toString() == "6, 4");
    delete has_left;
    delete has_left_prefix;

    BinaryTree<int>* has_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_right, 8);
    LinkedList<int>* has_right_prefix = nullptr;
    binaryTreePrefixOrder(has_right, has_right_prefix);
    result &= (has_right_prefix->toString() == "6, 8");
    delete has_right;
    delete has_right_prefix;

    BinaryTree<int>* has_left_and_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left_and_right, 4);
    binaryTreeInsertNode(has_left_and_right, 8);
    LinkedList<int>* has_left_and_right_prefix = nullptr;
    binaryTreePrefixOrder(has_left_and_right, has_left_and_right_prefix);
    result &= (has_left_and_right_prefix->toString() == "6, 4, 8");
    delete has_left_and_right;
    delete has_left_and_right_prefix;

    BinaryTree<int>* root_and_left_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_left_duplicate, 6);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    LinkedList<int>* root_and_left_duplicate_prefix = nullptr;
    binaryTreePrefixOrder(root_and_left_duplicate, root_and_left_duplicate_prefix);
    result &= (root_and_left_duplicate_prefix->toString() == "6, 6, 4, 4");
    delete root_and_left_duplicate;
    delete root_and_left_duplicate_prefix;

    BinaryTree<int>* root_and_right_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_right_duplicate, 6);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    LinkedList<int>* root_and_right_duplicate_prefix = nullptr;
    binaryTreePrefixOrder(root_and_right_duplicate, root_and_right_duplicate_prefix);
    result &= (root_and_right_duplicate_prefix->toString() == "6, 6, 8, 8");
    delete root_and_right_duplicate;
    delete root_and_right_duplicate_prefix;

    return result;
}

bool binaryTreeTestInfixOrder() {
    bool result = true;

    BinaryTree<int>* single_root = new BinaryTree<int>(6);
    LinkedList<int>* single_root_prefix = nullptr;
    binaryTreeInfixOrder(single_root, single_root_prefix);
    result &= (single_root_prefix->toString() == "6");
    delete single_root;
    delete single_root_prefix;

    BinaryTree<int>* duplicate_root = new BinaryTree<int>(6);
    binaryTreeInsertNode(duplicate_root, 6);
    LinkedList<int>* duplicate_root_prefix = nullptr;
    binaryTreeInfixOrder(duplicate_root, duplicate_root_prefix);
    result &= (duplicate_root_prefix->toString() == "6, 6");
    delete duplicate_root;
    delete duplicate_root_prefix;

    BinaryTree<int>* has_left = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left, 4);
    LinkedList<int>* has_left_prefix = nullptr;
    binaryTreeInfixOrder(has_left, has_left_prefix);
    result &= (has_left_prefix->toString() == "4, 6");
    delete has_left;
    delete has_left_prefix;

    BinaryTree<int>* has_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_right, 8);
    LinkedList<int>* has_right_prefix = nullptr;
    binaryTreeInfixOrder(has_right, has_right_prefix);
    result &= (has_right_prefix->toString() == "6, 8");
    delete has_right;
    delete has_right_prefix;

    BinaryTree<int>* has_left_and_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left_and_right, 4);
    binaryTreeInsertNode(has_left_and_right, 8);
    LinkedList<int>* has_left_and_right_prefix = nullptr;
    binaryTreeInfixOrder(has_left_and_right, has_left_and_right_prefix);
    result &= (has_left_and_right_prefix->toString() == "4, 6, 8");
    delete has_left_and_right;
    delete has_left_and_right_prefix;

    BinaryTree<int>* root_and_left_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_left_duplicate, 6);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    LinkedList<int>* root_and_left_duplicate_prefix = nullptr;
    binaryTreeInfixOrder(root_and_left_duplicate, root_and_left_duplicate_prefix);
    result &= (root_and_left_duplicate_prefix->toString() == "4, 4, 6, 6");
    delete root_and_left_duplicate;
    delete root_and_left_duplicate_prefix;

    BinaryTree<int>* root_and_right_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_right_duplicate, 6);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    LinkedList<int>* root_and_right_duplicate_prefix = nullptr;
    binaryTreeInfixOrder(root_and_right_duplicate, root_and_right_duplicate_prefix);
    result &= (root_and_right_duplicate_prefix->toString() == "6, 6, 8, 8");
    delete root_and_right_duplicate;
    delete root_and_right_duplicate_prefix;

    return result;
}

bool binaryTreeTestPostfixOrder() {
    bool result = true;

    BinaryTree<int>* single_root = new BinaryTree<int>(6);
    LinkedList<int>* single_root_prefix = nullptr;
    binaryTreePostfixOrder(single_root, single_root_prefix);
    result &= (single_root_prefix->toString() == "6");
    delete single_root;
    delete single_root_prefix;

    BinaryTree<int>* duplicate_root = new BinaryTree<int>(6);
    binaryTreeInsertNode(duplicate_root, 6);
    LinkedList<int>* duplicate_root_prefix = nullptr;
    binaryTreePostfixOrder(duplicate_root, duplicate_root_prefix);
    result &= (duplicate_root_prefix->toString() == "6, 6");
    delete duplicate_root;
    delete duplicate_root_prefix;

    BinaryTree<int>* has_left = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left, 4);
    LinkedList<int>* has_left_prefix = nullptr;
    binaryTreePostfixOrder(has_left, has_left_prefix);
    result &= (has_left_prefix->toString() == "4, 6");
    delete has_left;
    delete has_left_prefix;

    BinaryTree<int>* has_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_right, 8);
    LinkedList<int>* has_right_prefix = nullptr;
    binaryTreePostfixOrder(has_right, has_right_prefix);
    result &= (has_right_prefix->toString() == "8, 6");
    delete has_right;
    delete has_right_prefix;

    BinaryTree<int>* has_left_and_right = new BinaryTree<int>(6);
    binaryTreeInsertNode(has_left_and_right, 4);
    binaryTreeInsertNode(has_left_and_right, 8);
    LinkedList<int>* has_left_and_right_prefix = nullptr;
    binaryTreePostfixOrder(has_left_and_right, has_left_and_right_prefix);
    result &= (has_left_and_right_prefix->toString() == "4, 8, 6");
    delete has_left_and_right;
    delete has_left_and_right_prefix;

    BinaryTree<int>* root_and_left_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_left_duplicate, 6);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    binaryTreeInsertNode(root_and_left_duplicate, 4);
    LinkedList<int>* root_and_left_duplicate_prefix = nullptr;
    binaryTreePostfixOrder(root_and_left_duplicate, root_and_left_duplicate_prefix);
    result &= (root_and_left_duplicate_prefix->toString() == "4, 4, 6, 6");
    delete root_and_left_duplicate;
    delete root_and_left_duplicate_prefix;

    BinaryTree<int>* root_and_right_duplicate = new BinaryTree<int>(6);
    binaryTreeInsertNode(root_and_right_duplicate, 6);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    binaryTreeInsertNode(root_and_right_duplicate, 8);
    LinkedList<int>* root_and_right_duplicate_prefix = nullptr;
    binaryTreePostfixOrder(root_and_right_duplicate, root_and_right_duplicate_prefix);
    result &= (root_and_right_duplicate_prefix->toString() == "8, 8, 6, 6");
    delete root_and_right_duplicate;
    delete root_and_right_duplicate_prefix;

    return result;
}

TestGroup binaryTreeRegisterTests() {
    TestGroup test_group("binary trees");
    test_group.addTest(UnitTest(binaryTreeTestDefaultConstructor, "default constructor"));
    test_group.addTest(UnitTest(binaryTreeTestDataConstructor, "data constructor"));
    test_group.addTest(UnitTest(binaryTreeTestAllParamConstructor, "all param constructor"));
    test_group.addTest(UnitTest(binaryTreeTestCopyConstructor, "copy constructor"));
    test_group.addTest(UnitTest(binaryTreeTestDestructor, "destructor"));
    test_group.addTest(UnitTest(binaryTreeTestInsert, "insert"));
    test_group.addTest(UnitTest(binaryTreeTestGetPreOrderPredecessor, "get preorder predecessor"));
    test_group.addTest(UnitTest(binaryTreeTestGetPreOrderSuccessor, "get preorder successor"));
    test_group.addTest(UnitTest(binaryTreeTestAssignmentOperator, "assignment operator"));
    test_group.addTest(UnitTest(binaryTreeTestDelete, "delete node"));
    test_group.addTest(UnitTest(binaryTreeTestGetParentValueOf, "get parent value of"));
    test_group.addTest(UnitTest(binaryTreeTestToString, "to string"));
    test_group.addTest(UnitTest(binaryTreeTestOstreamOperator, "ostream operator"));
    test_group.addTest(UnitTest(binaryTreeTestDifferentChildren, "different children"));
    test_group.addTest(UnitTest(binaryTreeTestEqualityOperator, "equality operator"));
    test_group.addTest(UnitTest(binaryTreeTestPrefixOrder, "prefix order"));
    test_group.addTest(UnitTest(binaryTreeTestInfixOrder, "infix order"));
    test_group.addTest(UnitTest(binaryTreeTestPostfixOrder, "postfix order"));
    return test_group;
}