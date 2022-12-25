#include <iostream>
#include "data_structures/linked_list_tests.hpp"
#include "data_structures/double_linked_list_tests.hpp"
#include "data_structures/binary_tree_tests.hpp"
#include "data_structures/stack_tests.hpp"
#include "data_structures/queue_tests.hpp"
#include "data_structures/adjacency_list_tests.hpp"
#include "data_structures/edge_tests.hpp"

int main() {
    TestManager test_manager;
    linkedListTestRegisterTests(&test_manager);
    doubleLinkedListTestRegisterTests(&test_manager);
    binaryTreeTestRegisterTests(&test_manager);
    stackTestRegisterTests(&test_manager);
    queueTestRegisterTests(&test_manager);
    edgeTestRegisterTests(&test_manager);
    adjacencyListTestRegisterTests(&test_manager);
    testManagerRun(test_manager);
    return 0;
}