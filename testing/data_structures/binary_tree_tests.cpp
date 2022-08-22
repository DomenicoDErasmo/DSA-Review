#include "binary_tree_tests.hpp"

/**
 * @brief Builds a test tree for unit tests
 * 
 * @return A binary tree of integers
 */
BinaryTree<int> buildTestTree() {
    BinaryTree<int> tree(15);
    tree.addNode(3);
    tree.addNode(1);
    tree.addNode(2);
    tree.addNode(6);
    tree.addNode(22);
    return tree;
}

/**
 * @brief Tests that we build prefix order
 * 
 * @return true if all tests succeed, otherwise false
 */
bool testPrefixOrder() {
    bool result = true;

    BinaryTree<int> tree;
    tree = buildTestTree();

    LinkedList<int> prefix_order;
    prefix_order = tree.prefixOrder();

    LinkedList<int> expected_list(15);
    expected_list.insertAtTail(3);
    expected_list.insertAtTail(1);
    expected_list.insertAtTail(2);
    expected_list.insertAtTail(6);
    expected_list.insertAtTail(22);

    return result &= (prefix_order == expected_list);
}

/**
 * @brief Tests that we build postfix order
 * 
 * @return true if all tests succeed, otherwise false
 */
bool testPostfixOrder() {
    bool result = true;

    BinaryTree<int> tree;
    tree = buildTestTree();

    LinkedList<int> postfix_order;
    postfix_order = tree.postfixOrder();

    LinkedList<int> expected_list(22);
    expected_list.insertAtTail(15);
    expected_list.insertAtTail(6);
    expected_list.insertAtTail(3);
    expected_list.insertAtTail(2);
    expected_list.insertAtTail(1);

    return result &= (postfix_order == expected_list);
}

/**
 * @brief Tests that we build infix order
 * 
 * @return true if all tests succeed, otherwise false
 */
bool testInfixOrder() {
    bool result = true;

    BinaryTree<int> tree;
    tree = buildTestTree();

    LinkedList<int> infix_order;
    infix_order = tree.infixOrder();

    LinkedList<int> expected_list(1);
    expected_list.insertAtTail(2);
    expected_list.insertAtTail(3);
    expected_list.insertAtTail(6);
    expected_list.insertAtTail(15);
    expected_list.insertAtTail(22);

    return result &= (infix_order == expected_list);
}

/**
 * @brief Tests the equality operator
 * 
 * @return true if all tests succeed, otherwise false
 */
bool testTreeEquality() {
    bool result = true;

    BinaryTree<int> tree;
    tree = buildTestTree();

    BinaryTree<int> equals_tree;
    equals_tree = buildTestTree();

    result &= (tree == equals_tree);

    BinaryTree<int> left_missing(5);
    left_missing.addNode(6);

    BinaryTree<int> left_missing_not_equal(5);
    left_missing_not_equal.addNode(4);
    left_missing_not_equal.addNode(6);

    result &= (left_missing != left_missing_not_equal);

    BinaryTree<int> right_missing(5);
    right_missing.addNode(4);

    BinaryTree<int> right_missing_not_equal(5);
    right_missing_not_equal.addNode(4);
    right_missing_not_equal.addNode(6);

    result &= (right_missing != right_missing_not_equal);

    BinaryTree<int> different_vals(5);

    BinaryTree<int> different_vals_not_equal(6);

    result &= (different_vals != different_vals_not_equal);

    BinaryTree<int> different_left(5);
    different_left.addNode(4);

    BinaryTree<int> different_left_not_equal(5);
    different_left_not_equal.addNode(3);

    result &= (different_left != different_left_not_equal);

    BinaryTree<int> different_right(5);
    different_right.addNode(6);

    BinaryTree<int> different_right_not_equal(5);
    different_right_not_equal.addNode(7);

    result &= (different_right != different_right_not_equal);

    return result;
}

/**
 * @brief Adds all tests defined in this file to the provided test manager
 * 
 * @param test_manager The test manager that will run all tests
 */
void registerBinaryTreeTests(TestManager& test_manager) {
    test_manager.addTest(Test(testPrefixOrder, "Test prefix order"));
    test_manager.addTest(Test(testPostfixOrder, "Test postfix order"));
    test_manager.addTest(Test(testInfixOrder, "Test infix order"));
    test_manager.addTest(Test(testTreeEquality, "Test tree equality"));
}