#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <stack>
#include <climits>
#include <cmath>
using namespace std;

struct Edge {
    string to;
    int cost;
};

class Graph {
private:
    unordered_map<string, vector<Edge>> adj;
    unordered_map<string, pair<int, int>> coordinates; // For A* (x, y)

public:
    void addNode(string city, int x, int y) {
        coordinates[city] = {x, y};
        if (adj.find(city) == adj.end())
            adj[city] = {};
    }

    void addEdge(string from, string to, int cost, bool bidirectional = true) {
        adj[from].push_back({to, cost});
        if (bidirectional)
            adj[to].push_back({from, cost});
    }

    void dijkstra(string start, string end) {
        unordered_map<string, int> dist;
        unordered_map<string, string> parent;
        set<pair<int, string>> pq;

        for (auto& pair : adj) dist[pair.first] = INT_MAX;

        dist[start] = 0;
        pq.insert({0, start});

        while (!pq.empty()) {
            auto [d, u] = *pq.begin();
            pq.erase(pq.begin());

            for (auto& edge : adj[u]) {
                int newDist = d + edge.cost;
                if (newDist < dist[edge.to]) {
                    pq.erase({dist[edge.to], edge.to});
                    dist[edge.to] = newDist;
                    parent[edge.to] = u;
                    pq.insert({newDist, edge.to});
                }
            }
        }

        if (dist[end] == INT_MAX) {
            cout << "No path found.\n";
            return;
        }

        cout << "Shortest Distance: " << dist[end] << "\nPath: ";
        printPath(parent, start, end);
    }

    void aStar(string start, string end) {
        auto heuristic = [&](string a, string b) {
            auto [x1, y1] = coordinates[a];
            auto [x2, y2] = coordinates[b];
            return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
        };

        unordered_map<string, double> gScore, fScore;
        unordered_map<string, string> parent;
        set<pair<double, string>> openSet;

        for (auto& node : adj) {
            gScore[node.first] = fScore[node.first] = DBL_MAX;
        }

        gScore[start] = 0;
        fScore[start] = heuristic(start, end);
        openSet.insert({fScore[start], start});

        while (!openSet.empty()) {
            auto [f, current] = *openSet.begin();
            openSet.erase(openSet.begin());

            if (current == end) {
                cout << "Estimated Distance (A*): " << gScore[end] << "\nPath: ";
                printPath(parent, start, end);
                return;
            }

            for (auto& edge : adj[current]) {
                double tentative = gScore[current] + edge.cost;
                if (tentative < gScore[edge.to]) {
                    parent[edge.to] = current;
                    gScore[edge.to] = tentative;
                    fScore[edge.to] = tentative + heuristic(edge.to, end);
                    openSet.insert({fScore[edge.to], edge.to});
                }
            }
        }

        cout << "No path found.\n";
    }

    void printPath(unordered_map<string, string>& parent, string start, string end) {
        stack<string> path;
        string current = end;
        while (current != start) {
            path.push(current);
            current = parent[current];
        }
        path.push(start);

        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << "\n";
    }
};
