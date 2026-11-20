# Experiment 14 – Graph Representation Using an Adjacency Matrix

## 1. Aim
Represent an undirected graph as a matrix and traverse it with BFS and DFS.

## 2. Problem Statement
Read vertices and edges, print the adjacency matrix, and run BFS and DFS from a chosen vertex.

## 3. Theory
A graph contains vertices connected by edges. Matrix[u][v] is 1 when an edge connects them and 0 otherwise. This program represents a small unweighted undirected graph.

## 4. Important Terminology
- **Graph:** A set of vertices and edges representing objects and their relationships.
- **Invariant:** An undirected edge sets both symmetric matrix entries. BFS uses a queue; DFS uses recursion. Both mark visited vertices and print only the component reachable from start.
- **Precondition:** Each endpoint and start label must be within 1..vertex_count.
- **Edge case:** A disconnected graph may have vertices unreachable from the chosen start.
- **Complexity:** Matrix storage and printing are O(V^2). BFS/DFS scan a full row per visited vertex, so O(V^2) here. Traversal auxiliary space is O(V).

## 5. Working Principle
An undirected edge sets both symmetric matrix entries. BFS uses a queue; DFS uses recursion. Both mark visited vertices and print only the component reachable from start.

## 6. Algorithm
1. Validate vertex/edge counts and endpoints. Initialize a zero matrix. Set both cells for each edge. Print the matrix. BFS enqueues start and explores neighbors
2. DFS recursively visits unvisited neighbors.

## 7. Program Explanation
MAX_VERTICES bounds the matrix. Input labels are 1-based and converted to array indexes by subtracting one. Edge endpoints and start are checked before indexing. BFS marks vertices when enqueued to avoid duplicate queue entries. DFS marks on entry. The adjacency matrix causes each visited row to be scanned. Disconnected components not reachable from start are not printed.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `graph_matrix.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `graph_matrix.c`

**Sample input**

```text
4
3
1 2
1 3
2 4
1
```

**Actual program output**

```text
Enter number of vertices (1-20): Enter number of undirected edges (0-6): Enter each edge as two vertex numbers (1-4):
Adjacency matrix:
0 1 1 0
1 0 0 1
1 0 0 0
0 1 0 0
Enter start vertex for traversals (1-4): BFS: 1 2 3 4 
DFS: 1 2 4 3
```

## 10. Dry Run
Edges 1-2, 1-3, 2-4; start=1. BFS visits 1, then 2 and 3, then 4. DFS checks neighbors in numeric order and follows 1->2->4, backtracks, then visits 3.

| Vertex | Neighbors | BFS | DFS path |\n|---:|---|---:|---|\n| 1 | 2,3 | 1 | 1 |\n| 2 | 1,4 | 2 | 2 |\n| 3 | 1 | 3 | 4, then backtrack |\n| 4 | 2 | 4 | 3 after backtracking |

## 11. Time and Space Complexity
Matrix storage and printing are O(V^2). BFS/DFS scan a full row per visited vertex, so O(V^2) here. Traversal auxiliary space is O(V).

## 12. Advantages and Disadvantages
- **Advantages:** Simple representation and O(1) adjacency lookup.
- **Disadvantages:** O(V^2) space is wasteful for sparse graphs; traversal scans absent edges.

## 13. Applications
Small network maps, connectivity examples, and dense graphs.

## 14. Common Errors
Setting only one direction for undirected edges; mixing labels and indexes; forgetting visited; expecting a traversal from one start to cover disconnected vertices.

## 15. POE Viva Questions and Answers
1. **Q: What is a graph?**  
   A: A set of vertices and edges representing objects and their relationships.
2. **Q: What is the aim of Experiment 14?**  
   A: Represent an undirected graph as a matrix and traverse it with BFS and DFS.
3. **Q: What important rule should be preserved?**  
   A: An undirected edge sets both symmetric matrix entries. BFS uses a queue; DFS uses recursion. Both mark visited vertices and print only the component reachable from start.
4. **Q: What precondition must be checked?**  
   A: Each endpoint and start label must be within 1..vertex_count.
5. **Q: How should the important edge case be handled?**  
   A: A disconnected graph may have vertices unreachable from the chosen start.
6. **Q: What is the time and space complexity?**  
   A: Matrix storage and printing are O(V^2). BFS/DFS scan a full row per visited vertex, so O(V^2) here. Traversal auxiliary space is O(V).
7. **Q: State one advantage.**  
   A: Simple representation and O(1) adjacency lookup.
8. **Q: State one limitation.**  
   A: O(V^2) space is wasteful for sparse graphs; traversal scans absent edges.
9. **Q: Give one practical application.**  
   A: Small network maps, connectivity examples, and dense graphs.
10. **Q: Name a common programming error.**  
   A: Setting only one direction for undirected edges; mixing labels and indexes; forgetting visited; expecting a traversal from one start to cover disconnected vertices.
11. **Q: How is an undirected edge represented?**  
   A: Both matrix[u][v] and matrix[v][u] are set.
12. **Q: Which structure does BFS use?**  
   A: A queue, so vertices are processed in discovery order.
13. **Q: Why is visited needed?**  
   A: It avoids repeated processing and stops cycles from revisiting vertices.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Edges 1-2, 1-3, 2-4; start=1. BFS visits 1, then 2 and 3, then 4. DFS checks neighbors in numeric order and follows 1->2->4, backtracks, then visits 3.
2. Test the program's edge case: A disconnected graph may have vertices unreachable from the chosen start.
3. Explain the central rule without looking at the source: An undirected edge sets both symmetric matrix entries. BFS uses a queue; DFS uses recursion. Both mark visited vertices and print only the component reachable from start.
4. Compare this structure or algorithm with its alternative: Adjacency lists use O(V+E) space and suit sparse graphs; matrices suit small or dense graphs.
5. Discuss this program's performance: Matrix storage and printing are O(V^2). BFS/DFS scan a full row per visited vertex, so O(V^2) here. Traversal auxiliary space is O(V).

## 17. Important Exam Points
- The undirected matrix is symmetric
- BFS uses a queue; DFS uses recursion
- One start only reaches its connected component.
