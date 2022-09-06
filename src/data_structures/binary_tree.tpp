#ifndef BINARY_TREE_TPP
#define BINARY_TREE_TPP

#include <iostream>

template <typename T>
class BinaryTree {
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
    // Getters
    T getData() const {return data;}
    BinaryTree* getLeft() const {return left;}
    BinaryTree* getRight() const {return right;}
    int getCount() const {return count;}

    // Setters
    void setData(T in_data) {data = in_data;}
    void setLeft(BinaryTree* in_left) {left = in_left;}
    void setRight(BinaryTree* in_right) {right = in_right;}
    void setCount(int in_count) {count = in_count;}

    // Utility Functions
    std::string toString() const {
        std::string result = "[" + std::to_string(data);
        if (left) {result += (", " + left->toString());}
        if (right) {result += (", " + right->toString());}
        return result + "]";
    }

    friend std::ostream& operator << (std::ostream& out, const BinaryTree<int>& root) {
        out << root.toString();
        return out;
    }

    bool diffrentChildren(const BinaryTree<T>& other) {
        return (left and !other.getLeft()) 
        or (!left and other.getLeft()) 
        or (right and !other.getRight()) 
        or (!right and other.getRight());
    }

    void operator = (const BinaryTree<T>& rhs) {
        data = rhs.getData();
        count = rhs.getCount();
        if (left) {delete left;}
        left = new BinaryTree<T>(*rhs.getLeft());
        if (right) {delete right;}
        right = new BinaryTree<T>(*rhs.getRight());
    }

    const bool operator == (const BinaryTree<T>& other) {
        if (data != other.getData() or diffrentChildren(other)) {
            return false;
        } else if (!left and !right and !other.getLeft() and !other.getRight()) {
            return data == other.getData();
        } else {
            bool result = true;
            if (left and other.getLeft()) {
                result &= (*left == *other.getLeft());
            }
            if (right and other.getRight()) {
                result &= (*right == *other.getRight());
            }
            return result;
        }
    }

    const bool operator != (const BinaryTree<T>& other) {
        return !(*this == other);
    }

private:
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
 * @param data Data of some arbitrary type to be inserted
 */
void binaryTreeInsertNode(BinaryTree<T>*& root, T data_to_insert) {
    // We should only hit this if the tree was empty from a previous deletion
    if (!root->getLeft() and !root->getRight() and root->getCount() == 0) {
        root->setData(data_to_insert);
        root->setCount(1);
        return;
    }

    BinaryTree<T>* temp = root;
    while(true) {
        if (data_to_insert < temp->getData()) {
            if (!temp->getLeft()) {
                temp->setLeft(new BinaryTree<T>(data_to_insert));
                return;
            } else {
                temp = temp->getLeft();
            }
        } else if (data_to_insert == temp->getData()) {
            temp->setCount(temp->getCount() + 1);
            return;
        } else {
            if (!temp->getRight()) {
                temp->setRight(new BinaryTree<T>(data_to_insert));
                return;
            } else {
                temp = temp->getRight();
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
    if (!root->getLeft()) {return nullptr;}
    BinaryTree<T>* temp = root->getLeft();
    while(temp->getRight()) {
        temp = temp->getRight();
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
    if (!root->getRight()) {return nullptr;}
    BinaryTree<T>* temp = root->getRight();
    while(temp->getLeft()) {
        temp = temp->getLeft();
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
    if (!root or root->getData() == data) {return nullptr;}

    BinaryTree<T>* temp = root;
    while(temp) {
        BinaryTree<T> *left = temp->getLeft(), *right = temp->getRight();
        if ((left and left->getData() == data) or (right and right->getData() == data)) {
            return temp;
        } else if (data < temp->getData()) {
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
    while(data != temp->getData()) {
        if (data < temp->getData()) {
            if (temp->getLeft()) {
                temp = temp->getLeft();
            } else {
                return nullptr;
            }
        } else if (data > temp->getData()) {
            if (temp->getRight()) {
                temp = temp->getRight();
            } else {
                return nullptr;
            }
        }
    }
    return temp;
}

template <typename T>
struct TreeAccessors {
    T (*getter)();
    void (*setter)(T param);
};

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
    temp->setCount(temp->getCount() - 1);
    if (temp->getCount() > 0) {return;}
    if (temp == root and !temp->getLeft() and !temp->getRight()) {return;}

    if (temp->getLeft()) {
        // Set new head to data from the rightmost left element
        BinaryTree<T>* new_parent_info = binaryTreeGetPreOrderPredecessor(temp);
        BinaryTree<T>* parent_of_new_parent_info = binaryTreeGetParentValueOf(root, new_parent_info->getData());
        temp->setData(new_parent_info->getData());
        temp->setCount(new_parent_info->getCount());

        if (new_parent_info->getLeft()) {
            // If the rightmost node has a child, which has to be a left child,
            // set its contents to the rightmost node and delete the left child
            BinaryTree<T>* to_delete = new_parent_info->getLeft();
            *new_parent_info = *to_delete;

            to_delete->setLeft(nullptr);
            to_delete->setRight(nullptr);
            delete to_delete;
        } else {
            // The rightmost node has no children, so we can safely delete
            delete parent_of_new_parent_info->getLeft();
            parent_of_new_parent_info->setLeft(nullptr);
        }
    } else if (temp->getRight()) {
        // Set new head to data from the leftmost right element
        BinaryTree<T>* new_parent_info = binaryTreeGetPreOrderSuccessor(temp);
        BinaryTree<T>* parent_of_new_parent_info = binaryTreeGetParentValueOf(root, new_parent_info->getData());
        temp->setData(new_parent_info->getData());
        temp->setCount(new_parent_info->getCount());

        if (new_parent_info->getRight()) {
            // If the leftmost node has a child, which has to be a right child,
            // set its contents to the leftmost node and delete the right child
            BinaryTree<T>* to_delete = new_parent_info->getRight();
            *new_parent_info = *to_delete;

            to_delete->setLeft(nullptr);
            to_delete->setRight(nullptr);
            delete to_delete;
        } else {
            // The rightmost node has no children, so we can safely delete
            delete parent_of_new_parent_info->getRight();
            parent_of_new_parent_info->setRight(nullptr);
        }
    } else {
        BinaryTree<T>* parent = binaryTreeGetParentValueOf(root, temp->getData());
        if (temp->getData() < parent->getData()) {
            delete parent->getLeft();
            parent->setLeft(nullptr);
        } else {
            delete parent->getRight();
            parent->setRight(nullptr);
        }
    }
}

#endif