#include "graph_tests.hpp"
#include <data_structures/graph.cpp>

bool graphTestDefaultConstructor() {
    bool result = true;

    Graph<int> empty;
    result &= !empty.adjacency_matrix;

    return result;
}

// TODO: reimplement all of the below

bool graphTestCopyConstructor() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy(original);
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_matrix, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

    Graph<int> original;
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&original.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    Graph<int> copy = original;
    LinkedList<AdjacencyList<int>>* original_adj_node = 
        linkedListGetNthOccurrence(
            original.adjacency_matrix, AdjacencyList<int>(5), 1);
    LinkedList<AdjacencyList<int>>* copy_adj_node = 
        linkedListGetNthOccurrence(
            copy.adjacency_matrix, AdjacencyList<int>(5), 1);
    result &= *copy_adj_node->data.edges == *original_adj_node->data.edges;

    return result;
}

bool graphTestEqualityOperator() {
    bool result = true;

    Graph<int> inequal_lhs;
    linkedListInsertAtTail(
        &inequal_lhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &inequal_lhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            inequal_lhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4));
    Graph<int> inequal_rhs;
    linkedListInsertAtTail(
        &inequal_rhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &inequal_rhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            inequal_rhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4, 1.1));
    result &= !(inequal_lhs == inequal_rhs);

    Graph<int> equal_lhs;
    linkedListInsertAtTail(
        &equal_lhs.adjacency_matrix, 
        AdjacencyList<int>(4));
    linkedListInsertAtTail(
        &equal_lhs.adjacency_matrix, 
        AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            equal_lhs.adjacency_matrix, 
            AdjacencyList<int>(4), 
            1)->data,
        Edge<int>(5, 4));
    Graph<int> equal_rhs;
    linkedListInsertAtTail(&equal_rhs.adjacency_matrix, AdjacencyList<int>(4));
    linkedListInsertAtTail(&equal_rhs.adjacency_matrix, AdjacencyList<int>(5));
    adjacencyListAddEdge(
        linkedListGetNthOccurrence(
            equal_rhs.adjacency_matrix, AdjacencyList<int>(4), 1)->data,
        Edge<int>(5, 4));
    result &= equal_lhs == equal_rhs;
    return result;
}

bool graphTestGetNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphGetNode(node_not_found, 4);

    Graph<int> node_found;
    linkedListInsertAtTail(&node_found.adjacency_matrix, AdjacencyList<int>(5));
    LinkedList<AdjacencyList<int>>* list = graphGetNode(node_found, 5);
    result &= list->data.from == 5;

    return result;
}

bool graphTestHasNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphHasNode(node_not_found, 5);

    Graph<int> node_found;
    result &= !node_found.adjacency_matrix;
    linkedListInsertAtTail(
        &node_found.adjacency_matrix, 
        AdjacencyList<int>(5));
    result &= graphHasNode(node_found, 5);

    return result;
}

bool graphTestAddNode() {
    bool result = true;

    Graph<int> can_insert;
    result &= !can_insert.adjacency_matrix;
    graphAddNode(can_insert, 4);
    result &= can_insert.adjacency_matrix->data == 4;

    Graph<int> already_found;
    result &= !already_found.adjacency_matrix;
    linkedListInsertAtTail(
        &already_found.adjacency_matrix, 
        AdjacencyList<int>(5));
    result &= linkedListGetLength(already_found.adjacency_matrix) == 1;
    graphAddNode(already_found, 5);
    result &= linkedListGetLength(already_found.adjacency_matrix) == 1;

    return result;
}

bool graphTestAddEdge() {
    bool result = true;

    Graph<int> adj_list_not_found;
    try {
        graphAddEdge(adj_list_not_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> edge_found;
    graphAddNode(edge_found, 4);
    linkedListInsertAtTail(
        &edge_found.adjacency_matrix->data.edges, 
        Edge<int>(4, 3));
    try {
        graphAddEdge(edge_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> found;
    graphAddNode(found, 4);
    graphAddEdge(found, Edge<int>(4, 5, 1.2));
    result &= found.adjacency_matrix->data.edges->data == Edge<int>(4, 5, 1.2);

    return result;
}

void graphTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("graph");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        graphTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        graphTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator", 
        graphTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        graphTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("get node", graphTestGetNode));
    testGroupAddTest(&test_group, UnitTest("has node", graphTestHasNode));
    testGroupAddTest(&test_group, UnitTest("add node", graphTestAddNode));
    testGroupAddTest(&test_group, UnitTest("add edge", graphTestAddEdge));

    testManagerAddTestGroup(test_manager, test_group);
}
