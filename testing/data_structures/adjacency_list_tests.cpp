#include "adjacency_list_tests.hpp"
#include <data_structures/queue.cpp>

void adjacencyListTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("adjacency list");

    testManagerAddTestGroup(test_manager, test_group);
}
