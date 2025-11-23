#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <cmath>

struct Edge {
    int to_id;
    double distance;
};

struct Node {
    int id;
    std::vector<Edge> edges;
    int x, y;
};

struct Result {
    bool found;
    double total_distance;
    int visited_nodes;
    long long duration;
    std::vector<int> path;

    Result() : found(false), total_distance(0), visited_nodes(0), duration(0) {}
    Result(bool f, double total, int visited, long long dur, std::vector<int>&& p) : found(f), total_distance(total), visited_nodes(visited), duration(dur), path(p) {}
};

Result dijkstra(int start_id, int end_id, const std::vector<Node>& graph) {
    using type = std::pair<double, int>;
    constexpr double INF = std::numeric_limits<double>::infinity();
    int visited_nodes = 0;

    std::vector<double> distances(graph.size(), INF);
    std::vector<int> parents(graph.size(), -1);
    std::priority_queue<type, std::vector<type>, std::greater <type>> pq;

    distances[start_id] = 0;
    pq.emplace(0, start_id);

    const auto start(std::chrono::steady_clock::now());
    while (!pq.empty()) {
        double current_distance = pq.top().first;
        int current_id = pq.top().second;

        ++visited_nodes;
        pq.pop();

        if (current_distance > distances[current_id]) {
            continue;
        }

        if (current_id == end_id) {
            break;
        }

        for (const Edge& edge : graph[current_id].edges) {
            double new_distance = distances[current_id] + edge.distance;

            if (new_distance < distances[edge.to_id]) {
                distances[edge.to_id] = new_distance;
                pq.emplace(new_distance, edge.to_id);
                parents[edge.to_id] = current_id;
            }
        }
    }
    const auto finish(std::chrono::steady_clock::now());
    long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    if (distances[end_id] == INF) {
        return Result();
    }

    std::vector<int> path;
    for (int current = end_id; current != -1; current = parents[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());

    return { true, distances[end_id], visited_nodes, duration, std::move(path)};
}

double heuristic(const Node& left, const Node& right) {
    double dx = left.x - right.x;
    double dy = left.y - right.y;
    return std::sqrt(dx * dx + dy * dy);
}

Result a_star(int start_id, int end_id, const std::vector<Node>& graph) {
    using type = std::pair<double, int>;
    constexpr double INF = std::numeric_limits<double>::infinity();
    int visited_nodes = 0;

    std::vector<double> g_distances(graph.size(), INF);
    std::vector<int> parents(graph.size(), -1);
    std::priority_queue<type, std::vector<type>, std::greater <type>> pq;

    g_distances[start_id] = 0;
    pq.emplace(heuristic(graph[start_id], graph[end_id]), start_id);

    const auto start(std::chrono::steady_clock::now());
    while (!pq.empty()) {
        double current_f = pq.top().first;
        int current_id = pq.top().second;

        ++visited_nodes;
        pq.pop();

        if (current_f > g_distances[current_id] + heuristic(graph[current_id], graph[end_id]) + 0.00001) {
            continue;
        }

        if (current_id == end_id) {
            break;
        }

        for (const Edge& edge : graph[current_id].edges) {
            double new_g = g_distances[current_id] + edge.distance;

            if (new_g < g_distances[edge.to_id]) {
                g_distances[edge.to_id] = new_g;
                pq.emplace(new_g + heuristic(graph[edge.to_id], graph[end_id]), edge.to_id);
                parents[edge.to_id] = current_id;
            }
        }
    }
    const auto finish(std::chrono::steady_clock::now());
    long long duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    if (g_distances[end_id] == INF) {
        return Result();
    }

    std::vector<int> path;
    for (int current = end_id; current != -1; current = parents[current]) {
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());

    return { true, g_distances[end_id], visited_nodes, duration, std::move(path) };
}

int main()
{
    std::cout << "Hello World!\n";
}
