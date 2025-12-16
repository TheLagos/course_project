#pragma once
#include <vector>

struct Edge {
    int to_id = -1;
    double distance = 0;
};

struct Node {
    int id = -1;
    bool wall = false;
    std::vector<Edge> edges;
    int x = 0, y = 0;

    Node() = default;
    Node(int _id, bool _wall, int _x, int _y) : id(_id), wall(_wall), x(_x), y(_y) {}
};

struct Result {
    bool found = false;
    double total_distance = 0;
    long long duration = 0;
    std::vector<int> path;
    std::vector<int> visited_nodes;

    Result() = default;
    Result(bool f, double total, long long dur, std::vector<int>&& p, std::vector<int>&& visited) : found(f), total_distance(total), duration(dur), path(p), visited_nodes(visited) {}
};
