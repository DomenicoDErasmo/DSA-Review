#ifndef STACK_TPP
#define STACK_TPP

#include "linked_list.cpp"

template <typename T>
struct Stack {
    Stack(): head(nullptr) {}
    Stack(T data): head(new LinkedList<T>(data)) {}
    ~Stack() {delete head;}

    // Data Members
    LinkedList<T>* head;
};

template <typename T>
/**
 * @brief Returns the top of the stack. Assumes the stack isn't empty
 * 
 * @param stack A reference to a stack
 * @return T The top of the stack
 */
T stackTop(Stack<T>& stack) {return stack.head->data;}

template <typename T>
void stackPop(Stack<T>& stack) {linkedListDeleteNodeAtIndex(stack.head, 0);}

template <typename T>
void stackPush(Stack<T>& stack, T data) {linkedListInsertAtHead(stack.head, data);}

template <typename T>
bool stackIsEmpty(Stack<T>& stack) {
    return !stack.head;
}

#endif