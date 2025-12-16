#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>
#include "pipe.h"
#include "cs.h"
#include "connection.h"

struct Edge {
    int from;
    int to;
    int pipeId;
    double capacity;
    double flow;
    Edge* reverse;

    Edge(int f, int t, int pId, double cap)
        : from(f), to(t), pipeId(pId), capacity(cap), flow(0), reverse(nullptr) {
    }

    double residualCapacity() const {
        return capacity - flow;
    }
};

class Graph {
private:
    std::map<int, std::vector<Edge*>> adj;
    std::map<int, Edge*> edges;

public:
    void addEdge(int from, int to, int pipeId, double capacity, bool bidirectional = false);
    double maxFlow(int source, int sink);
    std::vector<int> shortestPath(int start, int end);
    void clear();

private:
    bool bfs(int source, int sink, std::map<int, Edge*>& parent);
    std::vector<double> dijkstra(int start);
};

#endif // GRAPH_H