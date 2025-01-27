#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 10  // Max nodes, can adjust as needed

// Struct to represent the graph
typedef struct {
    int cost[MAX_NODES][MAX_NODES];  // Adjacency matrix
    int visited[MAX_NODES];           // Visited nodes in Dijkstra's algorithm
    int distance[MAX_NODES];          // Distance from source to node
    int parent[MAX_NODES];            // Parent nodes for path reconstruction
} Network;

// Function to initialize the network with infinity distances
void initializeNetwork(Network* net, int nodes) {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (i == j) {
                net->cost[i][j] = 0; // Distance to self is 0
            } else {
                net->cost[i][j] = INT_MAX; // No connection initially
            }
        }
        net->visited[i] = 0;
        net->distance[i] = INT_MAX;
        net->parent[i] = -1;
    }
}

// Function to add an edge (link) between nodes
void addLink(Network* net, int src, int dest, int cost) {
    net->cost[src][dest] = cost;
    net->cost[dest][src] = cost; // For undirected graph
}

// Dijkstra's Algorithm to find the shortest path
void dijkstra(Network* net, int source, int nodes) {
    net->distance[source] = 0;

    for (int i = 0; i < nodes; i++) {
        int minDist = INT_MAX;
        int u = -1;

        // Find the unvisited node with the smallest distance
        for (int j = 0; j < nodes; j++) {
            if (!net->visited[j] && net->distance[j] < minDist) {
                minDist = net->distance[j];
                u = j;
            }
        }

        if (u == -1) {
            break; // No reachable nodes left
        }

        // Mark the node as visited
        net->visited[u] = 1;

        // Update the distances of adjacent nodes
        for (int v = 0; v < nodes; v++) {
            if (!net->visited[v] && net->cost[u][v] != INT_MAX) {
                int alt = net->distance[u] + net->cost[u][v];
                if (alt < net->distance[v]) {
                    net->distance[v] = alt;
                    net->parent[v] = u;
                }
            }
        }
    }
}

// Function to print the shortest path from source to destination
void printShortestPath(Network* net, int dest) {
    if (net->parent[dest] != -1) {
        printShortestPath(net, net->parent[dest]);
        printf(" -> ");
    }
    printf("%d", dest);
}

int main() {
    int nodes, edges;
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    Network net;
    initializeNetwork(&net, nodes);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    // Input edges and their costs
    for (int i = 0; i < edges; i++) {
        int src, dest, cost;
        printf("Enter edge %d (source destination cost): ", i + 1);
        scanf("%d %d %d", &src, &dest, &cost);

        // Make sure that the nodes are valid
        if (src >= 0 && src < nodes && dest >= 0 && dest < nodes) {
            addLink(&net, src, dest, cost);
        } else {
            printf("Invalid node indices. Please enter again.\n");
            i--;  // Decrement to repeat this iteration
        }
    }

    int source;
    printf("Enter source node for Dijkstra's algorithm: ");
    scanf("%d", &source);

    // Ensure the source node is valid
    if (source < 0 || source >= nodes) {
        printf("Invalid source node.\n");
        return -1;
    }

    // Run Dijkstra's algorithm from the source node
    dijkstra(&net, source, nodes);

    // Print the shortest path from source to every other node
    for (int i = 0; i < nodes; i++) {
        if (i != source) {
            printf("Shortest path from %d to %d: ", source, i);
            if (net.distance[i] == INT_MAX) {
                printf("No path\n");
            } else {
                printf("Distance: %d\n", net.distance[i]);
                printf("Path: ");
                printShortestPath(&net, i);
                printf("\n\n");
            }
        }
    }

    return 0;
}
