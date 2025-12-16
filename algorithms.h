#pragma once
#include "graph_types.h"
#include "grid.h"

Result dijkstra(const Grid& grid);

double heuristic(const Node& left, const Node& right);

Result a_star(const Grid& grid);

Result bfs(const Grid& grid);

