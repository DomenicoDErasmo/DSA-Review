#include <iostream>
#include "test_manager.hpp"
#include "data_structures/linked_list_tests.hpp"

int main() {
    TestManager test_manager;
    registerLinkedListTests(test_manager);
    test_manager.runTests();
    return 0;
}