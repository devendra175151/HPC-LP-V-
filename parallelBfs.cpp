#include <iostream>
#include <queue>
#include <vector>
#include <omp.h>

void parallelBFS(std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int startNode) {
    std::queue<int> queue;
    queue.push(startNode);
    visited[startNode] = true;

    while (!queue.empty()) {
        int queueSize = queue.size();

        #pragma omp parallel for
        for (int i = 0; i < queueSize; i++) {
            int node;
            #pragma omp critical
            {
                node = queue.front();
                queue.pop();
            }

            // Process node
            std::cout << "Visited node: " << node << std::endl;

            // Explore neighbors
            for (int neighbor = 0; neighbor < graph[node].size(); neighbor++) {
                if (graph[node][neighbor] == 1 && !visited[neighbor]) {
                    #pragma omp critical
                    {
                        visited[neighbor] = true;
                        queue.push(neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };
    std::vector<bool> visited(graph.size(), false);

    parallelBFS(graph, visited, 0);

    return 0;
}
