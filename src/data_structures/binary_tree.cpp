#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP

#include "linked_list.cpp"
template <typename T>
struct BinaryTree {
    // Fields
    T data;
    BinaryTree<T>* left;
    BinaryTree<T>* right;

    // Constructors
    BinaryTree(): data(T()), left(nullptr), right(nullptr) {}
    BinaryTree(const T& data): data(data), left(nullptr), right(nullptr) {}
    BinaryTree(
            const T& data, 
            BinaryTree<T>* const& left, 
            BinaryTree<T>* const& right): 
        data(data), left(left), right(right) {}
    BinaryTree(const BinaryTree<T>& other) {
        data = other.data;
        left = other.left ? new BinaryTree<T>(*other.left) : nullptr;
        right = other.right ? new BinaryTree<T>(*other.right) : nullptr;
    }

    // Destructors
    ~BinaryTree() {
        delete left;
        delete right;
    }

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom
     * discussed in the Linked List file
     * 
     * @param rhs The binary tree to copy
     * @return BinaryTree<T>& A copied binary tree
     */
    BinaryTree<T>& operator = (BinaryTree<T> rhs) {
        swap(*this, other);
        return *this;
    }

    // Utility Functions

    /**
     * @brief Swaps the provided binary trees
     * 
     * @param first The first binary tree to swap
     * @param second The second binary tree to swap
     */
    friend void swap(BinaryTree<T>& first, BinaryTree<T>& second) {
        // enables ADL - we could use namespaces to change functionality
        using std::swap;

        swap(first.data, second.data);
        swap(first.left, second.left);
        swap(first.right, second.right);
    }
};

/**
 * @brief Helper function to get height of tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @param level The current level of the tree
 * @return int The total height of the tree
 */
template <typename T>
int binaryTreeGetHeightHelper(BinaryTree<T>* const& tree, int level) {
    if (!tree) {return level;}
    int left = binaryTreeGetHeightHelper(tree->left, level + 1);
    int right = binaryTreeGetHeightHelper(tree->right, level + 1);
    return left > right ? left : right;
}

/**
 * @brief Gets the height of the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @return int The total height of the tree
 */
template <typename T>
int binaryTreeGetHeight(BinaryTree<T>* const& tree) {
    return binaryTreeGetHeightHelper(tree, 0);
}

/**
 * @brief Gets the total number of nodes in the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree A binary tree
 * @return int The total number of nodes in the tree
 */
template <typename T>
int binaryTreeGetNumNodes(BinaryTree<T>* const& tree) {
    if (!tree) {return 0;}
    return 1 + binaryTreeGetNumNodes(tree->left) 
             + binaryTreeGetNumNodes(tree->right);
}

/**
 * @brief Helper function to insert a node into the tree
 * 
 * @tparam T The type of the tree's data
 * @param node The node to insert a value for
 * @param data The data to insert into the tree
 */
template <typename T>
void binaryTreeInsertNodeHelper(BinaryTree<T>** node, T data) {
    if (*node) {binaryTreeInsertNode(node, data);} 
    else {*node = new BinaryTree<T>(data);}
}

/**
 * @brief Inserts a node into the tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @param data The data to insert into the tree
 */
template <typename T>
void binaryTreeInsertNode(BinaryTree<T>** tree, T data) {
    if (!*tree) {*tree = new BinaryTree<T>(data);}
    T node_data = (*tree)->data;
    if (node_data == data) {return;}
    BinaryTree<T>** next = data < node_data ? &(*tree)->left : &(*tree)->right;
    binaryTreeInsertNodeHelper(next, data);
}

/**
 * @brief Gets preorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The preorder of the tree
 */
template <typename T>
void binaryTreeGetPreorder(
        BinaryTree<T>* const& tree, LinkedList<T>** preorder) {
    if (!tree) {return;}
    linkedListInsertAtTail(preorder, tree->data);
    binaryTreeGetPreorder(tree->left, preorder);
    binaryTreeGetPreorder(tree->right, preorder);
}

/**
 * @brief Gets inorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The inorder of the tree
 */
template <typename T>
void binaryTreeGetInorder(BinaryTree<T>* const& tree, LinkedList<T>** inorder) {
    if (!tree) {return;}
    binaryTreeGetInorder(tree->left, inorder);
    linkedListInsertAtTail(inorder, tree->data);
    binaryTreeGetInorder(tree->right, inorder);
}

/**
 * @brief Gets postorder for the binary tree
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to insert data into
 * @return LinkedList<T>* The postorder of the tree
 */
template <typename T>
void binaryTreeGetPostorder(
        BinaryTree<T>* const& tree, LinkedList<T>** postorder) {
    if (!tree) {return;}
    binaryTreeGetPostorder(tree->left, postorder);
    binaryTreeGetPostorder(tree->right, postorder);
    linkedListInsertAtTail(postorder, tree->data);
}

/**
 * @brief Gets the node in the binary tree with matching data
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to search
 * @param data The data to search for
 * @return BinaryTree<T>* The node if found, otherwise nullptr
 */
template <typename T>
BinaryTree<T>* binaryTreeGetNode(BinaryTree<T>* const& tree, T data) {
    if (!tree || tree->data == data) {return tree;}
    else if (data < tree->data) {return binaryTreeGetNode(tree->left, data);}
    else {return binaryTreeGetNode(tree->right, data);}
}

/**
 * @brief Gets the prede/suc cessor to the desired order.
 * 
 * @tparam T The type of the tree's data
 * @param tree The binary tree to search
 * @param data The data to search for
 * @param order_function The tree traversal function (such as preorder)
 * @param cessor_function A function to get either the predecessor or successor
 * @return BinaryTree<T>* The node if found, otherwise nullptr
 */
template <typename T>
// TODO: unit tests
BinaryTree<T>* binaryTreeGetOrderCessor(
        BinaryTree<T>* const& tree, 
        T data, 
        void (*order_function)(BinaryTree<T>* const&, LinkedList<T>**),
        void (*cessor_function)(BinaryTree<T>* const&, T data, int n)) {
    if (!order_function) {return nullptr;}
    LinkedList<T>* order;
    order_function(tree, &order);
    LinkedList<T>* item = linkedListFindNthOccurrence(order, data, 1);
    LinkedList<T>* prev = cessor_function(order, item, 1);
    return binaryTreeGetNode(tree, prev->data;)
}

template <typename T>
void binaryTreeDeleteNode(BinaryTree<T>** tree, T data) {

}

#endif
