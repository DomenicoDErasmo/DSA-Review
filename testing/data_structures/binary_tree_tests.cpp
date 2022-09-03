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

TestGroup binaryTreeRegisterTests() {
    TestGroup test_group("binary trees");
    test_group.addTest(UnitTest(binaryTreeTestDefaultConstructor, "default constructor"));
    test_group.addTest(UnitTest(binaryTreeTestDataConstructor, "data constructor"));
    test_group.addTest(UnitTest(binaryTreeTestAllParamConstructor, "all param constructor"));
    test_group.addTest(UnitTest(binaryTreeTestCopyConstructor, "copy constructor"));
    test_group.addTest(UnitTest(binaryTreeTestDestructor, "destructor"));
    test_group.addTest(UnitTest(binaryTreeTestToString, "to string"));
    test_group.addTest(UnitTest(binaryTreeTestOstreamOperator, "ostream operator"));
    return test_group;
}