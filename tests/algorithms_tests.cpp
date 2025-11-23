#include <gtest/gtest.h>
#include <algorithms.h>
#include <graph_structure.h>

void check_algorithms(const std::vector<Node>& graph, int start, int end, bool exp_find, double exp_dist, const std::vector<int>& exp_path) {
    auto d_res = dijkstra(start, end, graph);
    EXPECT_EQ(exp_find, d_res.found);
    if (exp_find) {
        EXPECT_DOUBLE_EQ(exp_dist, d_res.total_distance);
        EXPECT_EQ(exp_path, d_res.path);
    }

    auto a_res = a_star(start, end, graph);
    EXPECT_EQ(exp_find, a_res.found);
    if (exp_find) {
        EXPECT_DOUBLE_EQ(exp_dist, a_res.total_distance);
        EXPECT_EQ(exp_path, a_res.path);
    }
}

TEST(AlgorithmsTests, WeightsPriority) {
    std::vector<Node> graph(3);
    graph[0] = { 0, {{2, 100.0}, {1, 1.0}}, 0, 0 };
    graph[1] = { 1, {{2, 1.0}}, 1, 1 };
    graph[2] = { 2, {}, 2, 0 };

    check_algorithms(graph, 0, 2, true, 2.0, { 0, 1, 2 });
}

TEST(AlgorithmsTests, ObstacleBypass) {
    std::vector<Node> graph(4);
    graph[0] = { 0, {{1, 1.0}}, 0, 0 };
    graph[1] = { 1, {{2, 1.0}}, 0, 1 };
    graph[2] = { 2, {{3, 1.41}}, 1, 1 };
    graph[3] = { 3, {}, 1, 0 };

    check_algorithms(graph, 0, 3, true, 3.41, { 0, 1, 2, 3 });
}

TEST(AlgorithmsTests, DisconnectedGraph) {
    std::vector<Node> graph(4);
    graph[0] = { 0, {{1, 1.0}}, 0, 0 };
    graph[1] = { 1, {{0, 1.0}}, 0, 1 };
    graph[2] = { 2, {{3, 1.0}}, 10, 10 };
    graph[3] = { 3, {{2, 1.0}}, 10, 11 };

    check_algorithms(graph, 0, 3, false, 0.0, {});
}

TEST(AlgorithmsTests, StartEqualsEnd) {
    std::vector<Node> graph(1);
    graph[0] = { 0, {{0, 1.0}}, 5, 5 };

    check_algorithms(graph, 0, 0, true, 0.0, { 0 });
}