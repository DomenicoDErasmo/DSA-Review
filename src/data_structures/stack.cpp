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
    Stack(const Stack<T>& other): top(new DoubleLinkedList<T>(*other.top)) {}

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

    /**
     * @brief Checks equality of two stacks
     * 
     * @param lhs The first stack to check
     * @param rhs The second stack to check
     * @return true if the stacks are equal, otherwise false
     */
    friend bool operator == (Stack<T>& lhs, Stack<T>& rhs) {
        return *lhs.top == *rhs.top;
    }

    /**
     * @brief Checks inequality of two stacks
     * 
     * @param lhs The first stack to check
     * @param rhs The second stack to check
     * @return true if the stacks are inequal, otherwise false
     */
    friend bool operator != (Stack<T>& lhs, Stack<T>& rhs) {
        return !(lhs == rhs);
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

/**
 * @brief Push a value onto the stack
 * 
 * @tparam T The type of the stack's data
 * @param stack The stack to push onto
 * @param data The data to add to the stack
 */
template <typename T>
void stackPush(Stack<T>& stack, T data) {
    doubleLinkedListInsertAtTail(&(stack.top), data);
    if (stack.top->next) {stack.top = stack.top->next;}
}

/**
 * @brief Yields the top element in the stack
 * 
 * @tparam T The type of the stack's data
 * @param stack The stack to take the top of
 * @return T& A reference to the data on the top of the stack
 */
template <typename T>
T& stackTop(Stack<T>& stack) {
    if (doubleLinkedListGetLength(stack.top) == 0) {
        throw std::logic_error("Can't take the top of an empty list!");
    } else {
        T& top = doubleLinkedListGetFromBackwardPosition(&stack.top, 0)->data;
        return top;
    }
}

#endif