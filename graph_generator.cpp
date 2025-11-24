#include "graph_generator.h"

void add_edge(Node& current, const Node& neighbour, double max_dist) {
	if (neighbour.wall) {
		return;
	}

	int distance = rand() % static_cast<int>(max_dist) + 1;
	current.edges.push_back({ neighbour.id, static_cast<double>(distance) });
}

std::vector<Node> node_generator(int width, int height, int wall_chance, double max_dist) {
	std::vector<Node> graph(width * height);

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int id = y * width + x;
			bool wall = false;
			if (wall_chance > 0) {
				wall = (rand() % wall_chance) == 0;
			}

			graph[id] = { id, wall, x, y };
		}
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int id = y * width + x;
			Node& current = graph[id];

			if (current.wall) {
				continue;
			}

			for (int i = 0; i < 4; ++i) {
				int new_x = x + dx[i];
				int new_y = y + dy[i];

				if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
					int neighbour_id = new_y * width + new_x;
					add_edge(graph[id], graph[neighbour_id], max_dist);
				}
			}
		}
	}
	return graph;
}