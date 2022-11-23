#include "graph_tests.hpp"

#include <data_structures/graph.cpp>
#include <iostream>
#include <sstream>

bool graphTestInsertEdge() {
    bool result = true;

    Graph<int>* g = new Graph<int>();
    result &= (!g->edges);
    graphInsertEdge(g, 4);
    result &= (g->edges->data.data == 4);
    graphInsertEdge(g, 3);
    result &= (g->edges->left->data == 3);
    graphInsertEdge(g, 5);
    result &= (g->edges->right->data == 5);

    return result;
}

bool graphTestToString() {
    bool result = true;

    Graph<int>* empty = new Graph<int>();
    result &= (empty->to_string() == "[\n]");

    return result;
}

TestGroup graphRegsiterTests() {
    TestGroup test_group("graphs");
    test_group.addTest(UnitTest(graphTestInsertEdge, "insert edge"));
    test_group.addTest(UnitTest(graphTestToString, "to string"));
    return test_group;
}