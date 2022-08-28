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
    ~LinkedList() {if (next) delete next;}

    // Getters
    T getData() {return data;}
    LinkedList* getNext() {return next;}

    // Setters
    void setData(T in_data) {data = in_data;}
    void setNext(LinkedList<T>* in_next) {next = in_next;}

    // Utility Functions
    std::string toString() {
        std::string result = std::to_string(data);
        if (next) {result += (", " + next->toString());}
        return result;
    }

    friend std::ostream& operator << (std::ostream& out, LinkedList& list) {
        out << list.toString();
        return out;
    }
    
private:
    T data;
    LinkedList<T>* next;
};

template <typename T>
void linkedListInsertAtHead(LinkedList<T>*& head, T in_data) {
    LinkedList<T>* new_head = new LinkedList<T>(in_data, head);
    head = new_head;
}

template <typename T>
void linkedListInsertAtTail(LinkedList<T>*& head, T in_data) {
    LinkedList<T>* new_tail = new LinkedList<T>(in_data);
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

#endif