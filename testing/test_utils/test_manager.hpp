#ifndef TESTING_TEST_UTILS_TEST_MANAGER_HPP_
#define TESTING_TEST_UTILS_TEST_MANAGER_HPP_

// TODO(dderasmo): replace with linked list
#include <vector>
#include "test_group.hpp"

struct TestManager {
 public:
    // Fields
    std::vector<TestGroup> test_groups;

    // Constructors
    TestManager(): test_groups(std::vector<TestGroup>()) {}
};

void testManagerRun(const TestManager& test_manager);
void testManagerAddTestGroup(
    TestManager* test_manager, 
    const TestGroup& test_group);

#endif  // TESTING_TEST_UTILS_TEST_MANAGER_HPP_
