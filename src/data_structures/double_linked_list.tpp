#ifndef DOUBLE_LINKED_LIST_TPP
#define DOUBLE_LINKED_LIST_TPP

template <typename T>
struct DoubleLinkedList {
    DoubleLinkedList(): data(T()), next(nullptr), prev(nullptr) {}
    DoubleLinkedList(T data): data(data), next(nullptr), prev(nullptr) {}
    DoubleLinkedList(T data, DoubleLinkedList<T>* next, DoubleLinkedList<T>* prev): data(data), next(next), prev(prev) {}
    ~DoubleLinkedList(): {
        delete next;
        delete prev;
    }

    T data;
    DoubleLinkedList<T>* next;
    DoubleLinkedList<T>* prev;
};

#endif