#include <gtest/gtest.h>
#include "../algorithms.h"
#include "../grid.h"
#include "../graph_types.h"

void check_algorithms(const Grid& grid, bool exp_find) {
    auto d_res = dijkstra(grid);
    EXPECT_EQ(d_res.found, exp_find) << "Dijkstra result mismatch";

    auto a_res = a_star(grid);
    EXPECT_EQ(a_res.found, exp_find) << "A* result mismatch";
    
    if (exp_find) {
        EXPECT_GT(d_res.total_distance, 0.0);
        EXPECT_FALSE(d_res.path.empty());
        
        EXPECT_GT(a_res.total_distance, 0.0);
        EXPECT_FALSE(a_res.path.empty());
    }
}

TEST(GridLogicTests, SafetyChecks) {
    Grid grid;
    grid.generate_graph(5, 5, 0, 10.0);

    EXPECT_FALSE(grid.set_start(-1));
    EXPECT_FALSE(grid.set_start(100));

    EXPECT_FALSE(grid.set_finish(-5));
    EXPECT_FALSE(grid.set_finish(25));

    EXPECT_TRUE(grid.set_start(0));
    EXPECT_FALSE(grid.set_finish(0));
    
    EXPECT_TRUE(grid.set_finish(1));
    EXPECT_EQ(grid.get_start(), 0);
    EXPECT_EQ(grid.get_finish(), 1);
}

TEST(PathfindingTests, SimpleCleanPath) {
    Grid grid;
    grid.generate_graph(3, 3, 0, 1.0); 

    grid.set_start(0);
    grid.set_finish(8);

    check_algorithms(grid, true);
}

TEST(PathfindingTests, WallBlockade) {
    Grid grid;
    grid.generate_graph(3, 1, 0, 1.0);

    grid.set_start(0);
    grid.set_finish(2);

    check_algorithms(grid, true);

    grid.toggle_wall(1);

    check_algorithms(grid, false);
}

TEST(GridLogicTests, ProtectedPoints) {
    Grid grid;
    grid.generate_graph(3, 3, 0, 1.0);

    grid.set_start(0);
    grid.set_finish(8);

    grid.toggle_wall(0);
    
    const auto& nodes = grid.get_graph();
    EXPECT_FALSE(nodes[0].wall) << "Start node should NOT become a wall";

    grid.toggle_wall(8);
    EXPECT_FALSE(nodes[8].wall) << "Finish node should NOT become a wall";

    grid.toggle_wall(4);
    EXPECT_TRUE(nodes[4].wall) << "Normal node SHOULD become a wall";
}

TEST(GridLogicTests, AutoFixWall) {
    Grid grid;
    grid.generate_graph(3, 3, 0, 1.0);

    grid.toggle_wall(5);
    const auto& nodes_before = grid.get_graph();
    ASSERT_TRUE(nodes_before[5].wall);

    bool success = grid.set_start(5);

    EXPECT_TRUE(success);
    EXPECT_EQ(grid.get_start(), 5);
    
    const auto& nodes_after = grid.get_graph();
    EXPECT_FALSE(nodes_after[5].wall) << "Wall should be removed automatically when setting start";
}