# Experiment 10 – Doubly Linked List

## 1. Aim
Insert, delete, search, and traverse a doubly linked list in both directions.

## 2. Problem Statement
Maintain both previous and next links along with head and tail pointers.

## 3. Theory
Doubly linked nodes point to their predecessor and successor. This supports backward traversal and easy unlinking, at the cost of another pointer.

## 4. Important Terminology
- **Doubly Linked List:** A linked list whose nodes contain both previous and next pointers.
- **Invariant:** For neighbors A and B, A->next=B and B->previous=A. Update both links and the head/tail pointers when an endpoint changes.
- **Precondition:** head and tail must be consistent; empty means both are NULL.
- **Edge case:** Deleting the sole node resets both pointers to NULL.
- **Complexity:** Endpoint insertion/deletion O(1) with head/tail; search and traversal O(n); storage O(n) with two links per node.

## 5. Working Principle
For neighbors A and B, A->next=B and B->previous=A. Update both links and the head/tail pointers when an endpoint changes.

## 6. Algorithm
1. Initialize head=tail=NULL. Insert at beginning/end and update both neighbor links. Delete an endpoint by reconnecting its neighbors. Search forward
2. Traverse from head and tail
3. Free nodes at exit.

## 7. Program Explanation
Node stores data, previous, and next. head and tail permit direct access to both endpoints. Insertion allocates and initializes all fields. remove_node reconnects both neighbors, updates endpoint pointers, and frees the selected node. Search uses a local current pointer. Forward and backward display demonstrate the two links.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `doubly_list.c`

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *previous;
    struct Node *next;
} Node;

static int insert_end(Node **head, Node **tail, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    node->previous = *tail;
    node->next = NULL;
    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;
    return 1;
}

static int insert_beginning(Node **head, Node **tail, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    node->previous = NULL;
    node->next = *head;
    if (*head == NULL) {
        *tail = node;
    } else {
        (*head)->previous = node;
    }
    *head = node;
    return 1;
}

static int remove_node(Node **head, Node **tail, Node *node, int *value)
{
    if (node == NULL) {
        return 0;
    }
    *value = node->data;
    /* Reconnect both neighboring links before releasing this node. */
    if (node->previous == NULL) {
        *head = node->next;
    } else {
        node->previous->next = node->next;
    }
    if (node->next == NULL) {
        *tail = node->previous;
    } else {
        node->next->previous = node->previous;
    }
    free(node);
    return 1;
}

static void display_forward(const Node *head)
{
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Forward: ");
    while (head != NULL) {
        printf("%d%s", head->data, head->next == NULL ? " -> NULL\n" : " <-> ");
        head = head->next;
    }
}

static void display_backward(const Node *tail)
{
    if (tail == NULL) {
        return;
    }
    printf("Backward: ");
    while (tail != NULL) {
        printf("%d%s", tail->data, tail->previous == NULL ? " -> NULL\n" : " <-> ");
        tail = tail->previous;
    }
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
    Node *tail = NULL;
    int choice;
    int value;

    do {
        printf("\n1. Insert beginning\n2. Insert end\n3. Delete beginning\n");
        printf("4. Delete end\n5. Search\n6. Traverse both ways\n7. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            free_list(head);
            return 1;
        }
        switch (choice) {
            case 1:
            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid value.\n");
                    free_list(head);
                    return 1;
                }
                if ((choice == 1 && !insert_beginning(&head, &tail, value)) ||
                    (choice == 2 && !insert_end(&head, &tail, value))) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free_list(head);
                    return 1;
                }
                printf("Inserted %d.\n", value);
                break;
            case 3:
                if (!remove_node(&head, &tail, head, &value)) {
                    printf("List is empty; nothing to delete.\n");
                } else {
                    printf("Deleted %d.\n", value);
                }
                break;
            case 4:
                if (!remove_node(&head, &tail, tail, &value)) {
                    printf("List is empty; nothing to delete.\n");
                } else {
                    printf("Deleted %d.\n", value);
                }
                break;
            case 5: {
                Node *current = head;
                int position = 1;
                int found = 0;

                printf("Enter value to search: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid search value.\n");
                    free_list(head);
                    return 1;
                }
                while (current != NULL) {
                    if (current->data == value) {
                        printf("%d found at position %d.\n", value, position);
                        found = 1;
                        break;
                    }
                    current = current->next;
                    position++;
                }
                if (!found) {
                    printf("%d was not found.\n", value);
                }
                break;
            }
            case 6:
                display_forward(head);
                display_backward(tail);
                break;
            case 7:
                printf("Goodbye.\n");
                break;
            default:
                printf("Choose an option from 1 to 7.\n");
        }
    } while (choice != 7);

    free_list(head);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `doubly_list.c`

**Sample input**

```text
1
10
2
20
6
5
20
4
6
7
```

**Actual program output**

```text

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Enter value: Inserted 10.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Enter value: Inserted 20.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Forward: 10 <-> 20 -> NULL
Backward: 20 <-> 10 -> NULL

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Enter value to search: 20 found at position 2.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Deleted 20.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Forward: 10 -> NULL
Backward: 10 -> NULL

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Search
6. Traverse both ways
7. Exit
Choice: Goodbye.
```

## 10. Dry Run
Insert 10 then 20: 10<->20. Delete tail 20: 10->next becomes NULL and 10 becomes tail. Backward traversal from tail now visits 10.

| Operation | Forward | Backward | Endpoints |\n|---|---|---|---|\n| Insert 10 | 10 | 10 | head=tail=10 |\n| Append 20 | 10 -> 20 | 20 -> 10 | head=10, tail=20 |\n| Delete tail | 10 | 10 | head=tail=10 |

## 11. Time and Space Complexity
Endpoint insertion/deletion O(1) with head/tail; search and traversal O(n); storage O(n) with two links per node.

## 12. Advantages and Disadvantages
- **Advantages:** Moves in either direction and supports constant-time endpoint changes.
- **Disadvantages:** Each node uses extra pointer memory; link updates are more error-prone.

## 13. Applications
Browser navigation, playlists, deques, and reversible history.

## 14. Common Errors
Updating only one link direction; not updating head/tail; leaving dangling pointers; freeing before preserving links.

## 15. POE Viva Questions and Answers
1. **Q: What is a doubly linked list?**  
   A: A linked list whose nodes contain both previous and next pointers.
2. **Q: What is the aim of Experiment 10?**  
   A: Insert, delete, search, and traverse a doubly linked list in both directions.
3. **Q: What important rule should be preserved?**  
   A: For neighbors A and B, A->next=B and B->previous=A. Update both links and the head/tail pointers when an endpoint changes.
4. **Q: What precondition must be checked?**  
   A: head and tail must be consistent; empty means both are NULL.
5. **Q: How should the important edge case be handled?**  
   A: Deleting the sole node resets both pointers to NULL.
6. **Q: What is the time and space complexity?**  
   A: Endpoint insertion/deletion O(1) with head/tail; search and traversal O(n); storage O(n) with two links per node.
7. **Q: State one advantage.**  
   A: Moves in either direction and supports constant-time endpoint changes.
8. **Q: State one limitation.**  
   A: Each node uses extra pointer memory; link updates are more error-prone.
9. **Q: Give one practical application.**  
   A: Browser navigation, playlists, deques, and reversible history.
10. **Q: Name a common programming error.**  
   A: Updating only one link direction; not updating head/tail; leaving dangling pointers; freeing before preserving links.
11. **Q: What must hold for adjacent nodes A and B?**  
   A: A->next points to B, and B->previous points to A.
12. **Q: Why are head and tail both stored?**  
   A: They allow direct access to both endpoints.
13. **Q: How many link fields are in each node?**  
   A: Two: previous and next.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insert 10 then 20: 10<->20. Delete tail 20: 10->next becomes NULL and 10 becomes tail. Backward traversal from tail now visits 10.
2. Test the program's edge case: Deleting the sole node resets both pointers to NULL.
3. Explain the central rule without looking at the source: For neighbors A and B, A->next=B and B->previous=A. Update both links and the head/tail pointers when an endpoint changes.
4. Compare this structure or algorithm with its alternative: Singly linked lists use less memory but cannot move directly backward.
5. Discuss this program's performance: Endpoint insertion/deletion O(1) with head/tail; search and traversal O(n); storage O(n) with two links per node.

## 17. Important Exam Points
- Keep both directions consistent
- Update endpoints
- Handle empty and one-node lists.
