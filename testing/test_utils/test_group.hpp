#ifndef TESTING_TEST_UTILS_TEST_GROUP_HPP_
#define TESTING_TEST_UTILS_TEST_GROUP_HPP_

// TODO(dderasmo): replace with linked list
#include <vector>
#include <string>
#include "test_utils/unit_test.hpp"

struct TestGroup {
 public:
    std::string group_name;
    std::vector<UnitTest> unit_tests;

    explicit TestGroup(const std::string& group_name):
        group_name(group_name), unit_tests(std::vector<UnitTest>()) {}
};

void testGroupAddTest(TestGroup* test_group, const UnitTest& unit_test);

void testGroupRun(const TestGroup& test_group);

#endif  // TESTING_TEST_UTILS_TEST_GROUP_HPP_
