# Experiment 11 – Circular Singly Linked List: Insertion and Deletion

## 1. Aim
Insert and delete at both ends while maintaining a circular link.

## 2. Problem Statement
Implement beginning/end operations on a circular singly linked list using a tail pointer.

## 3. Theory
The last node links back to the first, not NULL. With tail stored, head is tail->next. A single node points to itself.

## 4. Important Terminology
- **Circular Singly Linked List:** A singly linked list whose final node points back to its first node.
- **Invariant:** Empty means tail=NULL. Beginning insertion links between tail and old head. End insertion also moves tail. Delete tail by finding its predecessor.
- **Precondition:** A non-empty traversal ends when it returns to the saved head.
- **Edge case:** Deleting the only node sets tail=NULL.
- **Complexity:** Beginning insertion/deletion O(1); deleting the tail O(n); traversal O(n). Space O(n).

## 5. Working Principle
Empty means tail=NULL. Beginning insertion links between tail and old head. End insertion also moves tail. Delete tail by finding its predecessor.

## 6. Algorithm
1. Initialize tail=NULL. Insert allocated nodes and preserve tail->next=head. For deletion, handle empty/singleton cases and reconnect links. Display one cycle and break the circle temporarily to free nodes.

## 7. Program Explanation
Node stores data and next. tail->next identifies the head. Helpers check malloc and carefully maintain the cycle. End deletion scans for the predecessor; beginning deletion updates tail->next. display uses do-while because it must process head before comparing with the saved start. free_list breaks the cycle before linear freeing.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `circular_list_insert_delete.c`

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static int insert_beginning(Node **tail, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    if (*tail == NULL) {
        node->next = node;
        *tail = node;
    } else {
        /* The new head is placed between the tail and the old head. */
        node->next = (*tail)->next;
        (*tail)->next = node;
    }
    return 1;
}

static int insert_end(Node **tail, int value)
{
    if (!insert_beginning(tail, value)) {
        return 0;
    }
    *tail = (*tail)->next;
    return 1;
}

static int delete_beginning(Node **tail, int *value)
{
    Node *head;

    if (*tail == NULL) {
        return 0;
    }
    head = (*tail)->next;
    *value = head->data;
    if (head == *tail) {
        *tail = NULL;
    } else {
        (*tail)->next = head->next;
    }
    free(head);
    return 1;
}

static int delete_end(Node **tail, int *value)
{
    Node *previous;

    if (*tail == NULL) {
        return 0;
    }
    if ((*tail)->next == *tail) {
        return delete_beginning(tail, value);
    }
    previous = (*tail)->next;
    while (previous->next != *tail) {
        previous = previous->next;
    }
    *value = (*tail)->data;
    previous->next = (*tail)->next;
    free(*tail);
    *tail = previous;
    return 1;
}

static void display(const Node *tail)
{
    const Node *current;

    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("Circular list: ");
    current = tail->next;
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != tail->next);
    printf("(back to head)\n");
}

static void free_list(Node **tail)
{
    Node *head;

    if (*tail == NULL) {
        return;
    }
    head = (*tail)->next;
    /* Break the cycle so the remaining nodes can be freed linearly. */
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
    int choice;
    int value;

    do {
        printf("\n1. Insert beginning\n2. Insert end\n3. Delete beginning\n");
        printf("4. Delete end\n5. Display\n6. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            free_list(&tail);
            return 1;
        }
        switch (choice) {
            case 1:
            case 2:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid value.\n");
                    free_list(&tail);
                    return 1;
                }
                if ((choice == 1 && !insert_beginning(&tail, value)) ||
                    (choice == 2 && !insert_end(&tail, value))) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free_list(&tail);
                    return 1;
                }
                printf("Inserted %d.\n", value);
                break;
            case 3:
                if (delete_beginning(&tail, &value)) {
                    printf("Deleted first value %d.\n", value);
                } else {
                    printf("List is empty; nothing to delete.\n");
                }
                break;
            case 4:
                if (delete_end(&tail, &value)) {
                    printf("Deleted last value %d.\n", value);
                } else {
                    printf("List is empty; nothing to delete.\n");
                }
                break;
            case 5:
                display(tail);
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Choose an option from 1 to 6.\n");
        }
    } while (choice != 6);

    free_list(&tail);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `circular_list_insert_delete.c`

**Sample input**

```text
1
10
2
20
5
3
5
4
6
```

**Actual program output**

```text

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Enter value: Inserted 10.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Enter value: Inserted 20.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Circular list: 10 -> 20 -> (back to head)

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Deleted first value 10.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Circular list: 20 -> (back to head)

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Deleted last value 20.

1. Insert beginning
2. Insert end
3. Delete beginning
4. Delete end
5. Display
6. Exit
Choice: Goodbye.
```

## 10. Dry Run
Insert 10 into empty list: 10->10. Append 20: 10->20->10, tail=20. Delete first removes 10 and makes 20 point to itself.

| Step | Circular chain | tail |\n|---|---|---|\n| Empty | none | NULL |\n| Insert 10 | 10 -> back to 10 | 10 |\n| Append 20 | 10 -> 20 -> back to 10 | 20 |\n| Delete first | 20 -> back to 20 | 20 |

## 11. Time and Space Complexity
Beginning insertion/deletion O(1); deleting the tail O(n); traversal O(n). Space O(n).

## 12. Advantages and Disadvantages
- **Advantages:** Repeated cycling is natural; tail provides efficient beginning/end insertion.
- **Disadvantages:** No NULL terminator; incorrect traversal can loop forever; tail deletion scans.

## 13. Applications
Round-robin scheduling, circular playlists, and turn-based games.

## 14. Common Errors
Looping until NULL; failing to reconnect tail to head; mishandling one node; freeing an intact cycle.

## 15. POE Viva Questions and Answers
1. **Q: What is a circular singly linked list?**  
   A: A singly linked list whose final node points back to its first node.
2. **Q: What is the aim of Experiment 11?**  
   A: Insert and delete at both ends while maintaining a circular link.
3. **Q: What important rule should be preserved?**  
   A: Empty means tail=NULL. Beginning insertion links between tail and old head. End insertion also moves tail. Delete tail by finding its predecessor.
4. **Q: What precondition must be checked?**  
   A: A non-empty traversal ends when it returns to the saved head.
5. **Q: How should the important edge case be handled?**  
   A: Deleting the only node sets tail=NULL.
6. **Q: What is the time and space complexity?**  
   A: Beginning insertion/deletion O(1); deleting the tail O(n); traversal O(n). Space O(n).
7. **Q: State one advantage.**  
   A: Repeated cycling is natural; tail provides efficient beginning/end insertion.
8. **Q: State one limitation.**  
   A: No NULL terminator; incorrect traversal can loop forever; tail deletion scans.
9. **Q: Give one practical application.**  
   A: Round-robin scheduling, circular playlists, and turn-based games.
10. **Q: Name a common programming error.**  
   A: Looping until NULL; failing to reconnect tail to head; mishandling one node; freeing an intact cycle.
11. **Q: Where is head when only tail is stored?**  
   A: At tail->next.
12. **Q: Why does a one-node list point to itself?**  
   A: That node is both first and last, so its next points back to itself.
13. **Q: How does traversal stop?**  
   A: It stops when the current pointer returns to the saved head.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insert 10 into empty list: 10->10. Append 20: 10->20->10, tail=20. Delete first removes 10 and makes 20 point to itself.
2. Test the program's edge case: Deleting the only node sets tail=NULL.
3. Explain the central rule without looking at the source: Empty means tail=NULL. Beginning insertion links between tail and old head. End insertion also moves tail. Delete tail by finding its predecessor.
4. Compare this structure or algorithm with its alternative: A linear list ends at NULL; a circular list terminates traversal by returning to its start.
5. Discuss this program's performance: Beginning insertion/deletion O(1); deleting the tail O(n); traversal O(n). Space O(n).

## 17. Important Exam Points
- Empty tail is NULL
- Non-empty head is tail->next
- Do not use NULL to end a circular traversal.
