# Experiment 8 – Singly Linked List: Insertion and Deletion

## 1. Aim
Insert and delete first/last nodes while safely managing dynamic memory.

## 2. Problem Statement
Implement beginning/end insertion and deletion in a singly linked list, including empty-list and allocation cases.

## 3. Theory
Each node stores data and a pointer to its successor. Nodes need not be adjacent in memory, and the list grows dynamically.

## 4. Important Terminology
- **Singly Linked List:** A chain of nodes where each node points only to its successor.
- **Invariant:** head is NULL when empty. Beginning insertion changes head; end insertion finds the final next link. Deletion unlinks a node and frees it.
- **Precondition:** Insertion requires successful allocation; deletion requires a non-empty list.
- **Edge case:** Deleting the sole node must set head back to NULL.
- **Complexity:** Beginning insertion/deletion O(1). End insertion/deletion O(n) here because there is no tail pointer. Traversal O(n); storage O(n).

## 5. Working Principle
head is NULL when empty. Beginning insertion changes head; end insertion finds the final next link. Deletion unlinks a node and frees it.

## 6. Algorithm
1. Start head=NULL. Allocate and initialize a node for insertion. Link it at head or after the last node. For deletion, check empty, update head or predecessor link, free removed node. Traverse to display and free all remaining nodes at exit.

## 7. Program Explanation
stdio.h handles input/output and stdlib.h supplies malloc/free. Node stores data and next. Helpers receive Node ** when they must update head. Allocation is checked before dereference. Deletion handles empty and one-node lists; free_list saves next before freeing each node. Menu choices select the operation.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `singly_list_insert_delete.c`

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static int insert_at_end(Node **head, int value)
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
    /* Follow links because the list does not store a tail pointer. */
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 1;
}

static int insert_at_beginning(Node **head, int value)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }
    node->data = value;
    node->next = *head;
    *head = node;
    return 1;
}

static int delete_first(Node **head, int *deleted_value)
{
    Node *removed;

    if (*head == NULL) {
        return 0;
    }
    removed = *head;
    *deleted_value = removed->data;
    *head = removed->next;
    free(removed);
    return 1;
}

static int delete_last(Node **head, int *deleted_value)
{
    Node *current;

    if (*head == NULL) {
        return 0;
    }
    if ((*head)->next == NULL) {
        return delete_first(head, deleted_value);
    }
    current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    *deleted_value = current->next->data;
    free(current->next);
    current->next = NULL;
    return 1;
}

static void display(const Node *head)
{
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    printf("List: ");
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
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
    int choice;
    int value;

    do {
        printf("\n1. Insert at beginning\n2. Insert at end\n");
        printf("3. Delete first\n4. Delete last\n5. Display\n6. Exit\nChoice: ");
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
                if ((choice == 1 && !insert_at_beginning(&head, value)) ||
                    (choice == 2 && !insert_at_end(&head, value))) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    free_list(head);
                    return 1;
                }
                printf("Inserted %d.\n", value);
                break;
            case 3:
                if (delete_first(&head, &value)) {
                    printf("Deleted first value %d.\n", value);
                } else {
                    printf("List is empty; nothing to delete.\n");
                }
                break;
            case 4:
                if (delete_last(&head, &value)) {
                    printf("Deleted last value %d.\n", value);
                } else {
                    printf("List is empty; nothing to delete.\n");
                }
                break;
            case 5:
                display(head);
                break;
            case 6:
                printf("Goodbye.\n");
                break;
            default:
                printf("Choose an option from 1 to 6.\n");
        }
    } while (choice != 6);

    free_list(head);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `singly_list_insert_delete.c`

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

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: Enter value: Inserted 10.

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: Enter value: Inserted 20.

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: List: 10 -> 20 -> NULL

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: Deleted first value 10.

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: List: 20 -> NULL

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: Deleted last value 20.

1. Insert at beginning
2. Insert at end
3. Delete first
4. Delete last
5. Display
6. Exit
Choice: Goodbye.
```

## 10. Dry Run
Insert 10 at beginning: head->10->NULL. Append 20: head->10->20->NULL. Delete first frees 10 and head becomes 20. Delete last frees 20 and head becomes NULL.

| Step | Links |\n|---|---|\n| Empty | head -> NULL |\n| Insert 10,20 | head -> 10 -> 20 -> NULL |\n| Delete first | head -> 20 -> NULL |\n| Delete last | head -> NULL |

## 11. Time and Space Complexity
Beginning insertion/deletion O(1). End insertion/deletion O(n) here because there is no tail pointer. Traversal O(n); storage O(n).

## 12. Advantages and Disadvantages
- **Advantages:** Can grow dynamically and update the head in O(1).
- **Disadvantages:** No direct indexing; end operations need traversal; each node adds pointer storage.

## 13. Applications
Dynamic collections, adjacency lists, and stack/queue implementations.

## 14. Common Errors
Dereferencing NULL; losing next links; not freeing deleted nodes; mishandling a one-node list.

## 15. POE Viva Questions and Answers
1. **Q: What is a singly linked list?**  
   A: A chain of nodes where each node points only to its successor.
2. **Q: What is the aim of Experiment 8?**  
   A: Insert and delete first/last nodes while safely managing dynamic memory.
3. **Q: What important rule should be preserved?**  
   A: head is NULL when empty. Beginning insertion changes head; end insertion finds the final next link. Deletion unlinks a node and frees it.
4. **Q: What precondition must be checked?**  
   A: Insertion requires successful allocation; deletion requires a non-empty list.
5. **Q: How should the important edge case be handled?**  
   A: Deleting the sole node must set head back to NULL.
6. **Q: What is the time and space complexity?**  
   A: Beginning insertion/deletion O(1). End insertion/deletion O(n) here because there is no tail pointer. Traversal O(n); storage O(n).
7. **Q: State one advantage.**  
   A: Can grow dynamically and update the head in O(1).
8. **Q: State one limitation.**  
   A: No direct indexing; end operations need traversal; each node adds pointer storage.
9. **Q: Give one practical application.**  
   A: Dynamic collections, adjacency lists, and stack/queue implementations.
10. **Q: Name a common programming error.**  
   A: Dereferencing NULL; losing next links; not freeing deleted nodes; mishandling a one-node list.
11. **Q: Why free a deleted node?**  
   A: To release its dynamic memory and prevent a leak.
12. **Q: Why is deleting the last node O(n)?**  
   A: The previous node must be found because nodes have no previous link.
13. **Q: What is the empty-list representation?**  
   A: head is NULL.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insert 10 at beginning: head->10->NULL. Append 20: head->10->20->NULL. Delete first frees 10 and head becomes 20. Delete last frees 20 and head becomes NULL.
2. Test the program's edge case: Deleting the sole node must set head back to NULL.
3. Explain the central rule without looking at the source: head is NULL when empty. Beginning insertion changes head; end insertion finds the final next link. Deletion unlinks a node and frees it.
4. Compare this structure or algorithm with its alternative: Arrays allow direct indexing; lists avoid shifting but require sequential traversal.
5. Discuss this program's performance: Beginning insertion/deletion O(1). End insertion/deletion O(n) here because there is no tail pointer. Traversal O(n); storage O(n).

## 17. Important Exam Points
- Handle empty and single-node cases
- Preserve links before freeing
- Check malloc and free remaining nodes.
