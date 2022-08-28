#ifndef TEST_MANAGER_HPP
#define TEST_MANAGER_HPP

#include <vector>
#include "data_structures/unit_test.hpp"

class TestManager {
public:
    // Constructors
    TestManager(): tests({}) {}

    // Getters
    std::vector<UnitTest> getTests() {return tests;}

    // Utility functions
    void addTest(UnitTest test) {tests.push_back(test);}
    void runTests();
private:
    std::vector<UnitTest> tests;
};

#endif