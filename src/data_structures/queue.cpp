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
    Queue(Queue<T>& other) {
      if (other.head) {
        head = new LinkedList<T>(*other.head);
        tail = linkedListGetTail(&head);
      } else {
        head = nullptr;
        tail = nullptr;
      }
    }

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

/**
 * @brief Checks if the queue is empty
 * 
 * @tparam T The type of the queue's data
 * @param queue The queue to check
 * @return true if empty, otherwise false
 */
template <typename T>
bool queueEmpty(const Queue<T>& queue) {
  return !queue.head;
}

/**
 * @brief Get the number of elements in the queue
 * 
 * @tparam T The type of the queue's data
 * @param queue The queue to check
 * @return int The length of the queue
 */
template <typename T>
int queueLength(const Queue<T>& queue) {
  return linkedListGetLength(queue.head);
}

/**
 * @brief Pushes data to the end of the queue
 * 
 * @tparam T The type of the queue's data
 * @param queue The queue to push to
 * @param data The data to push into the queue
 */
template <typename T>
void queuePush(Queue<T>& queue, T data) {
  linkedListInsertAtTail(&queue.tail, data);
  if (!queue.head) {queue.head = queue.tail;} 
  else {queue.tail = queue.tail->next;}
}

/**
 * @brief Gets the front of the queue
 * 
 * @tparam T The type of the queue's data
 * @param queue The queue to get the front of
 * @return T The front of the queue
 */
template <typename T>
T queueFront(const Queue<T>& queue) {
  if (queueEmpty(queue)) {
    throw std::logic_error("Can't get the front of an empty queue.");
  } else {
    return queue.head->data;
  }
}

template <typename T>
void queuePop(Queue<T>& queue) {
  if (queueEmpty(queue)) {
    throw std::logic_error("Can't pop from an empty queue.");
  } else {
    linkedListDeleteNthOccurrence(&queue.head, queue.head->data, 1);
  }
}

#endif