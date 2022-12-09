#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP
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

template <typename T>
int binaryTreeGetHeight(BinaryTree<T>* const& tree) {
    return binaryTreeGetHeightHelper(tree, 0);
}

template <typename T>
int binaryTreeGetHeightHelper(BinaryTree<T>* const& tree, int height) {
    if (!tree) {return height;}
    int left = binaryTreeGetHeightHelper(tree->left, height + 1);
    int right = binaryTreeGetHeightHelper(tree->right, height + 1);
    return left > right ? left : right;
}

template <typename T>
int binaryTreeGetSize(BinaryTree<T>* const& tree) {
    if (!tree) {return 0;}
    return 1 + binaryTreeGetHeight(tree->left) 
             + binaryTreeGetHeight(tree->right);
}

template <typename T>
void binaryTreeInsertNode(BinaryTree<T>** tree, T data) {
    // TODO: implement with balancing
}

#endif
