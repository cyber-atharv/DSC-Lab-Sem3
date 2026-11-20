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
