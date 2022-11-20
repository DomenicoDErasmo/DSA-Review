#ifndef BINARY_TREE_TPP
#define BINARY_TREE_TPP

#include <iostream>
#include "linked_list.cpp"

template <typename T>
struct BinaryTree {
public:
    // Constructors
    BinaryTree(): data(T()), left(nullptr), right(nullptr), count(1) {}
    BinaryTree(T in_data): data(in_data), left(nullptr), right(nullptr), count(1) {}
    BinaryTree(T in_data, BinaryTree* in_left, BinaryTree* in_right): data(in_data), left(in_left), right(in_right), count(1) {}
    BinaryTree(const BinaryTree& other): data(other.data), left(other.left), right(other.right), count(1) {}
    ~BinaryTree() {
        delete left;
        delete right;
    }

    // Utility Functions
    std::string to_string() const {
        // Only works for types in which the underlying data type works with to_string
        std::string result = "[" + std::to_string(data);
        if (left) {result += (", " + left->to_string());}
        if (right) {result += (", " + right->to_string());}
        return result + "]";
    }

    // Operators
    friend std::ostream& operator << (std::ostream& out, const BinaryTree<T>& root) {
        out << root.to_string();
        return out;
    }

    bool differentChildren(const BinaryTree<T>& other) {
        return (left and !other.left) 
        or (!left and other.left) 
        or (right and !other.right) 
        or (!right and other.right);
    }

    void operator = (const BinaryTree<T>& rhs) {
        data = rhs.data;
        count = rhs.count;
        if (left) {delete left;}
        left = new BinaryTree<T>(*rhs.left);
        if (right) {delete right;}
        right = new BinaryTree<T>(*rhs.right);
    }

    const bool operator == (const BinaryTree<T>& other) {
        if (data != other.data or differentChildren(other)) {
            return false;
        } else if (!left and !right and !other.left and !other.right) {
            return data == other.data;
        } else {
            bool result = true;
            if (left and other.left) {
                result &= (*left == *other.left);
            }
            if (right and other.right) {
                result &= (*right == *other.right);
            }
            return result;
        }
    }

    const bool operator < (const BinaryTree<T>& other) {
        return data < other.data;
    }

    const bool operator > (const BinaryTree<T>& other) {
        return data > other.data;
    }

    const bool operator != (const BinaryTree<T>& other) {
        return !(*this == other);
    }

    // Data Members
    T data;
    BinaryTree<T>* left;
    BinaryTree<T>* right;
    int count;
};

template <typename T>
/**
 * @brief Creates a BinaryTree node and inserts it into the tree
 * 
 * @param root A reference to a pointer of the binary tree to insert into
 * @param data_to_insert Data of some arbitrary type to be inserted
 */
void binaryTreeInsertNode(BinaryTree<T>*& root, T data_to_insert) {
    if (!root) {
        root = new BinaryTree<T>(data_to_insert);
        return;
    }
    
    // We should only hit this if the tree was empty from a previous deletion
    if (!root->left and !root->right and root->count == 0) {
        root->data = data_to_insert;
        root->count = 1;
        return;
    }

    BinaryTree<T>* temp = root;
    while(true) {
        if (data_to_insert < temp->data) {
            if (!temp->left) {
                temp->left = new BinaryTree<T>(data_to_insert);
                return;
            } else {
                temp = temp->left;
            }
        } else if (data_to_insert == temp->data) {
            temp->count++;
            return;
        } else {
            if (!temp->right) {
                temp->right = new BinaryTree<T>(data_to_insert);
                return;
            } else {
                temp = temp->right;
            }
        }
    }
}

template <typename T>
/**
 * @brief Get the preorder predecessor of the tree node
 * 
 * @param root A pointer to a binary tree node
 * @return BinaryTree<T>* A pointer to the preorder predecessor
 */
BinaryTree<T>* binaryTreeGetPreOrderPredecessor(BinaryTree<T>* root) {
    if (!root->left) {return nullptr;}
    BinaryTree<T>* temp = root->left;
    while(temp->right) {
        temp = temp->right;
    }
    return temp;
}

template <typename T>
/**
 * @brief Get the post order successor of the tree node
 * 
 * @param root A pointer to a binary tree node
 * @return BinaryTree<T>* A pointer to the postorder predecessor
 */
BinaryTree<T>* binaryTreeGetPreOrderSuccessor(BinaryTree<T>* root) {
    if (!root->right) {return nullptr;}
    BinaryTree<T>* temp = root->right;
    while(temp->left) {
        temp = temp->left;
    }
    return temp;
}

template <typename T>
/**
 * @brief Gets the parent node of the value, if the value exists in the list
 * 
 * @param root A pointer to a binary tree
 * @param data The data to find the parent of
 * @return BinaryTree<T>* A pointer to a tree node, or nullptr if the value isn't in the tree
 */
BinaryTree<T>* binaryTreeGetParentValueOf(BinaryTree<T>* root, T data) {
    if (!root or root->data == data) {return nullptr;}

    BinaryTree<T>* temp = root;
    while(temp) {
        BinaryTree<T> *left = temp->left, *right = temp->right;
        if ((left and left->data == data) or (right and right->data == data)) {
            return temp;
        } else if (data < temp->data) {
            temp = left;
        } else {
            temp = right;
        }
    }
    return nullptr;
}

template <typename T>
/**
 * @brief Searches for a node in the tree
 * 
 * @param root A pointer to the tree to search
 * @param data The data to search within the tree
 * @return BinaryTree<T>* A pointer to a tree node or nullptr if not found
 */
BinaryTree<T>* binaryTreeFindNode(BinaryTree<T>* root, T data) {
    BinaryTree<T>* temp = root;
    while(data != temp->data) {
        if (data < temp->data) {
            if (temp->left) {
                temp = temp->left;
            } else {
                return nullptr;
            }
        } else if (data > temp->data) {
            if (temp->right) {
                temp = temp->right;
            } else {
                return nullptr;
            }
        }
    }
    return temp;
}

template <typename T>
/**
 * @brief Searches for a node in the tree and deletes it if found
 * 
 * @param root A reference to a pointer to the tree to delete from
 * @param data Data of some arbitrary type to delete from the tree
 */
void binaryTreeDeleteNode(BinaryTree<T>*& root, T data_to_delete) {
    // Find the node
    // Promote one child to occupy the vacancy
    // Set the oppostie child as a child that was promoted
    // Delete the node

    BinaryTree<T>* temp = binaryTreeFindNode(root, data_to_delete);
    temp->count--;
    if (temp->count > 0) {return;}
    if (temp == root and !temp->left and !temp->right) {return;}

    if (temp->left) {
        // Set new head to data from the rightmost left element
        BinaryTree<T>* new_parent_info = binaryTreeGetPreOrderPredecessor(temp);
        BinaryTree<T>* parent_of_new_parent_info = binaryTreeGetParentValueOf(root, new_parent_info->data);
        temp->data = new_parent_info->data;
        temp->count = new_parent_info->count;

        if (new_parent_info->left) {
            // If the rightmost node has a child, which has to be a left child,
            // set its contents to the rightmost node and delete the left child
            BinaryTree<T>* to_delete = new_parent_info->left;
            *new_parent_info = *to_delete;

            to_delete->left = nullptr;
            to_delete->right = nullptr;
            delete to_delete;
        } else {
            // The rightmost node has no children, so we can safely delete
            delete parent_of_new_parent_info->left;
            parent_of_new_parent_info->left = nullptr;
        }
    } else if (temp->right) {
        // Set new head to data from the leftmost right element
        BinaryTree<T>* new_parent_info = binaryTreeGetPreOrderSuccessor(temp);
        BinaryTree<T>* parent_of_new_parent_info = binaryTreeGetParentValueOf(root, new_parent_info->data);
        temp->data = new_parent_info->data;
        temp->count = new_parent_info->count;

        if (new_parent_info->right) {
            // If the leftmost node has a child, which has to be a right child,
            // set its contents to the leftmost node and delete the right child
            BinaryTree<T>* to_delete = new_parent_info->right;
            *new_parent_info = *to_delete;

            to_delete->left = nullptr;
            to_delete->right = nullptr;
            delete to_delete;
        } else {
            // The rightmost node has no children, so we can safely delete
            delete parent_of_new_parent_info->right;
            parent_of_new_parent_info->right = nullptr;
        }
    } else {
        BinaryTree<T>* parent = binaryTreeGetParentValueOf(root, temp->data);
        if (temp->data < parent->data) {
            delete parent->left;
            parent->left = nullptr;
        } else {
            delete parent->right;
            parent->right = nullptr;
        }
    }
}

template <typename T>
void binaryTreePrefixOrder(BinaryTree<T>* root, LinkedList<T>*& list) {
    // Prefix order: root, left, right
    for (size_t i = 0; i < root->count; i++) {
        linkedListInsertAtTail(list, root->data);
    }
    if (root->left) {
        binaryTreePrefixOrder(root->left, list);
    }
    if (root->right) {
        binaryTreePrefixOrder(root->right, list);
    }
}

template <typename T>
void  binaryTreeInfixOrder(BinaryTree<T>* root, LinkedList<T>*& list) {
    // Infix order: left, root, right
    if (root->left) {
        binaryTreeInfixOrder(root->left, list);
    }
    for (size_t i = 0; i < root->count; i++) {
        linkedListInsertAtTail(list, root->data);
    }
    if (root->right) {
        binaryTreeInfixOrder(root->right, list);
    }
}

template <typename T>
void  binaryTreePostfixOrder(BinaryTree<T>* root, LinkedList<T>*& list) {
    // Infix order: left, right, root
    if (root->left) {
        binaryTreePostfixOrder(root->left, list);
    }
    if (root->right) {
        binaryTreePostfixOrder(root->right, list);
    }
    for (size_t i = 0; i < root->count; i++) {
        linkedListInsertAtTail(list, root->data);
    }
}

template <typename T>
void binaryTreeBreadthFirstTraversal(BinaryTree<T>* root, LinkedList<T>*& list) {
    // TODO: use queue
}

template <typename T>
void binaryTreeDepthFirstTraversal(BinaryTree<T>* root, LinkedList<T>*& list) {
    // TODO: use stack
}
 
#endif