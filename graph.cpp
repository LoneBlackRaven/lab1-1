#include "graph.h"
#include <queue>
#include <limits>
#include <algorithm>

void Graph::addEdge(int from, int to, int pipeId, double capacity, bool bidirectional) {
    Edge* edge = new Edge(from, to, pipeId, capacity);
    Edge* reverseEdge = new Edge(to, from, pipeId, 0.0);

    edge->reverse = reverseEdge;
    reverseEdge->reverse = edge;

    adj[from].push_back(edge);
    adj[to].push_back(reverseEdge);

    if (bidirectional) {
        Edge* backEdge = new Edge(to, from, pipeId, capacity);
        Edge* backReverse = new Edge(from, to, pipeId, 0.0);

        backEdge->reverse = backReverse;
        backReverse->reverse = backEdge;

        adj[to].push_back(backEdge);
        adj[from].push_back(backReverse);
    }
}

bool Graph::bfs(int source, int sink, std::map<int, Edge*>& parent) {
    std::queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (Edge* edge : adj[current]) {
            if (parent.find(edge->to) == parent.end() &&
                edge->residualCapacity() > 1e-9) {
                parent[edge->to] = edge;
                if (edge->to == sink) {
                    return true;
                }
                q.push(edge->to);
            }
        }
    }

    return false;
}

double Graph::maxFlow(int source, int sink) {
    double totalFlow = 0.0;

    while (true) {
        std::map<int, Edge*> parent;
        if (!bfs(source, sink, parent)) {
            break;
        }

        // Находим минимальную остаточную пропускную способность
        double pathFlow = std::numeric_limits<double>::infinity();
        for (int v = sink; v != source; v = parent[v]->from) {
            pathFlow = std::min(pathFlow, parent[v]->residualCapacity());
        }

        // Обновляем потоки вдоль пути
        for (int v = sink; v != source; v = parent[v]->from) {
            parent[v]->flow += pathFlow;
            parent[v]->reverse->flow -= pathFlow;
        }

        totalFlow += pathFlow;
    }

    return totalFlow;
}

std::vector<double> Graph::dijkstra(int start) {
    std::map<int, double> distance;
    std::priority_queue<std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>> pq;

    for (const auto& node : adj) {
        distance[node.first] = std::numeric_limits<double>::infinity();
    }
    distance[start] = 0.0;
    pq.push({ 0.0, start });

    while (!pq.empty()) {
        double dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (dist > distance[current]) continue;

        for (Edge* edge : adj[current]) {
            // Используем длину как вес (capacity здесь не используется для веса)
            double weight = 1.0; // Базовый вес, можно настроить
            double newDist = dist + weight;

            if (newDist < distance[edge->to]) {
                distance[edge->to] = newDist;
                pq.push({ newDist, edge->to });
            }
        }
    }

    // Конвертируем в вектор
    std::vector<double> result;
    for (const auto& d : distance) {
        result.push_back(d.second);
    }
    return result;
}

std::vector<int> Graph::shortestPath(int start, int end) {
    std::map<int, double> distance;
    std::map<int, int> parent;
    std::priority_queue<std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>> pq;

    for (const auto& node : adj) {
        distance[node.first] = std::numeric_limits<double>::infinity();
        parent[node.first] = -1;
    }

    distance[start] = 0.0;
    pq.push({ 0.0, start });

    while (!pq.empty()) {
        double dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        if (dist > distance[current]) continue;
        if (current == end) break;

        for (Edge* edge : adj[current]) {
            // Используем длину как вес
            double weight = 1.0; // Базовый вес
            double newDist = dist + weight;

            if (newDist < distance[edge->to]) {
                distance[edge->to] = newDist;
                parent[edge->to] = current;
                pq.push({ newDist, edge->to });
            }
        }
    }

    // Восстанавливаем путь
    std::vector<int> path;
    if (distance[end] < std::numeric_limits<double>::infinity()) {
        for (int v = end; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}

void Graph::clear() {
    for (auto& node : adj) {
        for (Edge* edge : node.second) {
            delete edge;
        }
    }
    adj.clear();
}