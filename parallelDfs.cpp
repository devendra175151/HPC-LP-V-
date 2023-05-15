#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

void parallelDFS(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, int startNode) {
    std::stack<int> stack;
    stack.push(startNode);
    visited[startNode] = true;

    while (!stack.empty()) {
        int node = stack.top();
        stack.pop();

        // Process node
        std::cout << "Visited node: " << node << std::endl;

        #pragma omp parallel
        #pragma omp single nowait
        {
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;

                    #pragma omp task
                    {
                        stack.push(neighbor);
                        parallelDFS(graph, visited, neighbor);
                    }
                }
            }
        }
    }
}

int main() {
    std::vector<std::vector<int>> graph = {
        {1, 2},
        {0, 3, 4},
        {0},
        {1},
        {1}
    };
    std::vector<bool> visited(graph.size(), false);

    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS(graph, visited, 0);
        }
    }

    return 0;
}
/*
Explanation : 
In this code, we make use of OpenMP's task-based parallelism. The #pragma omp parallel directive creates a parallel region, and the #pragma omp single directive ensures that only one thread executes the following block of code.

Within that block, we iterate through the neighbors of the current node in parallel using the #pragma omp task directive. Each task pushes the unvisited neighbor onto the stack and recursively calls parallelDFS on that neighbor.

The nowait clause is used to allow tasks to be created in parallel without waiting for their completion.

Note that the code creates tasks dynamically as new unvisited neighbors are discovered, allowing for some level of parallelism in the DFS traversal. However, the effectiveness of parallelism in this case is limited due to the nature of the DFS algorithm and its recursive nature.

It's important to note that parallelizing DFS efficiently is a complex task, and alternative parallel graph traversal algorithms like parallel breadth-first search (BFS) or parallel algorithms that use work-stealing techniques are often preferred for achieving better parallelism.
*/