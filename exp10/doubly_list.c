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
