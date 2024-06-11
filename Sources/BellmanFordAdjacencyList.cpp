#include "../Headers/BellmanFordAdjacencyList.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include <chrono>

BellmanFordAdjacencyList::BellmanFordAdjacencyList(const AdjacencyList& adjacencyList)
        : adjList(adjacencyList) {}

bool BellmanFordAdjacencyList::findShortestPath(int startVertex, int endVertex) {
//    auto startTime = std::chrono::high_resolution_clock::now();

    int vertices = adjList.getVertices();
    dist.resize(vertices, std::numeric_limits<int>::max());
    prev.resize(vertices, -1);

    dist[startVertex] = 0;

    for (int i = 1; i < vertices; ++i) {
        bool updated = false;
        for (int u = 0; u < vertices; ++u) {
            for (const auto& edge : adjList.getAdjList()[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    prev[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) {
            break;
        }
    }

    for (int u = 0; u < vertices; ++u) {
        for (const auto& edge : adjList.getAdjList()[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                std::cout << "Negative weight cycle detected!" << std::endl;
                return false;
            }
        }
    }

//    auto endTime = std::chrono::high_resolution_clock::now();
//    std::chrono::duration<double, std::milli> elapsed = endTime - startTime; // Changed to milliseconds

    // Aktualizacja listy sąsiedztwa
    const_cast<AdjacencyList&>(adjList).updateListForBellmanFord(dist, prev);

    if (dist[endVertex] == std::numeric_limits<int>::max()) {
        std::cout << "No path from " << startVertex << " to " << endVertex << std::endl;
        return false;
    }

    std::vector<int> path;
    for (int at = endVertex; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    std::cout << "Shortest path from " << startVertex << " to " << endVertex << ": ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) std::cout << " -> ";
        std::cout << path[i];
    }
    std::cout << " with total weight " << dist[endVertex] << std::endl;
//    std::cout << "Elapsed time: " << elapsed.count() << " ms" << std::endl; // Changed output to milliseconds

    return true;
}

