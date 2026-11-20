# Supplementary Data-Structures Case Studies

These syllabus topics supplement the 14 experiments and do not create an additional experiment folder.

## Garbage Collection
Dynamic structures allocate nodes while a program runs. C's `malloc` reserves memory and the program must call `free` when that memory is no longer needed. An allocated node that becomes unreachable without being freed causes a memory leak. A tracing garbage collector reclaims unreachable objects automatically in some languages and runtimes; C has no built-in tracing collector. The linked-list examples explicitly free removed nodes and clean up remaining nodes at exit. See [Experiment 8](exp08/README.md), [Experiment 10](exp10/README.md), [Experiment 11](exp11/README.md), and [Experiment 12](exp12/README.md).

**POE point:** Save any needed `next` pointer before freeing a node; never dereference a node after `free`.

## Priority Queue in Bandwidth Management
A priority queue removes the highest- or lowest-priority item first, unlike a normal FIFO queue. A router may prioritize latency-sensitive voice packets over bulk transfers, while using fairness or aging so lower-priority traffic is not starved. A binary heap commonly provides insertion and removal in O(log n). Compare with the FIFO queues in [Experiment 5](exp05/README.md) and [Experiment 6](exp06/README.md).

**Design questions:** Define priority ties, capacity, and starvation prevention.

## Null-Terminated or Cyclic Node
In a linear singly linked list, the final `next` is `NULL`. In a circular list, the final node points back to the first, so traversal stops when it returns to the saved head, not at `NULL`. Confusing these rules causes early termination or an infinite loop. Compare [Experiment 8](exp08/README.md) with [Experiment 11](exp11/README.md) and [Experiment 12](exp12/README.md).

## Sparse Matrix in Social Networks and Maps
An adjacency matrix uses O(V^2) space even when most entries are zero. Social networks and road maps are often sparse: each person or location connects to relatively few others. An adjacency list stores only neighbors and uses O(V+E) space. The matrix in [Experiment 14](exp14/README.md) makes adjacency checks simple and suits small or dense graphs; lists are usually better for large sparse graphs.

**Example:** For 1,000 vertices with about 10 neighbors each, a matrix has one million cells, while adjacency lists store the vertices and about 10,000 links (an undirected edge is stored at both endpoints).
