#ifndef QUEUE_TPP
#define QUEUE_TPP

#include "doubly_linked_list.cpp"

template <typename T>
struct Queue {
    Queue(): head(nullptr), tail(nullptr) {}
    Queue(T data): head(new DoublyLinkedList<T>(data)), tail(head) {}
    ~Queue() {delete head;}

    DoublyLinkedList<T> *head, *tail;
};

template <typename T>
void queuePush(Queue<T>& queue, T data) {
    if (!queue.head) {
        queue.head = new DoublyLinkedList<T>(data);
        queue.tail = queue.head;
        return;
    }
    doublyLinkedListInsertNext(queue.tail, data);
    queue.tail = queue.tail->next;
}

template <typename T>
void queuePop(Queue<T>& queue) {
    bool move_tail = (queue.head == queue.tail);
    doublyLinkedListDeleteNode(queue.head, queue.head);
    if (move_tail) {queue.tail = nullptr;}
}

template <typename T>
/**
 * @brief Returns the front of the queue. Assumes that the queue is not empty.
 * 
 * @param queue A reference to a queue
 * @return T The front of the queue
 */
T queueFront(Queue<T>& queue) {
    return queue.head->data;
}

template <typename T>
bool queueIsEmpty(Queue<T>& queue) {
    return !queue.head;
}

#endif