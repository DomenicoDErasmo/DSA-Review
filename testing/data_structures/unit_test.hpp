#ifndef UNIT_TEST_HPP
#define UNIT_TEST_HPP

#include <string>

typedef bool (*test_function)();

struct UnitTest {
    test_function function;
    std::string name;
    UnitTest(): function(nullptr), name("") {}
    UnitTest(test_function in_function, std::string in_name): function(in_function), name(in_name) {}
};

#endif