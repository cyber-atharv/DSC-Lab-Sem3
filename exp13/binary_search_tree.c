#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

static Node *insert(Node *root, int value, int *allocation_failed)
{
    if (root == NULL) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            *allocation_failed = 1;
            return NULL;
        }
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    /* Preserve the BST rule: smaller values left, larger values right. */
    if (value < root->data) {
        root->left = insert(root->left, value, allocation_failed);
    } else if (value > root->data) {
        root->right = insert(root->right, value, allocation_failed);
    } else {
        printf("Duplicate %d ignored.\n", value);
    }
    return root;
}

static void inorder(const Node *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

static void preorder(const Node *root)
{
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

static void postorder(const Node *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

static void free_tree(Node *root)
{
    if (root != NULL) {
        /* Release children before their parent. */
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(void)
{
    Node *root = NULL;
    int count;
    int index;
    int value;
    int allocation_failed = 0;

    printf("Enter number of values (0-100): ");
    if (scanf("%d", &count) != 1 || count < 0 || count > 100) {
        fprintf(stderr, "Invalid number of values.\n");
        return 1;
    }
    for (index = 0; index < count; index++) {
        printf("Value %d: ", index + 1);
        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid tree value.\n");
            free_tree(root);
            return 1;
        }
        root = insert(root, value, &allocation_failed);
        if (allocation_failed) {
            fprintf(stderr, "Memory allocation failed.\n");
            free_tree(root);
            return 1;
        }
    }

    printf("Inorder (left, root, right): ");
    inorder(root);
    printf("\nPreorder (root, left, right): ");
    preorder(root);
    printf("\nPostorder (left, right, root): ");
    postorder(root);
    printf("\n");

    free_tree(root);
    return 0;
}
