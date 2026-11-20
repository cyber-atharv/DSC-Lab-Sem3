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
