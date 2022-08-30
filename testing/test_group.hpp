#ifndef TEST_GROUP_HPP
#define TEST_GROUP_HPP

#include <vector>
#include "unit_test.hpp"
class TestGroup {
public:
    // Constructors
    TestGroup(): tests({}), name("") {}
    TestGroup(std::string in_name): tests({}), name(in_name) {}

    // Getters
    std::vector<UnitTest> getTests() {return tests;}
    std::string getName() {return name;}

    // Setters
    void setName(std::string in_name) {name = in_name;}

    // Utility functions
    void addTest(UnitTest test) {tests.push_back(test);}
    void runTests();
private:
    std::vector<UnitTest> tests;
    std::string name;
};

#endif