#ifndef TEST_MANAGER_HPP
#define TEST_MANAGER_HPP

#include <vector>
#include "test_group.hpp"

class TestManager {
public:
    // Constructors
    TestManager(): test_groups({}) {}

    // Getters
    std::vector<TestGroup> getTestGroups() {return test_groups;}

    // Utility functions
    void addTestGroup(TestGroup test_group) {test_groups.push_back(test_group);}
    void runTests();
private:
    std::vector<TestGroup> test_groups;
};

#endif