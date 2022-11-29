#ifndef TESTING_TEST_UTILS_UNIT_TEST_HPP_
#define TESTING_TEST_UTILS_UNIT_TEST_HPP_

#include <iostream>
#include <string>

typedef bool (*test_fn)();

struct UnitTest {
 public:
    // Fields
    std::string test_name;
    test_fn test_function;

    // Constructors
    UnitTest(const std::string& test_name, const test_fn& test_function):
        test_name(test_name), test_function(test_function) {}
};

#endif  // TESTING_TEST_UTILS_UNIT_TEST_HPP_
