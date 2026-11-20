# Experiment 12 – Circular Singly Linked List: Traversal and Searching

## 1. Aim
Traverse a complete circular list once and search without an infinite loop.

## 2. Problem Statement
Create a circular list, display one full cycle, and find a key's position.

## 3. Theory
A circular list has no NULL at its logical end. Traversal must stop when it returns to the saved head.

## 4. Important Terminology
- **Circular Traversal:** Visiting each node once and stopping when the pointer returns to the start.
- **Invariant:** Save head=tail->next. A do-while processes the starting node, advances once, and stops when current==head.
- **Precondition:** The list must be non-empty before accessing tail->next.
- **Edge case:** An empty list is tail=NULL and has no node to visit or search.
- **Complexity:** Traversal/search O(n) worst; search O(1) best. Appending with tail is O(1) per node. Space O(n).

## 5. Working Principle
Save head=tail->next. A do-while processes the starting node, advances once, and stops when current==head.

## 6. Algorithm
1. Read count and append nodes. Handle empty list. Traverse one cycle from head. Search similarly, returning on a match or not found after returning to head. Free safely.

## 7. Program Explanation
Node stores data and next; tail identifies the last node. append inserts after tail in O(1). traverse and search save the head and use do-while loops to process one circuit. search counts 1-based positions. free_list breaks the tail link before freeing nodes.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `circular_list_traversal_search.c`

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static int append(Node **tail, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    if (*tail == NULL) {
        node->next = node;
    } else {
        node->next = (*tail)->next;
        (*tail)->next = node;
    }
    *tail = node;
    return 1;
}

static void traverse(const Node *tail)
{
    const Node *head;
    const Node *current;

    if (tail == NULL) {
        printf("Circular list is empty.\n");
        return;
    }
    head = tail->next;
    current = head;
    printf("Traversal: ");
    /* A circular list ends this traversal by returning to its head. */
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);
    printf("(back to head)\n");
}

static int search(const Node *tail, int key)
{
    const Node *head;
    const Node *current;
    int position = 1;

    if (tail == NULL) {
        return 0;
    }
    head = tail->next;
    current = head;
    do {
        if (current->data == key) {
            return position;
        }
        current = current->next;
        position++;
    } while (current != head);
    return 0;
}

static void free_list(Node **tail)
{
    Node *head;

    if (*tail == NULL) {
        return;
    }
    head = (*tail)->next;
    /* Break the cycle before using the ordinary NULL-terminated cleanup loop. */
    (*tail)->next = NULL;
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
    *tail = NULL;
}

int main(void)
{
    Node *tail = NULL;
    int count;
    int index;
    int value;
    int position;

    printf("Enter number of nodes (0-100): ");
    if (scanf("%d", &count) != 1 || count < 0 || count > 100) {
        fprintf(stderr, "Invalid node count.\n");
        return 1;
    }
    for (index = 0; index < count; index++) {
        printf("Value for node %d: ", index + 1);
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid node value.\n");
            free_list(&tail);
            return 1;
        }
        if (!append(&tail, value)) {
            fprintf(stderr, "Memory allocation failed.\n");
            free_list(&tail);
            return 1;
        }
    }
    traverse(tail);

    printf("Enter value to search: ");
    if (scanf("%d", &value) != 1) {
        fprintf(stderr, "Invalid search value.\n");
        free_list(&tail);
        return 1;
    }
    position = search(tail, value);
    if (position == 0) {
        printf("%d was not found.\n", value);
    } else {
        printf("%d found at position %d.\n", value, position);
    }

    free_list(&tail);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `circular_list_traversal_search.c`

**Sample input**

```text
3
10
20
30
20
```

**Actual program output**

```text
Enter number of nodes (0-100): Value for node 1: Value for node 2: Value for node 3: Traversal: 10 -> 20 -> 30 -> (back to head)
Enter value to search: 20 found at position 2.
```

## 10. Dry Run
For 10->20->30->back to 10, key 20: compare 10 at position 1, advance, compare 20 at position 2 and stop.

| Visit | Value | Key 20? | Action |\n|---:|---:|---|---|\n| 1 | 10 | No | Advance |\n| 2 | 20 | Yes | Found at 2 |

## 11. Time and Space Complexity
Traversal/search O(n) worst; search O(1) best. Appending with tail is O(1) per node. Space O(n).

## 12. Advantages and Disadvantages
- **Advantages:** Append is constant-time with a tail pointer; cyclic order is represented directly.
- **Disadvantages:** There is no NULL stop marker; termination conditions require care.

## 13. Applications
Rotating work lists and cyclic navigation.

## 14. Common Errors
Using current!=NULL; not saving the original head; dereferencing tail when empty; missing the one-node case.

## 15. POE Viva Questions and Answers
1. **Q: What is a circular traversal?**  
   A: Visiting each node once and stopping when the pointer returns to the start.
2. **Q: What is the aim of Experiment 12?**  
   A: Traverse a complete circular list once and search without an infinite loop.
3. **Q: What important rule should be preserved?**  
   A: Save head=tail->next. A do-while processes the starting node, advances once, and stops when current==head.
4. **Q: What precondition must be checked?**  
   A: The list must be non-empty before accessing tail->next.
5. **Q: How should the important edge case be handled?**  
   A: An empty list is tail=NULL and has no node to visit or search.
6. **Q: What is the time and space complexity?**  
   A: Traversal/search O(n) worst; search O(1) best. Appending with tail is O(1) per node. Space O(n).
7. **Q: State one advantage.**  
   A: Append is constant-time with a tail pointer; cyclic order is represented directly.
8. **Q: State one limitation.**  
   A: There is no NULL stop marker; termination conditions require care.
9. **Q: Give one practical application.**  
   A: Rotating work lists and cyclic navigation.
10. **Q: Name a common programming error.**  
   A: Using current!=NULL; not saving the original head; dereferencing tail when empty; missing the one-node case.
11. **Q: Why is do-while useful here?**  
   A: It visits the starting node before testing whether traversal returned to the start.
12. **Q: What happens if the key is absent?**  
   A: Search visits one full cycle and then reports not found.
13. **Q: How is an empty circular list represented?**  
   A: tail is NULL.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: For 10->20->30->back to 10, key 20: compare 10 at position 1, advance, compare 20 at position 2 and stop.
2. Test the program's edge case: An empty list is tail=NULL and has no node to visit or search.
3. Explain the central rule without looking at the source: Save head=tail->next. A do-while processes the starting node, advances once, and stops when current==head.
4. Compare this structure or algorithm with its alternative: Linear traversal stops at NULL; circular traversal stops at the original head.
5. Discuss this program's performance: Traversal/search O(n) worst; search O(1) best. Appending with tail is O(1) per node. Space O(n).

## 17. Important Exam Points
- Save head
- Stop on return to head
- Check empty before accessing tail->next.
