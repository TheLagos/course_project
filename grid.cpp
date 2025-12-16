#include "grid.h"

#include <string>
#include <iostream>

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };


void Grid::add_edge(Node& current, const Node& neighbour) {
    int distance = 1;
    if (max_distance > 1) {
        distance = rand() % static_cast<int>(max_distance) + 1;
    }
    current.edges.push_back({ neighbour.id, static_cast<double>(distance) });
}

void Grid::generator() {
	graph.assign(width * height, Node());

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

			for (int i = 0; i < 4; ++i) {
				int new_x = x + dx[i];
				int new_y = y + dy[i];

				if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
					int neighbour_id = new_y * width + new_x;
					add_edge(graph[id], graph[neighbour_id]);
				}
			}
		}
	}

    random_endpoints();
}

void Grid::random_endpoints() {
    do {
        start_id = rand() % (width * height);
    } while (graph[start_id].wall);

    do {
        finish_id = rand() % (width * height);
    } while (graph[finish_id].wall || finish_id == start_id);
}

void Grid::generate_graph(int w, int h, int chance, double max_dist) {
	width = w;
	height = h;
	wall_chance = chance;
	max_distance = max_dist;

	generator();
}

void Grid::toggle_wall(int id) {
	if (id < 0 || id >= (width * height)) {
		return;
	}

	if (id == start_id || id == finish_id) {
		return;
	}

	graph[id].wall = !graph[id].wall;
}

bool Grid::set_start(int id) {
    if (id < 0 || id >= (width * height)) {
        return false;
    }

    start_id = id;
    return true;
}

bool Grid::set_finish(int id) {
    if (id < 0 || id >= (width * height)) {
        return false;
    }

    finish_id = id;
    return true;
}

int Grid::get_start() const { return start_id; }
int Grid::get_finish() const { return finish_id; }
int Grid::get_width() const { return width; }
int Grid::get_height() const { return height; }

const std::vector<Node>& Grid::get_graph() const { return graph; }
size_t Grid::size() const { return width * height; }


