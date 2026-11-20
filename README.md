# Data Structures Using C Laboratory

**Subject:** Data Structures Using C Laboratory  
**Course code:** PCCP201  
**Semester:** III

## Course Overview
This repository contains practical programs and beginner-friendly study guides for the Semester III Data Structures laboratory. The experiments progress from arrays and algorithms to stacks, queues, linked lists, trees, and graphs. Each experiment has independent C source file(s), a detailed guide, and captured sample executions.

## Experiments
1. [Experiment 01 – Array Operations](exp01/README.md)
2. [Experiment 02 – Searching: Linear and Binary Search](exp02/README.md)
3. [Experiment 03 – Sorting: Bubble, Selection, and Insertion Sort](exp03/README.md)
4. [Experiment 04 – Stack Using an Array](exp04/README.md)
5. [Experiment 05 – Queue Using a Linear Array](exp05/README.md)
6. [Experiment 06 – Circular Queue Using an Array](exp06/README.md)
7. [Experiment 07 – Implement a Stack Using Queues](exp07/README.md)
8. [Experiment 08 – Singly Linked List: Insertion and Deletion](exp08/README.md)
9. [Experiment 09 – Singly Linked List: Traversal and Searching](exp09/README.md)
10. [Experiment 10 – Doubly Linked List](exp10/README.md)
11. [Experiment 11 – Circular Singly Linked List: Insertion and Deletion](exp11/README.md)
12. [Experiment 12 – Circular Singly Linked List: Traversal and Searching](exp12/README.md)
13. [Experiment 13 – Binary Search Tree](exp13/README.md)
14. [Experiment 14 – Graph Representation Using an Adjacency Matrix](exp14/README.md)

Supplementary case-study topics: [Case Studies](case_studies.md).

## Folder Navigation
Each `expNN` folder contains its guide (`README.md`), sample runs (`output.md`), and the corresponding `.c` file(s). Compile one source file at a time because each independent program has its own `main()`.

## Compile and Run with GCC
From the repository root, for example:

```sh
gcc -std=c99 -Wall -Wextra -Wpedantic exp04/stack_array.c -o stack_array
./stack_array
```

In PowerShell:

```powershell
gcc -std=c99 -Wall -Wextra -Wpedantic .\exp04\stack_array.c -o .\stack_array.exe
& .\stack_array.exe
```

## Recommended Learning Order
Follow Experiments 1–3 for arrays and algorithms, 4–7 for stacks and queues, 8–12 for linked lists, then 13 for trees and 14 for graphs.

## POE Preparation Guidance
For each experiment, explain its aim and invariant, trace a small input by hand, identify boundary cases, and state time and space complexity. Compile and run programs yourself and practice explaining each pointer or index update aloud. Pay special attention to overflow/underflow, empty and single-node lists, sorted-input requirements, and circular-list termination.
