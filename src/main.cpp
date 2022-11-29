#include <iostream>
#include "data_structures/linked_list.cpp"

int main() {
    std::cout << "Hello world! Source." << std::endl;
    LinkedList<int>* head = nullptr;
    std::cout << head->data << ", " << head->next->data << std::endl;
    return 0;
}