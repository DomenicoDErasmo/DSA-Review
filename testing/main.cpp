#include <iostream>
#include "data_structures/linked_list_tests.hpp"
#include "data_structures/binary_tree_tests.hpp"

int main() {
    TestManager test_manager;
    linkedListTestRegisterTests(&test_manager);
    binaryTreeTestRegisterTests(&test_manager);
    testManagerRun(test_manager);
    return 0;
}