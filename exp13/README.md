# Experiment 13 – Binary Search Tree

## 1. Aim
Create a BST by insertion and print inorder, preorder, and postorder traversals.

## 2. Problem Statement
Insert integer keys into a BST and display its three depth-first traversal orders.

## 3. Theory
In a BST, smaller values go left and larger values go right. This program ignores duplicates. Tree shape depends on input order.

## 4. Important Terminology
- **Binary Search Tree:** A binary tree where left descendants are smaller and right descendants are larger than a node.
- **Invariant:** Insertion compares recursively until it finds a NULL child. Traversals use different orders: inorder L-root-R; preorder root-L-R; postorder L-R-root.
- **Precondition:** Insertion maintains the ordering rule at every subtree.
- **Edge case:** An empty tree has root=NULL; each traversal safely prints nothing.
- **Complexity:** Insertion is average O(log n) in a balanced tree and worst O(n) when skewed. A full traversal is O(n). Space is O(n); recursion stack is O(height).

## 5. Working Principle
Insertion compares recursively until it finds a NULL child. Traversals use different orders: inorder L-root-R; preorder root-L-R; postorder L-R-root.

## 6. Algorithm
1. Start root=NULL. Insert each key according to comparisons
2. Allocate at a NULL link
3. Ignore equals. Run three recursive traversals, then free child subtrees before each parent.

## 7. Program Explanation
Node contains data and left/right pointers. insert returns the updated subtree root. malloc is checked through allocation_failed. NULL is the recursive base case. The three traversal functions differ only in when they print root. free_tree releases children before parent.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `binary_search_tree.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `binary_search_tree.c`

**Sample input**

```text
5
50
30
70
20
40
```

**Actual program output**

```text
Enter number of values (0-100): Value 1: Value 2: Value 3: Value 4: Value 5: Inorder (left, root, right): 20 30 40 50 70 
Preorder (root, left, right): 50 30 20 40 70 
Postorder (left, right, root): 20 40 30 70 50
```

## 10. Dry Run
Insert 50 root; 30 goes left; 70 right; 20 left of 30; 40 right of 30. Inorder: 20,30,40,50,70. Preorder: 50,30,20,40,70. Postorder: 20,40,30,70,50.

| Insert | Comparisons | Position |\n|---:|---|---|\n| 50 | Empty | Root |\n| 30 | 30<50 | Left of 50 |\n| 70 | 70>50 | Right of 50 |\n| 20 | 20<50, 20<30 | Left of 30 |\n| 40 | 40<50, 40>30 | Right of 30 |

## 11. Time and Space Complexity
Insertion is average O(log n) in a balanced tree and worst O(n) when skewed. A full traversal is O(n). Space is O(n); recursion stack is O(height).

## 12. Advantages and Disadvantages
- **Advantages:** Inorder traversal produces sorted values; dynamic insertions preserve ordering.
- **Disadvantages:** No balancing or deletion; skewed input can reduce performance to O(n).

## 13. Applications
Ordered sets, indexes, and sorted reporting.

## 14. Common Errors
Reversing left/right comparison; missing NULL base case; assuming all BST operations are O(log n); inconsistent duplicate handling.

## 15. POE Viva Questions and Answers
1. **Q: What is a binary search tree?**  
   A: A binary tree where left descendants are smaller and right descendants are larger than a node.
2. **Q: What is the aim of Experiment 13?**  
   A: Create a BST by insertion and print inorder, preorder, and postorder traversals.
3. **Q: What important rule should be preserved?**  
   A: Insertion compares recursively until it finds a NULL child. Traversals use different orders: inorder L-root-R; preorder root-L-R; postorder L-R-root.
4. **Q: What precondition must be checked?**  
   A: Insertion maintains the ordering rule at every subtree.
5. **Q: How should the important edge case be handled?**  
   A: An empty tree has root=NULL; each traversal safely prints nothing.
6. **Q: What is the time and space complexity?**  
   A: Insertion is average O(log n) in a balanced tree and worst O(n) when skewed. A full traversal is O(n). Space is O(n); recursion stack is O(height).
7. **Q: State one advantage.**  
   A: Inorder traversal produces sorted values; dynamic insertions preserve ordering.
8. **Q: State one limitation.**  
   A: No balancing or deletion; skewed input can reduce performance to O(n).
9. **Q: Give one practical application.**  
   A: Ordered sets, indexes, and sorted reporting.
10. **Q: Name a common programming error.**  
   A: Reversing left/right comparison; missing NULL base case; assuming all BST operations are O(log n); inconsistent duplicate handling.
11. **Q: Why does inorder produce ascending order?**  
   A: It visits the left values, then the node, then the larger right values.
12. **Q: What is the recursive base case?**  
   A: A NULL node means there is no subtree to process.
13. **Q: What is the worst-case shape?**  
   A: A chain of nodes, making the height O(n).

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insert 50 root; 30 goes left; 70 right; 20 left of 30; 40 right of 30. Inorder: 20,30,40,50,70. Preorder: 50,30,20,40,70. Postorder: 20,40,30,70,50.
2. Test the program's edge case: An empty tree has root=NULL; each traversal safely prints nothing.
3. Explain the central rule without looking at the source: Insertion compares recursively until it finds a NULL child. Traversals use different orders: inorder L-root-R; preorder root-L-R; postorder L-R-root.
4. Compare this structure or algorithm with its alternative: A BST can insert dynamically; a sorted array supports binary search but insertion shifts values.
5. Discuss this program's performance: Insertion is average O(log n) in a balanced tree and worst O(n) when skewed. A full traversal is O(n). Space is O(n); recursion stack is O(height).

## 17. Important Exam Points
- Know left < node < right and the exact traversal order
- Do not promise O(log n) without balance.
