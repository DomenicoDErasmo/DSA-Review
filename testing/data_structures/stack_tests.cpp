#include "stack_tests.hpp"

void stackTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("stack");

    testManagerAddTestGroup(test_manager, test_group);
}