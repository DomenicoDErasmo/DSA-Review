#ifndef BINARY_TREE_TPP
#define BINARY_TREE_TPP

#include <iostream>
#include <string>

#include "linked_list.tpp"

template <typename T>
class TreeNode {
public:
    // Constructors
    TreeNode(): data(T()), left(nullptr), right(nullptr) {}
    TreeNode(T in_data): data(in_data), left(nullptr), right(nullptr) {}
    TreeNode(T in_data, TreeNode* in_left, TreeNode* in_right): data(in_data), left(in_left), right(in_right) {}

    // Destructor
    ~TreeNode() {
        if (left) {
            delete left;
        }
        if (right) {
            delete right;
        }
    }

    // Getters
    T getData() {return data;}
    TreeNode<T>* getLeft() {return left;}
    TreeNode<T>* getRight() {return right;}

    // Setters
    void setData(T in_data) {data = in_data;}
    void setLeft(TreeNode<T>* in_left) {left = in_left;}
    void setRight(TreeNode<T>* in_right) {right = in_right;}

    // Utility Functions
    bool operator == (const TreeNode<T>& rhs) {return data == rhs.getData();}
    bool operator != (const TreeNode<T>& rhs) {return data != rhs.getData();}

private:
    T data;
    TreeNode* left;
    TreeNode* right;
};

template <typename T>
class BinaryTree {
public:
    // Constructors
    BinaryTree(): head(new TreeNode<T>()) {}
    BinaryTree(T data): head(new TreeNode<T>(data)) {}
    BinaryTree(BinaryTree<T>& original): head(original.getHead()) {}

    // Destructors
    ~BinaryTree() {
        if (head) {
            delete head;
        }
    }

    // Getters
    TreeNode<T>* getHead() {return head;}

    // Setters
    void setHead(TreeNode<T>* in_head) {head = in_head}

    // Utility functions

    /**
     * @brief Adds a node to the binary tree. Because the tree is sorted, we use binary search to find where to put the node.
     * 
     * @param data The data to insert into the node.
     */
    void addNode(T data) {
        TreeNode<T>* temp = head;
        while (true) {
            if (data < temp->getData()) {
                if (temp->getLeft()) {
                    temp = temp->getLeft();
                } else {
                    temp->setLeft(new TreeNode<T>(data));
                    return;
                }
            } else if (data > temp->getData()) {
                if (temp->getRight()) {
                    temp = temp->getRight();
                } else {
                    temp->setRight(new TreeNode<T>(data));
                    return;
                }
            } else {
                return;
            }
        }
    }

    /**
     * @brief Returns prefix order for the tree.
     * 
     * @return LinkedList<T> A list representing the nodes of the tree in prefix order.
     */
    LinkedList<T> prefixOrder() {
        LinkedList<T> list;
        prefixOrderHelper(list, head);
        return list;
    }

    /**
     * @brief Returns prefix order for the tree. Prefix order is when we access elements in order of node, then left, then right.
     * So why do we access in reverse order? We insert at the head due to performance benefit (O(1) vs O(N)), so we reverse the order of access.
     * 
     * @param list The linked list to populate.
     * @param node A tree node.
     */
    void prefixOrderHelper(LinkedList<T>& list, TreeNode<T>* node) {
        if (node) {
            prefixOrderHelper(list, node->getRight());
            prefixOrderHelper(list, node->getLeft());
            list.insertAtHead(node->getData());
        }
    }

    /**
     * @brief Returns postfix order for the tree.
     * 
     * @return LinkedList<T> A list representing the nodes of the tree in postfix order.
     */
    LinkedList<T> postfixOrder() {
        LinkedList<T> list;
        postfixOrderHelper(list, head);
        return list;
    }

    /**
     * @brief Returns postfix order for the tree. Postfix order is when we access elements in order of right, then node, then left.
     * So why do we access in reverse order? We insert at the head due to performance benefit (O(1) vs O(N)), so we reverse the order of access.
     * 
     * @param list The linked list to populate.
     * @param node A tree node.
     */
    void postfixOrderHelper(LinkedList<T>& list, TreeNode<T>* node) {
        if (node) {
            postfixOrderHelper(list, node->getLeft());
            list.insertAtHead(node->getData());
            postfixOrderHelper(list, node->getRight());
        }
    }

    /**
     * @brief Returns infix order for the tree.
     * 
     * @return LinkedList<T> A list representing the nodes of the tree in infix order.
     */
    LinkedList<T> infixOrder() {
        LinkedList<T> list;
        infixOrderHelper(list, head);
        return list;
    }

    /**
     * @brief Returns infix order for the tree. Infix order is when we access elements in order of left, then node, then right.
     * So why do we access in reverse order? We insert at the head due to performance benefit (O(1) vs O(N)), so we reverse the order of access.
     * 
     * @param list The linked list to populate.
     * @param node A tree node.
     */
    void infixOrderHelper(LinkedList<T>& list, TreeNode<T>* node) {
        if (node) {
            infixOrderHelper(list, node->getRight());
            list.insertAtHead(node->getData());
            infixOrderHelper(list, node->getLeft());
        }
    }

    bool operator == (BinaryTree<T>& rhs) {return internalCompare(head, rhs.getHead());}
    bool operator != (BinaryTree<T>& rhs) {return !internalCompare(head, rhs.getHead());}

private:
    TreeNode<T>* head;

    /**
     * @brief Checks if the tree nodes have different null children, i.e. if only one of the tree nodes has a left child or if only one of the trees has a right child.
     * 
     * @param lhs A tree node.
     * @param rhs A tree node from some other tree.
     * @return true if only one of the nodes has a left child or if only one of the nodes has a right child, otherwise false.
     */
    bool differentNullChildren(TreeNode<T>* lhs, TreeNode<T>* rhs) {
        return ((!lhs->getLeft() and rhs->getLeft()) or (lhs->getLeft() and !lhs->getRight())) or ((!lhs->getRight() and rhs->getRight()) or (lhs->getRight() and !rhs->getRight()));
    }

    /**
     * @brief Runs internal recursive comparison logic to check if the two tree nodes are equal. We separate this function from the equality operator due to having a separate class to mark the head of the tree.
     * 
     * @param lhs A tree node.
     * @param rhs A tree node from some other tree.
     * @return true if the trees are equal, otherwise false.
     */
    bool internalCompare(TreeNode<T>* lhs, TreeNode<T>* rhs) {
        bool guard = differentNullChildren(lhs, rhs);
        if (!lhs->getLeft() and !lhs->getRight() and !rhs->getLeft() and !rhs->getRight()) {
            return lhs->getData() == rhs->getData();
        } else if (differentNullChildren(lhs, rhs)) {
            return false;
        }
        bool result = true;

        if (lhs->getLeft() and rhs->getLeft()) {
            result &= internalCompare(lhs->getLeft(), rhs->getLeft());
        }
        if (lhs->getRight() and rhs->getRight()) {
            result &= internalCompare(lhs->getRight(), rhs->getRight());
        }

        return result;
    }
};

#endif