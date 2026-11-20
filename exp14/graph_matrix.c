#include <stdio.h>

#define MAX_VERTICES 20

static void depth_first(int graph[MAX_VERTICES][MAX_VERTICES],
                        int vertex_count, int vertex, int visited[])
{
    int neighbour;

    visited[vertex] = 1;
    printf("%d ", vertex + 1);
    /* Scan neighbors in vertex-number order for a repeatable traversal. */
    for (neighbour = 0; neighbour < vertex_count; neighbour++) {
        if (graph[vertex][neighbour] && !visited[neighbour]) {
            depth_first(graph, vertex_count, neighbour, visited);
        }
    }
}

static void breadth_first(int graph[MAX_VERTICES][MAX_VERTICES],
                          int vertex_count, int start)
{
    int queue[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    visited[start] = 1;
    printf("BFS: ");
    /* Mark on enqueue so no vertex enters the queue more than once. */
    while (front < rear) {
        int vertex = queue[front++];
        int neighbour;

        printf("%d ", vertex + 1);
        for (neighbour = 0; neighbour < vertex_count; neighbour++) {
            if (graph[vertex][neighbour] && !visited[neighbour]) {
                visited[neighbour] = 1;
                queue[rear++] = neighbour;
            }
        }
    }
    printf("\n");
}

int main(void)
{
    int graph[MAX_VERTICES][MAX_VERTICES] = {{0}};
    int vertex_count;
    int edge_count;
    int edge;
    int start;
    int row;
    int column;
    int visited[MAX_VERTICES] = {0};

    printf("Enter number of vertices (1-%d): ", MAX_VERTICES);
    if (scanf("%d", &vertex_count) != 1 ||
        vertex_count < 1 || vertex_count > MAX_VERTICES) {
        fprintf(stderr, "Invalid number of vertices.\n");
        return 1;
    }
    printf("Enter number of undirected edges (0-%d): ",
           vertex_count * (vertex_count - 1) / 2);
    if (scanf("%d", &edge_count) != 1 || edge_count < 0 ||
        edge_count > vertex_count * (vertex_count - 1) / 2) {
        fprintf(stderr, "Invalid number of edges.\n");
        return 1;
    }
    printf("Enter each edge as two vertex numbers (1-%d):\n", vertex_count);
    for (edge = 0; edge < edge_count; edge++) {
        int first;
        int second;

        if (scanf("%d %d", &first, &second) != 2 ||
            first < 1 || first > vertex_count ||
            second < 1 || second > vertex_count || first == second) {
            fprintf(stderr, "Invalid edge; use two different valid vertices.\n");
            return 1;
        }
        /* An undirected edge appears in both symmetric matrix cells. */
        graph[first - 1][second - 1] = 1;
        graph[second - 1][first - 1] = 1;
    }

    printf("Adjacency matrix:\n");
    for (row = 0; row < vertex_count; row++) {
        for (column = 0; column < vertex_count; column++) {
            printf("%d%s", graph[row][column],
                   column == vertex_count - 1 ? "\n" : " ");
        }
    }
    printf("Enter start vertex for traversals (1-%d): ", vertex_count);
    if (scanf("%d", &start) != 1 || start < 1 || start > vertex_count) {
        fprintf(stderr, "Invalid start vertex.\n");
        return 1;
    }

    breadth_first(graph, vertex_count, start - 1);
    printf("DFS: ");
    depth_first(graph, vertex_count, start - 1, visited);
    printf("\n");
    return 0;
}
