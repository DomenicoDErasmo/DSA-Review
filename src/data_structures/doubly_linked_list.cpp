#ifndef DOUBLY_LINKED_LIST_TPP
#define DOUBLY_LINKED_LIST_TPP

#include <iostream>
#include <string>

template <typename T>
struct DoublyLinkedList {
    // Constructors
    DoublyLinkedList(): data(T()), prev(nullptr), next(nullptr) {}
    DoublyLinkedList(T in_data): data(in_data), prev(nullptr), next(nullptr) {}
    DoublyLinkedList(T in_data, DoublyLinkedList<T>* in_prev, DoublyLinkedList<T>* in_next): 
        data(in_data), prev(in_prev), next(in_next) {}

    // Destructor
    // Note: Up to the user to delete from the beginning of the list
    ~DoublyLinkedList() {delete next;}

    // Utility Functions
    std::string to_string() const {
        std::string result = std::to_string(data);
        if (next) {result += (" <-> " + next->to_string());}
        return result;
    }

    // Operators
    friend std::ostream& operator << (std::ostream& out, const DoublyLinkedList& list) {
        out << list.to_string();
        return out;
    }

    // Only checks one direction, because we could get caught up infinitely otherwise?
    const bool operator == (const DoublyLinkedList<T>& rhs) {
        if (!this->next and !rhs.next) {return this->data == rhs.data;}
        if (!this->next and rhs.next or this->next and !rhs.next) {return false;}
        if (this->data != rhs.data) {return false;}
        return *(this->next) == *(rhs.next);
    }

    const bool operator != (const DoublyLinkedList<T>& rhs) {
        return !(*this == rhs);
    }

    // Data Members
    T data;
    DoublyLinkedList<T>* prev;
    DoublyLinkedList<T>* next;
};


template <typename T>
void doublyLinkedListInsertPrev(DoublyLinkedList<T>*& head, T in_data) {
    if (!head) {
        head = new DoublyLinkedList<T>(in_data);
        return;
    }
    DoublyLinkedList<T>* new_node = new DoublyLinkedList<T>(in_data, head->prev, head);
    if (new_node->prev) {new_node->prev->next = new_node;}
    head->prev = new_node;
}

template <typename T>
void doublyLinkedListInsertNext(DoublyLinkedList<T>*& head, T in_data) {
    if (!head) {
        head = new DoublyLinkedList<T>(in_data);
        return;
    }
    DoublyLinkedList<T>* new_node = new DoublyLinkedList<T>(in_data, head, head->next);
    if (new_node->next) {new_node->next->prev = new_node;}
    head->next = new_node;
}

template <typename T>
void doublyLinkedListDeleteNode(DoublyLinkedList<T>*& head, DoublyLinkedList<T>* to_delete) {
    if (!head) {return;}
    
    if (to_delete == head) {
        head = head->next;
        to_delete->next = nullptr;
        delete to_delete;
        return;
    }
    DoublyLinkedList<T>* temp = head;
    while (temp != to_delete && temp) {
        temp = temp->next;
    }
    if (temp) {
        DoublyLinkedList<T>* temp2 = temp->prev;
        temp2->next = temp->next;
        temp->next = nullptr;
        delete temp;
    }
}


#endif