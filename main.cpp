#include <iostream>
#include "algorithms.h"

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
    return 0;
}
