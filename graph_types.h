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
    int visited_nodes = 0;
    long long duration = 0;
    std::vector<int> path;

    Result() = default;
    Result(bool f, double total, int visited, long long dur, std::vector<int>&& p) : found(f), total_distance(total), visited_nodes(visited), duration(dur), path(p) {}
};