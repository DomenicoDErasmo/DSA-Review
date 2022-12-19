#ifndef DOUBLE_LINKED_LIST_CPP
#define DOUBLE_LINKED_LIST_CPP

/**
 * @brief Generic double linked list class
 * 
 * @tparam T Any type. Assumes that the type implements the equality operator.
 */
template <typename T>
struct DoubleLinkedList {
    // Fields
    T data;
    DoubleLinkedList<T>* prev;
    DoubleLinkedList<T>* next;

    // Constructors

    // Default - Assumes that the type has a default constructor
    DoubleLinkedList(): data(T()), prev(nullptr), next(nullptr) {}

    DoubleLinkedList(T data): data(data), prev(nullptr), next(nullptr) {}
    DoubleLinkedList(
        T data, 
        DoubleLinkedList<T>* prev, 
        DoubleLinkedList<T>* next): data(data), prev(prev), next(next) {}

    /**
     * @brief Copy constructor for the double linked list. We only go in
     * one direction because we will infinitely loop otherwise!
     * 
     * @param other The double linked list to copy
     */
    DoubleLinkedList(const DoubleLinkedList<T>& other) {
        copyConstructorHelper(this, other, nullptr);
    }

    // Destructor
    ~DoubleLinkedList() {delete next;}

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom.
     * 
     * @param rhs The double linked list to copy
     * @return DoubleLinkedList<T>& A copied double linked list
     */
    DoubleLinkedList<T>& operator = (DoubleLinkedList<T> rhs) {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Checks equality of two double linked lists
     * 
     * @param lhs The first double linked list to check
     * @param rhs The second double linked list to check
     * @return true if the lists are equal, otherwise false
     */
    friend bool operator == (
            DoubleLinkedList<T>& lhs, 
            DoubleLinkedList<T>& rhs) {
        DoubleLinkedList<T> *lhs_temp = &lhs, *rhs_temp = &rhs;

        // We can only check one direction, otherwise we will infinitely loop
        // One work around is to get to the start of each list and check next
        while (lhs_temp->prev) {lhs_temp = lhs_temp->prev;}
        while (rhs_temp->prev) {rhs_temp = rhs_temp->prev;}

        while (lhs_temp && rhs_temp) {
            if (lhs_temp->data != rhs_temp->data) {return false;}
            lhs_temp = lhs_temp->next;
            rhs_temp = rhs_temp->next;
        }
        return (!lhs_temp && !rhs_temp);
    }

    /**
     * @brief Checks inequality of two double linked lists
     * 
     * @param lhs The first double linked list to check
     * @param rhs The second double linked list to check
     * @return true if the lists are inequal, otherwise false
     */
    friend bool operator != (
            DoubleLinkedList<T>& lhs, 
            DoubleLinkedList<T>& rhs) {
        return !(lhs == rhs);
    }

    // Utility Functions

    /**
     * @brief Helper function for the copy constructor
     * 
     * @param self The double linked list being constructed
     * @param other The double linked list being copied
     * @param prev The node to set self->prev to
     */
    void copyConstructorHelper(
            DoubleLinkedList<T>* self, 
            const DoubleLinkedList<T>& other, 
            DoubleLinkedList<T>* prev) {
        self->data = other.data;
        self->prev = prev;

        if (other.next) {
            self->next = new DoubleLinkedList<T>(other.next->data);
            copyConstructorHelper(self->next, *other.next, self);
        } else {
            self->next = nullptr;
        }
    }
    
    /**
     * @brief Swaps the provided double linked lists
     * 
     * @param first The first double linked list to swap
     * @param second The second double linked list to swap
     */
    friend void swap (DoubleLinkedList<T>& first, DoubleLinkedList<T>& second) {
        // enables ADL - we could use namespaces to change functionality
        using std::swap;

        swap(first.data, second.data);
        swap(first.prev, second.prev);
        swap(first.next, second.next);
    }
};

/**
 * @brief Inserts a new node before the current node
 * We pass a double pointer because otherwise we don't get the exact head
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to the node to insert before
 * @param data The data to insert
 */
template <typename T>
void doubleLinkedListInsertPrev(DoubleLinkedList<T>** node, T data) {
    if (!*node) {
        *node = new DoubleLinkedList<T>(data);
        return;
    }
    DoubleLinkedList<T>* prev = (*node)->prev;
    DoubleLinkedList<T>* new_node = new DoubleLinkedList<T>(data, prev, *node);
    (*node)->prev = new_node;
    if (prev) {prev->next = new_node;}
}

/**
 * @brief Inserts a new node after the current node
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to the node to insert after
 * @param data The data to insert
 */
template <typename T>
void doubleLinkedListInsertNext(DoubleLinkedList<T>** node, T data) {
    if (!*node) {
        *node = new DoubleLinkedList<T>(data);
        return;
    }
    DoubleLinkedList<T>* next = (*node)->next;
    DoubleLinkedList<T>* new_node = new DoubleLinkedList<T>(data, *node, next);
    (*node)->next = new_node;
    if (next) {next->prev = new_node;}
}

/**
 * @brief Gets the head of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to find the head of
 * @return DoubleLinkedList<T>* The head of the double linked list
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetHead(DoubleLinkedList<T>** node) {
    if (!*node) {return nullptr;}
    DoubleLinkedList<T>* temp = *node;
    while (temp->prev) {temp = temp->prev;}
    return temp;
}

/**
 * @brief Gets the tail of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to find the tail of
 * @return DoubleLinkedList<T>* The tail of the double linked list
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetTail(DoubleLinkedList<T>** node) {
    if (!*node) {return nullptr;}
    DoubleLinkedList<T>* temp = *node;
    while (temp->next) {temp = temp->next;}
    return temp;
}

/**
 * @brief Gets a node from the forward position of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to find the forward nth position of
 * @param n The position to find
 * @return DoubleLinkedList<T>* The nth forward node in the list
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetFromForwardPosition(
        DoubleLinkedList<T>** node, 
        int n) {
    if (n < 0) {return nullptr;}
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(node);
    int current = 0;
    while (head && current < n) {
        head = head->next;
        current++;
    }
    if (current < n) {return nullptr;}
    else {return head;}
}

/**
 * @brief Gets a node from the backward position of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to find the backward nth position of
 * @param n The position to find
 * @return DoubleLinkedList<T>* The nth backward node in the list
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetFromBackwardPosition(
        DoubleLinkedList<T>** node, 
        int n) {
    if (n < 0) {return nullptr;}
    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(node);
    int current = 0;
    while (tail && current < n) {
        tail = tail->prev;
        current++;
    }
    if (current < n) {return nullptr;}
    else {return tail;}
}

/**
 * @brief Deletes the node at the nth forward position
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list
 * @param n The positional node to delete
 */
template <typename T>
void doubleLinkedListDeleteFromForwardPosition(
        DoubleLinkedList<T>** node,
        int n) {
    if (n < 0) {return;}

    DoubleLinkedList<T>* head = doubleLinkedListGetHead(node);
    if (!head) {return;}

    if (n == 0) {
        DoubleLinkedList<T>* next = head->next;
        if (*node == head) {*node = next;}
        if (next) {next->prev = nullptr;}

        head->next = nullptr;
        delete head;  
        return;      
    }

    DoubleLinkedList<T>* to_delete = doubleLinkedListGetFromForwardPosition(
        &head, 
        n);
    if (!to_delete) {return;}

    DoubleLinkedList<T>* prev = to_delete->prev, **next = &prev->next;
    if (*node == to_delete) {*node = prev;}

    *next = to_delete->next;
    if (*next) {(*next)->prev = prev;}

    to_delete->prev = nullptr;
    to_delete->next = nullptr;
    delete to_delete;
}

/**
 * @brief Deletes the node at the nth backward position
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list
 * @param n The positional node to delete
 */
template <typename T>
void doubleLinkedListDeleteFromBackwardPosition(
        DoubleLinkedList<T>** node,
        int n) {
    if (n < 0) {return;}

    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(node);
    if (!tail) {return;}

    if (n == 0) {
        DoubleLinkedList<T>* prev = tail->prev;
        if (*node == tail) {*node = prev;}
        if (prev) {prev->next = nullptr;}

        tail->prev = nullptr;
        delete tail;  
        return;      
    }

    DoubleLinkedList<T>* to_delete = doubleLinkedListGetFromBackwardPosition(
        &tail, 
        n);
    if (!to_delete) {return;}

    DoubleLinkedList<T>* next = to_delete->next, **prev = &next->prev;
    if (*node == to_delete) {*node = next;}

    *prev = to_delete->prev;
    if (*prev) {(*prev)->next = next;}

    to_delete->prev = nullptr;
    to_delete->next = nullptr;
    delete to_delete;
}

/**
 * @brief Inserts at the head of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to insert at the head of
 * @param data The data to insert at the head of the list
 */
template <typename T>
void doubleLinkedListInsertAtHead(DoubleLinkedList<T>** node, T data) {
    if (!*node) {
        *node = new DoubleLinkedList<T>(data);
        return;
    }
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(node);
    doubleLinkedListInsertPrev(&head, data);
}

/**
 * @brief Inserts at the tail of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list to insert at the tail of
 * @param data The data to insert at the tail of the list
 */
template <typename T>
void doubleLinkedListInsertAtTail(DoubleLinkedList<T>** node, T data) {
    if (!*node) {
        *node = new DoubleLinkedList<T>(data);
        return;
    }
    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(node);
    doubleLinkedListInsertNext(&tail, data);
}

/**
 * @brief Gets the length of the double linked list
 * 
 * @tparam T The type of the double linked list's data
 * @param node A node of the list to get the head of
 * @return int The length of the double linked list
 */
template <typename T>
int doubleLinkedListGetLength(DoubleLinkedList<T>* node) {
    int result = 0;
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(&node);
    while (head) {
        head = head->next;
        result++;
    }
    return result;
}

/**
 * @brief Gets the position of the Nth occurrence of data starting from the head
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to the node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 * @return int The position of the nth occurrence of data in the list or -1
 */
template <typename T>
int doubleLinkedListGetForwardPositionOfNthOccurrence(
        DoubleLinkedList<T>* node, 
        T data,
        int n) {
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(&node);
    int num_found = 0, current = 0;
    while (head && num_found < n) {
        if (head->data == data) {
            num_found++;
            if (num_found == n) {return current;} 
        }
        head = head->next;
        current++;
    }
    return -1;
}

/**
 * @brief Gets the position of the Nth occurrence of data starting from the tail
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to the node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 * @return int The position of the nth occurrence of data in the list or -1
 */
template <typename T>
int doubleLinkedListGetBackwardPositionOfNthOccurrence(
        DoubleLinkedList<T>* node, 
        T data,
        int n) {
    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(&node);
    int num_found = 0, current = 0;
    while (tail && num_found < n) {
        if (tail->data == data) {
            num_found++;
            if (num_found == n) {return current;} 
        }
        tail = tail->prev;
        current++;
    }
    return -1;
}

/**
 * @brief Gets the nth occurrence of the data in the list starting at the front
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 * @return DoubleLinkedList<T>* The nth occurrence in the list or nullptr
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetForwardNthOccurrence(
        DoubleLinkedList<T>** node, 
        T data, 
        int n) {
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(node);
    int position = doubleLinkedListGetForwardPositionOfNthOccurrence(
        head, 
        data, 
        n);
    return doubleLinkedListGetFromForwardPosition(&head, position);
}


/**
 * @brief Gets the nth occurrence of the data in the list starting at the back
 * 
 * @tparam T The type of the double linked list's data
 * @param node A pointer to a node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 * @return DoubleLinkedList<T>* The nth occurrence in the list or nullptr
 */
template <typename T>
DoubleLinkedList<T>* doubleLinkedListGetBackwardNthOccurrence(
        DoubleLinkedList<T>** node, 
        T data, 
        int n) {
    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(node);
    int position = doubleLinkedListGetBackwardPositionOfNthOccurrence(
        tail, 
        data, 
        n);
    return doubleLinkedListGetFromBackwardPosition(&tail, position);
}

/**
 * @brief Deletes the nth occurrence of the data searching from the head
 * 
 * @tparam T The type of the doulbe linked list's data
 * @param node A pointer to a node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 */
template <typename T>
void doubleLinkedListDeleteForwardNthOccurrence(
        DoubleLinkedList<T>** node,
        T data,
        int n) {
    DoubleLinkedList<T>* head = doubleLinkedListGetHead(node);
    int position = doubleLinkedListGetForwardPositionOfNthOccurrence(
        head,
        data,
        n);
    doubleLinkedListDeleteFromForwardPosition(&head, position);
}

/**
 * @brief Deletes the nth occurrence of the data searching from the tail
 * 
 * @tparam T The type of the doulbe linked list's data
 * @param node A pointer to a node in the list
 * @param data The data to search for in the list
 * @param n The number of occurrences to stop at
 */
template <typename T>
void doubleLinkedListDeleteBackwardNthOccurrence(
        DoubleLinkedList<T>** node,
        T data,
        int n) {
    DoubleLinkedList<T>* tail = doubleLinkedListGetTail(node);
    int position = doubleLinkedListGetBackwardPositionOfNthOccurrence(
        tail,
        data,
        n);
    doubleLinkedListDeleteFromBackwardPosition(&tail, position);
}

#endif