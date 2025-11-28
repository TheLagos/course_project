#pragma once
#include "graph_types.h"
#include <cstdlib>

class Grid {
private:
	int start_id = -1, finish_id = -1;
	int width = 0, height = 0;

	int wall_chance = 0;
	double max_distance = 0;

	std::vector<Node> graph;

	void add_edge(Node& current, const Node& neighbour);
	void generator();
public:
	Grid() = default;
	~Grid() = default;

	void generate_graph(int width, int height, int chance, double max_dist);
	void toggle_wall(int id);

	bool set_start(int id);
	bool set_finish(int id);

	int get_start() const;
	int get_finish() const;

	const std::vector<Node>& get_graph() const;
	size_t size() const;
};