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
    Stack(T data): top(new DoubleLinkedList<T>(data)) {}
    Stack(const Stack<T>& other): top(new DoubleLinkedList<T>(other)) {}

    // Destructor
    ~Stack() {delete top;}

    // Operators
    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom.
     * 
     * @param rhs The stack to copy
     * @return Stack<T>& A copied stack
     */
    Stack<T>& operator = (Stack<T> rhs) {
        swap (*this, other);
        return *this;
    }

    // Utility Functions

    /**
     * @brief Swaps the provided stacks
     * 
     * @param first The first stack to swap
     * @param second The second stack to swap
     */
    friend void swap (Stack<T>& first, Stack<T>& second) {
        // enables ADL
        using std::swap;
        swap(first.top, second.top);
    }
};

#endif