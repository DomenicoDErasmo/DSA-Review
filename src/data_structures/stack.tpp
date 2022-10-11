#ifndef STACK_TPP
#define STACK_TPP

#include "linked_list.tpp"

template <typename T>
struct Stack {
    Stack(): head(nullptr) {}
    Stack(T data): head(new LinkedList<T>(data)) {}
    ~Stack() {delete head;}

    // Data Members
    LinkedList<T>* head;
};

template <typename T>
T stackTop(Stack<T>& stack) {return stack.head->data;}

template <typename T>
void stackPop(Stack<T>& stack) {linkedListDeleteNodeAtIndex(stack.head, 0);}

template <typename T>
void stackPush(Stack<T>& stack, T data) {linkedListInsertAtHead(stack.head, data);}

#endif