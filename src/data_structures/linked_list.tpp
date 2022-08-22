#ifndef LINKEDLIST_TPP
#define LINKEDLIST_TPP

#include <iostream>
#include <string>
#include <set>

template <typename T>
class ListNode {
public:
    // Constructors
    ListNode(): data(T()), next(nullptr) {}
    ListNode(T in_data): data(in_data), next(nullptr) {}
    ListNode(T in_data, ListNode* in_next): data(in_data), next(in_next) {}
    ListNode(ListNode<T>& original): data(original.getData()), next(original.getNext()) {}

    // Destructor
    ~ListNode() {
        if (next) {
            delete next;
        }
    }

    // Getters
    T getData() {return data;};
    ListNode* getNext() {return next;}

    // Setters
    void setData(T in_data) {data = in_data;}
    void setNext(ListNode* in_next) {next = in_next;}

    // Utility Functions
    bool operator == (const ListNode<T>& rhs) const {return data = rhs.getData();}
    bool operator != (const ListNode<T>& rhs) const {return data != rhs.getData();}
    
private:
    T data;
    ListNode* next;
};

template <typename T>
class LinkedList {
public:
    // Constructors
    LinkedList(): head() {}
    LinkedList(T data): head(new ListNode<T>(data)) {}
    LinkedList(LinkedList<T>& list): head(list.getHead()) {}

    // Destructor
    ~LinkedList() {
        if (head) {
            delete head;
        }
    }

    // Getters
    ListNode<T>* getHead() {return head;}

    // Setters
    void setHead(ListNode<T>* in_head) {head = in_head;}

    // Utility functions

    /**
     * @brief Adds a value to the list. Only have the data as an argument, becuase it
     * doesn't make sense to add a ListNode to a list when we have to set the new head's
     * link to point to the rest of the list. 
     * 
     * @param data The data to enter.
     */
    void insertAtHead(T data) {
        ListNode<T>* node = new ListNode<T>(data, head);
        head = node;
    }

    /**
     * @brief Inserts a node at the tail of the list. Takes O(N) time, unlike O(1) time for head insertion.
     * 
     * @tparam T The list's data type.
     * @param data The data to insert into the list.
     */
    void insertAtTail(T data) {
        ListNode<T>* temp = head;
        while (temp->getNext()) {
            temp = temp->getNext();
        }
        temp->setNext(new ListNode<T>(data));
    }

    /**
     * @brief Gets the length of the list, i.e. the number of ListNodes present.
     * 
     * @return int The length of the list.
     */
    int length() {
        int length = 0;
        ListNode<T>* temp = head;
        while (temp) {
            temp = temp->getNext();
            length++;
        }
        return length;
    }

    bool operator == (LinkedList<T>& second) {return internalCompare(head, second.getHead());}
    bool operator != (LinkedList<T>& second) {return !internalCompare(head, second.getHead());}

private:
    ListNode<T>* head;

    /**
     * @brief Recursively compares the given ListNodes. Used to determine if two linked lists are equal.
     * NOTE: because we use the inequality operator, floats/doubles may not work well with this method.
     * 
     * @param lhs A node from the first list.
     * @param rhs A node from the second list.
     * @return true if the nodes and all subsequent values are equal, otherwise false.
     */
    bool internalCompare(ListNode<T>* lhs, ListNode<T>* rhs) {
        if (!lhs and !rhs) {
            return true;
        } else if (lhs and !rhs or !lhs and rhs) {
            return false;
        } else if (lhs->getData() != rhs->getData()) {
            return false;
        } else {
            return internalCompare(lhs->getNext(), rhs->getNext());
        }
    }
};

/**
 * @brief Reverses the list.
 * 
 * @tparam T The data type that the list contains.
 * @param list The list to reverse.
 */
template <typename T>
void reverseList(LinkedList<T>* list) {
    if (list->length() < 2) {
        return;
    }
    ListNode<T> *prev = nullptr, *temp = list->getHead(), *next = temp->getNext();
    while (temp) {
        next = temp->getNext();
        temp->setNext(prev);
        prev = temp;
        temp = next;
    }
    list->setHead(prev);
}

/**
 * @brief Removes the given node. Assumes that previous_node is not null,
 * so we probably shouldn't use on the start of the list.
 * 
 * @tparam T The list's data type.
 * @param previous_node The previous node in the list.
 * @param to_delete The node to delete.
 */
template <typename T>
void removeNode(ListNode<T>* previous_node, ListNode<T>* to_delete) {
    previous_node->setNext(to_delete->getNext());
    to_delete->setNext(nullptr);
    delete to_delete;
}

/**
 * @brief Removes duplicate nodes from the list.
 * 
 * @tparam T The list's data type.
 * @param list The list to remove duplicates from.
 */
template <typename T>
void removeDuplicates(LinkedList<T>* list) {
    if (list->length() < 2) {
        return;
    }
    ListNode<T>* temp = list->getHead();
    std::set<T> unique_elements {temp->getData()};
    while (temp->getNext()) {
        if (unique_elements.count(temp->getNext()->getData())) {
            removeNode(temp, temp->getNext());
        } else {
            unique_elements.insert(temp->getNext()->getData());
            temp = temp->getNext();
        }
    }
}

#endif