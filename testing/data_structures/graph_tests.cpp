#include "graph_tests.hpp"
#include <data_structures/graph.cpp>

const std::string TESTING = "../resources/testing/";

bool graphTestDefaultConstructor() {
    bool result = true;

    Graph<int> empty;
    result &= !empty.adjacency_matrix;

    return result;
}

/**
 * @brief Helper function for the file path constructor.
 * 
 * @param graph The graph to check
 * @param node The node to check
 * @param length The expected length of the node's adjacency list
 * @param n The edge within the adjacency list to check
 * @param to The expected to value of the nth edge
 * @return true if all checks succeed, otherwise false 
 */
bool graphTestFilePathConstructorHelper(
        const Graph<int>& graph,
        int node,
        int length,
        int n,
        int to) {
    bool result = true;
    AdjacencyList<int> adj_list = linkedListGetNthOccurrence(
        graph.adjacency_matrix,
        AdjacencyList<int>(node),
        1,
        adjacencyListWeakEquality)->data;
    if (length == -1) {
        result &= !adj_list.edges;
    }
    else {
        result &= linkedListGetLength(adj_list.edges) == length;
        result &= linkedListGetNthNode(adj_list.edges, n)->data.to == to;
    }
    return result;
}

bool graphTestFilePathConstructor() {
    bool result = true;

    std::string graph_file = "file_path_constructor.txt";

    Graph<int> directed(TESTING + graph_file, GRAPH_DIRECTED);
    result &= linkedListGetLength(directed.adjacency_matrix) == 10;
    result &= graphTestFilePathConstructorHelper(directed, 0, -1, 0, -1);
    result &= graphTestFilePathConstructorHelper(directed, 1, 1, 0, 2);
    result &= graphTestFilePathConstructorHelper(directed, 3, 2, 0, 4);
    result &= graphTestFilePathConstructorHelper(directed, 3, 2, 1, 5);
    result &= graphTestFilePathConstructorHelper(directed, 4, 1, 0, 5);
    result &= graphTestFilePathConstructorHelper(directed, 6, 2, 0, 7);
    result &= graphTestFilePathConstructorHelper(directed, 6, 2, 1, 9);
    result &= graphTestFilePathConstructorHelper(directed, 8, 2, 0, 7);
    result &= graphTestFilePathConstructorHelper(directed, 8, 2, 1, 9);

    Graph<int> undirected(TESTING + graph_file, GRAPH_UNDIRECTED);
    result &= graphTestFilePathConstructorHelper(undirected, 5, 2, 0, 3);
    result &= graphTestFilePathConstructorHelper(undirected, 5, 2, 1, 4);

    return result;
}

bool graphTestCopyConstructor() {
    bool result = true;

    Graph<int> original(TESTING + "copy_constructor.txt", GRAPH_DIRECTED);
    Graph<int> copy(original);
    result &= (*copy.adjacency_matrix->data.edges 
    == *original.adjacency_matrix->data.edges);

    return result;
}

bool graphTestAssignmentOperator() {
    bool result = true;

    Graph<int> original(TESTING + "assignment_operator.txt", GRAPH_DIRECTED);
    Graph<int> copy(original);
    result &= (*copy.adjacency_matrix->data.edges 
    == *original.adjacency_matrix->data.edges);

    return result;
}

bool graphTestEqualityOperator() {
    const std::string directory = TESTING + "equality_operator/";
    bool result = true;

    Graph<int> inequal_lhs(directory + "inequal_lhs.txt", GRAPH_DIRECTED);
    Graph<int> inequal_rhs(directory + "inequal_rhs.txt", GRAPH_DIRECTED);
    result &= !(inequal_lhs == inequal_rhs);

    Graph<int> equal_lhs(directory + "equal_lhs.txt", GRAPH_DIRECTED);
    Graph<int> equal_rhs(directory + "equal_rhs.txt", GRAPH_DIRECTED);
    result &= equal_lhs == equal_rhs;

    return result;
}

bool graphTestGetNumNodes() {
    bool result = true;

    Graph<int> graph(TESTING + "get_num_nodes_7.txt", GRAPH_DIRECTED);
    result &= graphGetNumNodes(graph) == 7;

    return result;
}

bool graphTestGetNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphGetNode(node_not_found, 4);

    Graph<int> node_found(TESTING + "get_node.txt", GRAPH_DIRECTED);
    LinkedList<AdjacencyList<int>>* list = graphGetNode(node_found, 5);
    result &= list->data.from == 5;

    return result;
}

bool graphTestHasNode() {
    bool result = true;

    Graph<int> node_not_found;
    result &= !graphHasNode(node_not_found, 5);

    Graph<int> node_found(TESTING + "has_node.txt", GRAPH_UNDIRECTED);
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

bool graphTestUpdateNode() {
    bool result = true;
    std::string directory = TESTING + "update_node/";

    Graph<int> node_not_found(
        directory + "node_not_found.txt", 
        GRAPH_UNDIRECTED);
    graphUpdateNode(node_not_found, 1, 4);
    result &= graphHasNode(node_not_found, 4);

    Graph<int> node_found(directory + "node_found.txt", GRAPH_UNDIRECTED);
    try {
        graphUpdateNode(node_found, 1, 3);
    } catch (std::logic_error) {
        result &= true;
    } catch (...) {
        result &= false;
    }

    return result;
}

bool graphTestDeleteNode() {
    bool result = true;
    std::string directory = TESTING + "delete_node/";

    Graph<int> node_found(directory + "node_found.txt", GRAPH_DIRECTED);
    result &= graphGetNumNodes(node_found) == 5;
    graphDeleteNode(node_found, 2);
    result &= graphGetNumNodes(node_found) == 4;

    Graph<int> node_not_found(directory + "node_not_found.txt", GRAPH_DIRECTED);
    result &= graphGetNumNodes(node_not_found) == 4;
    graphDeleteNode(node_not_found, 4);
    result &= graphGetNumNodes(node_not_found) == 4;

    return result;
}

bool graphTestGetEdge() {
    bool result = true;

    Graph<int> adj_list_not_found;
    try {
        graphGetEdge(adj_list_not_found, Edge<int>(4, 3));
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> has_edge;
    graphAddNode(has_edge, 4);
    LinkedList<AdjacencyList<int>>* adj_list = graphGetNode(has_edge, 4);
    linkedListInsertAtTail(&adj_list->data.edges, Edge<int>(4, 5));
    LinkedList<Edge<int>>* edge = graphGetEdge(has_edge, Edge<int>(4, 5));
    result &= edge->data.to == 5;
    result &= edge == adj_list->data.edges;
    edge->data.to = 3;
    result &= adj_list->data.edges->data.to == 3;

    return result;
}

bool graphTestHasEdge() {
    bool result = true;

    Graph<int> missing_node;
    result &= !graphHasEdge(missing_node, Edge<int>(4, 5));

    Graph<int> missing_edge;
    graphAddNode(missing_edge, 4);
    result &= !graphHasEdge(missing_node, Edge<int>(4, 5));

    Graph<int> has_edge;
    graphAddNode(has_edge, 4);
    graphAddEdge(has_edge, Edge<int>(4, 5));
    result &= graphHasEdge(has_edge, Edge<int>(4, 5));

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

bool graphTestUpdateEdge() {
    bool result = true;

    std::string directory = TESTING + "update_edge/";
    Graph<int> edge_found(directory + "edge_found.txt", GRAPH_DIRECTED);
    try {
        graphUpdateEdge(edge_found, {1, 2, 5}, {1, 3, 6});
    } catch (std::logic_error) {
        result &= true;
    } catch(...) {
        result &= false;
    }

    Graph<int> edge_not_found(
        directory + "edge_not_found.txt", 
        GRAPH_UNDIRECTED);
    graphUpdateEdge(edge_not_found, {1, 2, 5}, {1, 4, 6});
    result &= graphHasEdge(edge_not_found, {1, 4, 6});
    result &= !graphHasEdge(edge_not_found, {1, 2, 5});

    return result;
}

bool graphTestDeleteEdge() {
    bool result = true;

    std::string directory = TESTING + "delete_edge/";
    Graph<int> edge_found(directory + "edge_found.txt", GRAPH_DIRECTED);
    graphDeleteEdge(edge_found, {1, 2});
    result &= !graphHasEdge(edge_found, {1, 2, 5});

    Graph<int> edge_not_found(directory + "edge_not_found.txt", GRAPH_DIRECTED);
    graphDeleteEdge(edge_not_found, {3, 4});
    result &= !graphHasEdge(edge_not_found, {3, 4, 5});

    return result;
}

void graphTestRegisterTests(TestManager* test_manager) {
    TestGroup test_group("graph");

    testGroupAddTest(&test_group, UnitTest("default constructor", 
        graphTestDefaultConstructor));
    testGroupAddTest(&test_group, UnitTest("file path constructor", 
        graphTestFilePathConstructor));
    testGroupAddTest(&test_group, UnitTest("copy constructor", 
        graphTestCopyConstructor));
    testGroupAddTest(&test_group, UnitTest("assignment operator", 
        graphTestAssignmentOperator));
    testGroupAddTest(&test_group, UnitTest("equality operator", 
        graphTestEqualityOperator));
    testGroupAddTest(&test_group, UnitTest("get num nodes", 
        graphTestGetNumNodes));
    testGroupAddTest(&test_group, UnitTest("get node", graphTestGetNode));
    testGroupAddTest(&test_group, UnitTest("has node", graphTestHasNode));
    testGroupAddTest(&test_group, UnitTest("add node", graphTestAddNode));
    testGroupAddTest(&test_group, UnitTest("update node", graphTestUpdateNode));
    testGroupAddTest(&test_group, UnitTest("delete node", graphTestDeleteNode));
    testGroupAddTest(&test_group, UnitTest("get edge", graphTestGetEdge));
    testGroupAddTest(&test_group, UnitTest("has edge", graphTestHasEdge));
    testGroupAddTest(&test_group, UnitTest("add edge", graphTestAddEdge));
    testGroupAddTest(&test_group, UnitTest("update edge", graphTestUpdateEdge));
    testGroupAddTest(&test_group, UnitTest("delete edge", graphTestDeleteEdge));

    testManagerAddTestGroup(test_manager, test_group);
}
