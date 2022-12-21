#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "linked_list.cpp"

 /**
  * @brief Generic queue implementation
  * 
  * @tparam T Any type. Assumes that the type implements the equality operator
  */
template <typename T>
struct Queue {
    // Fields
    LinkedList<T>* head;
    LinkedList<T>* tail;

    // Constructors
    Queue(): head(nullptr), tail(nullptr) {}
    Queue(T data): head(new LinkedList<T>(data)), tail(head) {}
    Queue(Queue<T>& other): 
      head(new LinkedList<T>(*other.head)), 
      tail(linkedListGetTail(&head)) {}

    // Destructor
    ~Queue() {delete head;}

    // Operators

    /**
     * @brief Copy assignment operator
     * 
     * @param rhs The queue to copy
     * @return Queue<T>& A copied queue
     */
    Queue<T>& operator = (Queue<T> rhs) {
      *head = *rhs.head;
      *tail = *rhs.tail;
      return *this;
    }

    /**
     * @brief Checks equality of two queues. We could probably just check
     * for the heads being equal, but then we would think the lists are equal
     * if the tails somehow get changed.
     * 
     * @param lhs The first queue to check
     * @param rhs The second queue to check
     * @return true if the queues are equal, otherwise false
     */
    friend bool operator == (Queue<T>& lhs, Queue<T>& rhs) {
      return *lhs.head == *rhs.head && *lhs.tail == *rhs.tail;
    }

    /**
     * @brief Checks inequality of two queues
     * 
     * @param lhs The first queue to check
     * @param rhs The second queue to check
     * @return true if the queues are inequal, otherwise false
     */
    friend bool operator != (Queue<T>& lhs, Queue<T>& rhs) {
      return !(lhs == rhs);
    }
};

#endif