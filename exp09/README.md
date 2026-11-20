# Experiment 9 – Singly Linked List: Traversal and Searching

## 1. Aim
Create a singly linked list, traverse all nodes, and search for a key.

## 2. Problem Statement
Read node values, display the linked sequence, and report a key's 1-based position.

## 3. Theory
Traversal follows next pointers until NULL. Search compares each node's data and stops at the first match or the list end.

## 4. Important Terminology
- **Traversal:** Visiting nodes in order by following their links.
- **Invariant:** Use a temporary current pointer so head remains available. Increment the position as current advances; reaching NULL means absent.
- **Precondition:** A valid head pointer; NULL is a valid empty list.
- **Edge case:** Search on empty returns not found without dereferencing any node.
- **Complexity:** Traversal/search O(n) worst and O(1) best for a first-node match. Appending with a tail scan makes building n nodes O(n^2). Space is O(n).

## 5. Working Principle
Use a temporary current pointer so head remains available. Increment the position as current advances; reaching NULL means absent.

## 6. Algorithm
1. Read a bounded count
2. Append each allocated node
3. Traverse and print
4. Read key
5. Advance current while comparing
6. Report first position or not found
7. Free all nodes.

## 7. Program Explanation
Node contains data and next. append allocates and initializes nodes, checking malloc. display uses a local pointer so it does not change head. search counts positions from one and returns zero for not found. free_list saves the next pointer before freeing each node.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `singly_list_traversal_search.c`

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static int append(Node **head, int value)
{
    Node *node = malloc(sizeof(*node));
    Node *current;

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    node->next = NULL;
    if (*head == NULL) {
        *head = node;
        return 1;
    }
    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 1;
}

static void display(const Node *head)
{
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    /* Advance a local pointer so the caller's head remains unchanged. */
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        printf("%s", head == NULL ? " -> NULL\n" : " -> ");
    }
}

static int search(const Node *head, int key)
{
    int position = 1;

    while (head != NULL) {
        if (head->data == key) {
            return position;
        }
        head = head->next;
        position++;
    }
    return 0;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Node *head = NULL;
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
            free_list(head);
            return 1;
        }
        if (!append(&head, value)) {
            fprintf(stderr, "Memory allocation failed.\n");
            free_list(head);
            return 1;
        }
    }

    display(head);
    printf("Enter value to search: ");
    if (scanf("%d", &value) != 1) {
        fprintf(stderr, "Invalid search value.\n");
        free_list(head);
        return 1;
    }
    position = search(head, value);
    if (position == 0) {
        printf("%d was not found.\n", value);
    } else {
        printf("%d found at position %d.\n", value, position);
    }

    free_list(head);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `singly_list_traversal_search.c`

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
Enter number of nodes (0-100): Value for node 1: Value for node 2: Value for node 3: List: 10 -> 20 -> 30 -> NULL
Enter value to search: 20 found at position 2.
```

## 10. Dry Run
For 10->20->30 and key 20: compare 10 at position 1, advance; compare 20 at position 2, match and stop.

| Position | Value | Compare to 20 | Result |\n|---:|---:|---|---|\n| 1 | 10 | Unequal | Advance |\n| 2 | 20 | Equal | Found, stop |

## 11. Time and Space Complexity
Traversal/search O(n) worst and O(1) best for a first-node match. Appending with a tail scan makes building n nodes O(n^2). Space is O(n).

## 12. Advantages and Disadvantages
- **Advantages:** Dynamic size; search does not require sorted input.
- **Disadvantages:** Sequential search and pointer memory; tail-scan construction is quadratic.

## 13. Applications
Finding records in dynamically sized arrival-order lists.

## 14. Common Errors
Moving head instead of current; forgetting current=current->next; using NULL termination incorrectly; failing to release memory.

## 15. POE Viva Questions and Answers
1. **Q: What is a traversal?**  
   A: Visiting nodes in order by following their links.
2. **Q: What is the aim of Experiment 9?**  
   A: Create a singly linked list, traverse all nodes, and search for a key.
3. **Q: What important rule should be preserved?**  
   A: Use a temporary current pointer so head remains available. Increment the position as current advances; reaching NULL means absent.
4. **Q: What precondition must be checked?**  
   A: A valid head pointer; NULL is a valid empty list.
5. **Q: How should the important edge case be handled?**  
   A: Search on empty returns not found without dereferencing any node.
6. **Q: What is the time and space complexity?**  
   A: Traversal/search O(n) worst and O(1) best for a first-node match. Appending with a tail scan makes building n nodes O(n^2). Space is O(n).
7. **Q: State one advantage.**  
   A: Dynamic size; search does not require sorted input.
8. **Q: State one limitation.**  
   A: Sequential search and pointer memory; tail-scan construction is quadratic.
9. **Q: Give one practical application.**  
   A: Finding records in dynamically sized arrival-order lists.
10. **Q: Name a common programming error.**  
   A: Moving head instead of current; forgetting current=current->next; using NULL termination incorrectly; failing to release memory.
11. **Q: Why use current instead of changing head?**  
   A: The original head is needed for later operations and cleanup.
12. **Q: How does traversal terminate?**  
   A: The next pointer eventually becomes NULL.
13. **Q: What does search return for absence?**  
   A: Zero; valid positions start at one.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: For 10->20->30 and key 20: compare 10 at position 1, advance; compare 20 at position 2, match and stop.
2. Test the program's edge case: Search on empty returns not found without dereferencing any node.
3. Explain the central rule without looking at the source: Use a temporary current pointer so head remains available. Increment the position as current advances; reaching NULL means absent.
4. Compare this structure or algorithm with its alternative: Array linear search uses indexes; linked search uses pointers but is still O(n).
5. Discuss this program's performance: Traversal/search O(n) worst and O(1) best for a first-node match. Appending with a tail scan makes building n nodes O(n^2). Space is O(n).

## 17. Important Exam Points
- Keep head unchanged
- Advance once per node
- Check empty lists and free all nodes.
