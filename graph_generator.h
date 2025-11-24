#include "graph_structure.h"
#include <cstdlib>

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

void add_edge(Node& current, const Node& neighbour, double max_dist);

std::vector<Node> node_generator(int width, int height, int wall_chance, double max_dist);