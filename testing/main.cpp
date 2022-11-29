#include <iostream>
#include "data_structures/linked_list_tests.hpp"

int main() {
    TestManager test_manager;
    linkedListTestsRegisterTests(&test_manager);
    testManagerRun(test_manager);
    return 0;
}