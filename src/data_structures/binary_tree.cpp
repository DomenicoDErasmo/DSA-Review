#ifndef BINARY_TREE_CPP
#define BINARY_TREE_CPP

template <typename T>
struct BinaryTree {
    // Fields
    T data;
    BinaryTree<T>* left;
    BinaryTree<T>* right;
};

#endif
