#include "test_manager.hpp"
#include "test_group.hpp"
#include <iostream>

void testManagerRun(const TestManager& test_manager) {
    std::cout << "Running tests." << std::endl;

    // TODO(dderasmo): replace with linked list
    for (size_t i = 0; i < test_manager.test_groups.size(); i++) {
        TestGroup test_group = test_manager.test_groups[i];
        std::cout << "Running tests for group "
            << test_group.group_name << std::endl;
        testGroupRun(test_group);
    }
    std::cout << "Done!" << std::endl;
}

void testManagerAddTestGroup(
        TestManager* test_manager, 
        const TestGroup& test_group) {
    test_manager->test_groups.push_back(test_group);
}