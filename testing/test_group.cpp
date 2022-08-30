#include <iostream>
#include "test_group.hpp"

void TestGroup::runTests() {
    std::cout << "Running tests" << std::endl;
    int passed = 0, failed = 0, num_tests = tests.size();
    for (size_t i = 0; i < num_tests; i++) {
        std::cout << "Testing " << tests[i].name << "... ";
        if (tests[i].function()) {
            std::cout << "Passed! [" << i + 1 << "/" << num_tests << "]" << std::endl;
            passed++;
        } else {
            std::cout << "Failed! [" << i + 1 << "/" << num_tests << "]" << std::endl;
            failed++;
        }
    }
    std::cout << "Total tests ran: " << num_tests << std::endl;
    std::cout << "Tests passed: " << passed << "/" << num_tests << std::endl;
    std::cout << "Tests failed: " << failed << "/" << num_tests << std::endl;
}