#include "test_manager.hpp"
#include <iostream>

void TestManager::runTests() {
    std::cout << "Running all test groups" << std::endl;
    for (int i = 0; i < test_groups.size(); i++) {
        std::cout << "Running tests for " << test_groups[i].getName() << std::endl;
        test_groups[i].runTests();
    std::cout << "Done running tests for " << test_groups[i].getName() << std::endl;
    }
}