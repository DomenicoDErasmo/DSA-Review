#ifndef TEST_MANAGER_HPP
#define TEST_MANAGER_HPP

#include <string>
#include <vector>

typedef bool (*test_fn)();

class Test {
public:
    // Constructors
    Test(): test_function(nullptr), description("Unassigned") {}
    Test(test_fn in_test_function, std::string in_description): test_function(in_test_function), description(in_description) {}

    // Getters
    test_fn getTestFunction() {return test_function;}
    std::string getDescription() {return description;}

    // Setters
    void setTestFunction(test_fn in_test_function) {test_function = in_test_function;}
    void setDescription(std::string in_description) {description = in_description;}

private:
    test_fn test_function;
    std::string description;
};

class TestManager {
public:
    // Constructors
    TestManager(): tests(std::vector<Test>{}) {}
    TestManager(std::vector<Test> in_tests): tests(in_tests) {}

    // Getters
    std::vector<Test> getTests() {return tests;}    

    // Setters
    void setTests(std::vector<Test> in_tests) {tests = in_tests;}

    // Utility functions
    void runTests();
    void addTest(Test test) {tests.push_back(test);}
private:
    std::vector<Test> tests;
};

#endif