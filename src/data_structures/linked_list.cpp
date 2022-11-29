#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

template <typename T>
struct LinkedList {
    // Fields
    T data;
    LinkedList<T>* next;

    // Constructors

    // Default - Assumes that the type has a default constructor
    LinkedList(): data(T()), next(nullptr) {}

    explicit LinkedList(const T& data): data(data), next(nullptr) {}
    LinkedList(const T& data,
               LinkedList<T>* const& next): data(data), next(next) {}
    LinkedList(const LinkedList<T>& other) {
        data = other.data;
        if (other.next) {
            next = new LinkedList<T>(*other.next);
        } else {
            next = nullptr;
        }
    }

    // Destructors
    ~LinkedList() {
        delete next;
    }

    // Operators

    /**
     * @brief Copy assignment operator. Uses the copy-and-swap idiom from
     * https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
     * 
     * As discussed in the aforementioned link, we pass by value for optimization.
     * 
     * @param rhs The linked list to copy
     * @return LinkedList<T>& A copied linked list
     */
    LinkedList<T>& operator = (LinkedList<T> rhs) {
        swap(*this, other);
        return *this;
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
        LinkedList<T>* const& head, T data, int n) {
    LinkedList<T> *result = nullptr, *temp = head;
    int num_found = 0;

    for (int i = 0; i < linkedListGetLength(head); i++) {
        if (temp->data == data && num_found == n - 1) {
            result = temp;
            break;
        } else if (temp->data == data) {
            num_found++;
        }
        temp = temp->next;
    }

    return result;
}

#endif
