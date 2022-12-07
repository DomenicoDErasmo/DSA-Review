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

#endif
