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
