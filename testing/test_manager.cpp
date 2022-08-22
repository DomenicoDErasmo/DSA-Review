#include "test_manager.hpp"
#include "data_structures/linked_list_tests.hpp"
#include <iostream>

void TestManager::runTests() {
    int passed = 0, failed = 0;
    for (size_t i = 0; i < tests.size(); i++) {
        std::cout << "Running test: " << tests[i].getDescription() << "... ";
        if ((*tests[i].getTestFunction())()) {
            std::cout << "Passed!" << std::endl;
            passed++;
        } else {
            std::cout << "Failed!" << std::endl;
            failed++;
        }
    }
    std::cout << "Passed: " << passed << "/" << tests.size() << std::endl;
    std::cout << "Failed: " << failed << "/" << tests.size() << std::endl;
}