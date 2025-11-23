#pragma once
#include "graph_structure.h"

Result dijkstra(int start_id, int end_id, const std::vector<Node>& graph);

double heuristic(const Node& left, const Node& right);

Result a_star(int start_id, int end_id, const std::vector<Node>& graph);

