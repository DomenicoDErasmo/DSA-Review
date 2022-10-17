#include <iostream>
#include "data_structures/queue.tpp"

int main() {
    Queue<int> queue(5);
    std::cout << queue.head << ", " << queue.tail << std::endl;
    return 0;
}