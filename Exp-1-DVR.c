#include <stdio.h>
#include <limits.h>
#define MAX_NODES 50
#define INF INT_MAX

struct RouteEntry {
    int distance;
    int nextHop;
};

struct Network {
    int nodes;
    int graph[MAX_NODES][MAX_NODES];
    struct RouteEntry routingTable[MAX_NODES][MAX_NODES];
};

void initNetwork(struct Network* net, int nodes) {
    net->nodes = nodes;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            net->graph[i][j] = (i == j) ? 0 : INF;
            net->routingTable[i][j].distance = INF;
            net->routingTable[i][j].nextHop = -1;
        }
    }
}

void printRoutingTable(struct Network* net, int node) {
    printf("\nRouting Table for N%d\n", node + 1);
    printf("Destination\tNext Hop\tDistance\n");
    for (int dest = 0; dest < net->nodes; dest++) {
        printf("N%d\t\t", dest + 1);
        if (dest == node) {
            printf("self\t\t0\n");
        } else if (net->routingTable[node][dest].nextHop == -1) {
            printf("-\t\tINF\n");
        } else {
            printf("N%d\t\t%d\n", net->routingTable[node][dest].nextHop + 1, net->routingTable[node][dest].distance);
        }
    }
}

void calculateRoutingTables(struct Network* net) {
    for (int i = 0; i < net->nodes; i++) {
        for (int j = 0; j < net->nodes; j++) {
            if (i == j || net->graph[i][j] != INF) {
                net->routingTable[i][j].distance = net->graph[i][j];
                net->routingTable[i][j].nextHop = (i == j) ? i : j;
            }
        }
    }

    for (int k = 0; k < net->nodes; k++) {
        for (int i = 0; i < net->nodes; i++) {
            for (int j = 0; j < net->nodes; j++) {
                if (net->routingTable[i][k].distance != INF && net->routingTable[k][j].distance != INF) {
                    int newDist = net->routingTable[i][k].distance + net->routingTable[k][j].distance;
                    if (newDist < net->routingTable[i][j].distance) {
                        net->routingTable[i][j].distance = newDist;
                        net->routingTable[i][j].nextHop = net->routingTable[i][k].nextHop;
                    }
                }
            }
        }
    }
}

int main() {
    struct Network net;
    int nodes;

    printf("Enter number of nodes (1-%d): ", MAX_NODES);
    scanf("%d", &nodes);

    initNetwork(&net, nodes);

    printf("\nEnter the distance matrix (-1 for no connection):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (i != j) {
                printf("Distance from N%d to N%d: ", i + 1, j + 1);
                int distance;
                scanf("%d", &distance);
                net.graph[i][j] = (distance == -1) ? INF : distance;
            }
        }
    }

    calculateRoutingTables(&net);

    for (int i = 0; i < nodes; i++) {
        printRoutingTable(&net, i);
    }

    return 0;
}
