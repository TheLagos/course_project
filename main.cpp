#include <iostream>
#include <ctime>
#include "algorithms.h"
#include "graph_generator.h"

void print_result(const Result& result, std::string&& algorithm_name) {
    std::cout << algorithm_name << " results: " << "\n"
        << "Successfull - " << result.found << "\n"
        << "Total distance - " << result.total_distance << "\n"
        << "Visited nodes count - " << result.visited_nodes << "\n"
        << "Duration - " << result.duration << " ms \n"
        << "Path - ";

    for (const int& node : result.path) {
        std::cout << node;
        if (node != result.path.back()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n\n";
}

int main()
{
    std::srand(std::time(nullptr));
    std::vector<Node> graph = node_generator(5, 5, 5, 15);

    auto dj_res = dijkstra(1, 16, graph);
    auto a_res = a_star(1, 16, graph);

    print_result(dj_res, "Dijkstra");
    print_result(a_res, "AStar");
    return 0;
}
