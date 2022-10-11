#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include <iostream>
#include <string>
template <typename T>
struct LinkedList {
public:
    // Constructors
    LinkedList(): data(T()), next(nullptr) {}
    LinkedList(T in_data): data(in_data), next(nullptr) {}
    LinkedList(T in_data, LinkedList<T>* in_next): data(in_data), next(in_next) {}
    LinkedList(const LinkedList<T>& other): data(other.data), next(other.next) {}

    // Destructor
    ~LinkedList() {delete next;}

    // Utility Functions
    std::string toString() const {
        std::string result = std::to_string(data);
        if (next) {result += (", " + next->toString());}
        return result;
    }

    // Operators
    friend std::ostream& operator << (std::ostream& out, const LinkedList<T>& list) {
        out << list.toString();
        return out;
    }

    const bool operator == (const LinkedList<T>& rhs) {
        if (!this->next and !rhs.next) {return this->data == rhs.data;}
        if (!this->next and rhs.next or this->next and !rhs.next) {return false;}
        if (this->data != rhs.data) {return false;}
        return *(this->next) == *(rhs.next);
    }

    const bool operator != (const LinkedList<T>& rhs) {
        return !(*this == rhs);
    }
    
    // Data Members
    T data;
    LinkedList<T>* next;
};

template <typename T>
void linkedListInsertAtHead(LinkedList<T>*& head, T in_data) {
    if (!head) {
        head = new LinkedList<T>(in_data);
        return;
    }
    LinkedList<T>* new_head = new LinkedList<T>(in_data, head);
    head = new_head;
}

template <typename T>
void linkedListInsertNodeAtTail(LinkedList<T>*& head, LinkedList<T>* new_tail) {
    LinkedList<T>* temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_tail;
}

template <typename T>
void linkedListInsertAtTail(LinkedList<T>*& head, T in_data) {
    if (!head) {
        head = new LinkedList<T>(in_data);
        return;
    }
    LinkedList<T>* new_tail = new LinkedList<T>(in_data);
    linkedListInsertNodeAtTail(head, new_tail);
}

template <typename T>
int linkedListGetSize(LinkedList<T>*& head) {
    int result = 0;
    LinkedList<T>* temp = head;
    while (temp) {
        temp = temp->next;
        result++;
    }
    return result;
}

template <typename T>
/**
 * @brief Returns the data from the middle value of the list
 * 
 * @param head A reference to a linked list pointer. Assumed that head is not null 
 * @return T The data from the middle node of the list
 */
T linkedListGetMiddle(LinkedList<T>*& head) {
    int middle = linkedListGetSize(head) / 2;
    LinkedList<T>* temp = head;
    for (size_t i = 0; i < middle; i++) {
        temp = temp->next;
    }
    return temp->data;
}

template <typename T>
/**
 * @brief Gets the linked list node at the 0-index-specified position
 * 
 * @param head A pointer to a linked list
 * @param pos The index of the list whose node we want to return
 * @return LinkedList<T>* A pointer to the ith node in the list, or nullptr if not found
 */
LinkedList<T>* linkedListGetNodeAtIndex(LinkedList<T>* head, int pos) {
    LinkedList<T>* temp = head;
    for (size_t i = 0; i < pos; i++) {
        if (!temp) {return nullptr;}
        temp = temp->next;
    }
    return temp;
}

template <typename T>
/**
 * @brief Finds the nth occurrence of to_find
 * 
 * @param head A linked list pointer
 * @param to_find The data to find
 * @param n The occurrence of the data to find
 * @return int The 0-indexed-position of the nth occurrence of to_find in the linked list, or -1 if not found
 */
int linkedListFindNthOccurrence(LinkedList<T>* head, T to_find, int n) {
    if (n <= 0) {return -1;}
    int times_found = 0, current_position = -1;
    LinkedList<T>* temp = head;
    while (times_found < n and temp) {
        if (temp->data == to_find) {
            times_found++;
        }
        temp = temp->next;
        current_position++;
    }
    if (times_found == n) {
        return current_position;
    } else {
        return -1;
    }
}

template <typename T>
/**
 * @brief Deletes the linked list node at the 0-index-specified position
 * 
 * @param head A reference to a pointer to a linked list
 * @param pos The index of the list whose node we want to delete
 */
// TODO: fix delete node at index
void linkedListDeleteNodeAtIndex(LinkedList<T>*& head, int pos) {
    if (linkedListGetSize(head) < pos || !head) {return;}
    if (pos == 0) {
        LinkedList<T>* to_delete = head;
        head = head->next;
        to_delete->next = nullptr;
        delete to_delete;
        return;
    }
    LinkedList<T> *prev = nullptr, *temp = head;
    for (size_t i = 0; i < pos and temp; i++) {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    temp->next = nullptr;
    delete temp;
}

template <typename T>
/**
 * @brief Deletes the nth occurrence of to_delete
 * 
 * @param head A reference to a linked list pointer
 * @param to_delete The data to delete
 * @param n The occurrence of the data to delete
 */
void linkedListDeleteNthOccurrence(LinkedList<T>*& head, T to_delete, int n) {
    if (n <= 0) {return;}
    int times_found = 0, current_position = -1;
    LinkedList<T>* temp = head;
    while (times_found < n and temp) {
        if (temp->data == to_delete) {
            times_found++;
        }
        temp = temp->next;
        current_position++;
    }
    if (times_found == n) {
        linkedListDeleteNodeAtIndex(head, current_position);
    } else {
        return;
    }
}

template <typename T>
/**
 * @brief Reverses the linked list
 * 
 * @param head A reference to a pointer to a linked list
 */
void linkedListReverse(LinkedList<T>*& head) {
    LinkedList<T> *temp = head, *prev = nullptr, *curr = temp;
    while (temp) {
        curr->next = prev;
        temp = temp->next;
        prev = curr;
        curr = temp;
    }
}

#endif