#ifndef STACK_CPP
#define STACK_CPP

#include "double_linked_list.cpp"

/**
 * @brief Stack implementation
 * 
 * @tparam T The type of the stack's data
 */
template <typename T>
struct Stack {
    // Fields
    DoubleLinkedList<T>* top;

    // Constructors
    Stack(): top(nullptr) {}
};

#endif