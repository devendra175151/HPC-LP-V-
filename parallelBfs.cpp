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

/*Explanation : 

First, we have a function called parallelBFS that takes the graph, a list of visited nodes, and the starting node as input. This function performs the breadth-first search algorithm in parallel using OpenMP.

Inside the function, we have a queue that stores the nodes to be processed. We start by adding the starting node to the queue and marking it as visited.

Next, we enter a loop that continues until the queue is empty. This loop represents each level of the BFS traversal.

Within this loop, we divide the work among multiple threads using OpenMP. Each thread processes a subset of nodes from the current level simultaneously.

We use the #pragma omp parallel for directive to indicate that the following loop should be executed in parallel. It automatically distributes the work among the available threads.

Inside the loop, we retrieve a node from the queue in a thread-safe manner. We use the #pragma omp critical directive to ensure that only one thread accesses the queue at a time. This prevents conflicts and data corruption.

Once a node is retrieved, we process it by printing a message indicating that the node has been visited.

Then, we explore the neighbors of the current node. If a neighbor is connected to the current node and has not been visited before, we mark it as visited and add it to the queue for further exploration. Again, we use the #pragma omp critical directive to ensure that the queue is accessed safely by only one thread at a time.

The process continues until all nodes have been visited.

Finally, in the main function, we create a graph represented as an adjacency matrix and a list of visited nodes. We call the parallelBFS function, passing in the graph, visited list, and the starting node index.

When the program runs, it performs parallel breadth-first search on the graph, printing the visited nodes to the console. */
