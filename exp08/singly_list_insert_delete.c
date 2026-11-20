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
