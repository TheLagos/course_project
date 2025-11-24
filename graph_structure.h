#pragma once
#include <vector>

struct Edge {
    int to_id;
    double distance;
};

struct Node {
    int id;
    bool wall;
    std::vector<Edge> edges;
    int x, y;

    Node() = default;
    Node(int _id, bool _wall, int _x, int _y) : id(_id), wall(_wall), x(_x), y(_y) {}
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