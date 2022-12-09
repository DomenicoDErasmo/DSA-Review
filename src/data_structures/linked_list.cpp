#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

/**
 * @brief Generic linked list class
 * 
 * @tparam T Any type. Assumes that the type implements the equality operator
 */
template <typename T>
struct LinkedList {
    // Fields
    T data;
    LinkedList<T>* next;

    // Constructors

    // Default - Assumes that the type has a default constructor
    LinkedList(): data(T()), next(nullptr) {}

    LinkedList(const T& data): data(data), next(nullptr) {}
    LinkedList(const T& data,
               LinkedList<T>* const& next): data(data), next(next) {}
    LinkedList(const LinkedList<T>& other) {
        data = other.data;
        next = other.next ? new LinkedList<T>(*other.next) : nullptr;
    }

    // Destructors
    ~LinkedList() {delete next;}

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom from
     * https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
     * 
     * As discussed in the aforementioned link, 
     * we pass by value for optimization.
     * 
     * @param rhs The linked list to copy
     * @return LinkedList<T>& A copied linked list
     */
    LinkedList<T>& operator = (LinkedList<T> rhs) {
        swap(*this, other);
        return *this;
    }

    /**
     * @brief Checks equality of two linked lists
     * 
     * @param lhs The first linked list to chekc
     * @param rhs The second linked list to checl
     * @return true if the lists are equal, otherwise false
     */
    friend bool operator == (LinkedList<T>& lhs, LinkedList<T>& rhs) {
        LinkedList<T> *lhs_temp = &lhs, *rhs_temp = &rhs;
        while (lhs_temp && rhs_temp) {
            if (lhs_temp->data != rhs_temp->data) {return false;}
            lhs_temp = lhs_temp->next;
            rhs_temp = rhs_temp->next;
        }
        return (!lhs_temp && !rhs_temp);
    }

    /**
     * @brief Checks inequality of two linked lists
     * 
     * @param lhs The first linked list to chekc
     * @param rhs The second linked list to checl
     * @return true if the lists are inequal, otherwise false 
     */
    friend bool operator != (LinkedList<T>& lhs, LinkedList<T>& rhs)  {
        return !(lhs == rhs);
    }

    // Utility Functions

    /**
     * @brief Swaps the provided linked lists
     * 
     * @param first The first linked list to swap
     * @param second The second linked list to swap
     */
    friend void swap(LinkedList<T>& first, LinkedList<T>& second) {
        // enables ADL - we could use namespaces to change functionality
        using std::swap;

        swap(first.data, second.data);
        swap(first.next, second.next);
    }
};

/**
 * @brief Inserts data at the tail of the linked list
 * 
 * @tparam T The type of the linked list
 * @param head A double pointer to the head of the linked list
 * @param data The data to insert
 */
template <typename T>
void linkedListInsertAtTail(LinkedList<T>** head, const T& data) {
    if (!(*head)) {
        *head = new LinkedList<T>(data);
        return;
    }
    LinkedList<T>* temp = *head;

    // We have to set temp->next, setting temp makes it fail sometimes
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new LinkedList<T>(data);
}

/**
 * @brief Inserts data at the head of the linked list
 * 
 * @tparam T The type of the linked list
 * @param head A double pointer to the head of the linked list
 * @param data The data to insert
 */
template <typename T>
void linkedListInsertAtHead(LinkedList<T>** head, const T& data) {
    LinkedList<T>* temp = *head;
    *head = new LinkedList<T>(data, temp);
}

/**
 * @brief Gets the length of the linked list
 * 
 * @tparam T The type of the linked list
 * @param head A pointer to the head of the linked list
 * @return int The length of the list
 */
template <typename T>
int linkedListGetLength(LinkedList<T>*const& head) {
    LinkedList<T>* temp = head;
    int result = 0;
    while (temp) {
        result++;
        temp = temp->next;
    }
    return result;
}

/**
 * @brief Finds the Nth occurrence of the data in the list 
 * and returns its index. Assumes that the type has an equality operator.
 * 
 * @tparam T The type of the linked list
 * @param head The head of the list to search
 * @param data The data to search for
 * @param n The occurrence of the data in the list
 * @return int The position of the nth occurrence of the data
 */
template <typename T>
int linkedListPositionOfNthOccurrence(
        LinkedList<T>* const& head, const T& data, const int& n) {
    int result = -1, num_found = 0;
    LinkedList<T>* temp = head;
    for (int i = 0; i < linkedListGetLength(head); i++) {
        if (temp->data == data && num_found == n - 1) {
            result = i;
            break;
        } else if (temp->data == data) {
            num_found++;
        }
        temp = temp->next;
    }

    return result;
}

/**
 * @brief Retrieves the Nth node from the list
 * 
 * @tparam T The type of the linked list
 * @param head The head of the list to pull a node from
 * @param n The positional node to retrieve
 * @return LinkedList<T>* A node from the list
 */
template <typename T>
LinkedList<T>* linkedListGetNthNode(LinkedList<T>* const& head, int n) {
    if (n == -1) {return nullptr;}

    LinkedList<T> *temp = head;
    for (size_t i = 0; i < n; i++) {
        if (!temp) {
            break;
        } else {
            temp = temp->next;
        }
    }
    return temp;
}

/**
 * @brief Finds the Nth occurrence of the data in the list and returns its node.
 * Assumes that the type has an equality operator.
 * Because the node comes from the list, it doesn't need to be deleted;
 * it gets deleted when the list's head is deleted.
 * 
 * @tparam T The type of the linked list
 * @param head The head of the list to search
 * @param data The data to search for
 * @param n The occurrence of the data in the list
 * @return LinkedList<T>* A node denoting the nth occurrence of the data
 */
template <typename T>
LinkedList<T>* linkedListFindNthOccurrence(
        LinkedList<T>* const& head,
        const T& data,
        const int& n) {
    int position = linkedListPositionOfNthOccurrence(head, data, n);
    if (position == -1) {return nullptr;}
    return linkedListGetNthNode(head, position);
}

/**
 * @brief Deletes the nth occurrence of the data from the list, if it exists
 * 
 * @tparam T The type of the linked list
 * @param head The head of the list to search
 * @param data The data to search for
 * @param n The occurrence of the data in the list
 */
template <typename T>
void linkedListDeleteNthOccurrence(
        LinkedList<T>** head,
        const T& data,
        const int& n) {
    int position = linkedListPositionOfNthOccurrence(*head, data, n);
    if (position == -1) {return;}

    // no need to make separate cases for head and not head
    LinkedList<T> *dummy = new LinkedList<T>(0, *head), *prev = dummy;
    for (int i = 0; i < position - 1; i++) {prev = prev->next;}

    LinkedList<T> *temp = prev->next;
    prev->next = temp->next;
    temp->next = nullptr;
    delete temp;

    // need to delete dummy down here because for case of head, prev = dummy
    *head = prev->next;
    dummy->next = nullptr;
    delete dummy;
}

#endif
