#include <iostream>
#include "data_structures/doubly_linked_list.tpp"

int main() {
    // Init
    DoublyLinkedList<int>* head = new DoublyLinkedList<int>(4);
    std::cout << *head << std::endl;
    return 0;
}