#include <iostream>
#include "test_utils/test_manager.hpp"
#include "data_structures/linked_list_tests.hpp"
#include "data_structures/binary_tree_tests.hpp"
#include "data_structures/stack_tests.hpp"

int main() {
    TestManager test_manager;
    test_manager.addTestGroup(linkedListRegisterTests());
    test_manager.addTestGroup(binaryTreeRegisterTests());
    test_manager.addTestGroup(stackRegisterTests());
    test_manager.runTests();
    return 0;
}