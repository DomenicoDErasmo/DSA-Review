#ifndef LINKED_LIST_TPP
#define LINKED_LIST_TPP

#include <string>
template <typename T>
class LinkedList {
public:
    // Constructors
    LinkedList(): data(T()), next(nullptr) {}
    LinkedList(T in_data): data(in_data), next(nullptr) {}
    LinkedList(T in_data, LinkedList* in_next): data(in_data), next(in_next) {}
    LinkedList(const LinkedList& other): data(other.data), next(other.next) {}

    // Destructors
    ~LinkedList() {delete next;}

    // Getters
    T getData() const {return data;}
    LinkedList* getNext() const {return next;}

    // Setters
    void setData(T in_data) {data = in_data;}
    void setNext(LinkedList<T>* in_next) {next = in_next;}

    // Utility Functions
    std::string toString() const {
        std::string result = std::to_string(data);
        if (next) {result += (", " + next->toString());}
        return result;
    }

    friend std::ostream& operator << (std::ostream& out, const LinkedList& list) {
        out << list.toString();
        return out;
    }

    const bool operator == (const LinkedList& rhs) {
        if (!this->getNext() and !rhs.getNext()) {return this->getData() == rhs.getData();}
        if (!this->getNext() and rhs.getNext() or this->getNext() and !rhs.getNext()) {return false;}
        if (this->getData() != rhs.getData()) {return false;}
        return *(this->getNext()) == *(rhs.getNext());
    }

    const bool operator != (const LinkedList& rhs) {
        return !(*this == rhs);
    }
    
private:
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
void linkedListInsertAtTail(LinkedList<T>*& head, T in_data) {
    if (!head) {
        head = new LinkedList<T>(in_data);
        return;
    }
    LinkedList<T>* new_tail = new LinkedList<T>(in_data);
    LinkedList<T>* temp = head;
    while (temp->getNext()) {
        temp = temp->getNext();
    }
    temp->setNext(new_tail);
}

template <typename T>
void linkedListInsertNodeAtTail(LinkedList<T>*& head, LinkedList<T>* new_tail) {
    LinkedList<T>* temp = head;
    while (temp->getNext()) {
        temp = temp->getNext();
    }
    temp->setNext(new_tail);
}

template <typename T>
int linkedListGetSize(LinkedList<T>*& head) {
    int result = 0;
    LinkedList<T>* temp = head;
    while (temp) {
        temp = temp->getNext();
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
        temp = temp->getNext();
    }
    return temp->getData();
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
        temp = temp->getNext();
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
        if (temp->getData() == to_find) {
            times_found++;
        }
        temp = temp->getNext();
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
void linkedListDeleteNodeAtIndex(LinkedList<T>*& head, int pos) {
    LinkedList<T>* temp = head;
    for (size_t i = 0; i < pos - 1; i++) {
        if (!temp) {return;}
        temp = temp->getNext();
    }
    LinkedList<T>* to_delete = temp->getNext();
    temp->setNext(to_delete->getNext());
    to_delete->setNext(nullptr);
    delete to_delete;
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
        if (temp->getData() == to_delete) {
            times_found++;
        }
        temp = temp->getNext();
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
        curr->setNext(prev);
        temp = temp->getNext();
        prev = curr;
        curr = temp;
    }
}

#endif