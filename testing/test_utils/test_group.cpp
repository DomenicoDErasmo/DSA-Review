#include "test_group.hpp"
#include <iostream>

void testGroupRun(const TestGroup& test_group) {
    std::cout << "===========================================" << std::endl;
    std::cout << "Running tests for " << test_group.group_name
        << std::endl << std::endl;

    // TODO(dderasmo): Replace with linked list.
    size_t total = test_group.unit_tests.size(), passed = 0, failed = 0;
    for (size_t i = 0; i < total; i++) {
        UnitTest unit_test = test_group.unit_tests[i];
        std::cout << "Testing " << unit_test.test_name
            << " [" << i + 1 << "/" << total << "]: ";
        if (unit_test.test_function()) {
            std::cout << "Passed!" << std::endl;
            passed++;
        } else {
            std::cout << "Failed!" << std::endl;
            failed++;
        }
    }
    std::cout << std::endl;
    std::cout << "Passed: " << passed << "/" << total << std::endl;
    std::cout << "Failed: " << failed << "/" << total << std::endl;
    std::cout << "===========================================" << std::endl;
}

void testGroupAddTest(TestGroup* test_group, const UnitTest& unit_test) {
    test_group->unit_tests.push_back(unit_test);
}
