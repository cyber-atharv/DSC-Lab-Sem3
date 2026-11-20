#include <stdio.h>

#define CAPACITY 5

int main(void)
{
    int stack[CAPACITY];
    int top = -1;
    int choice;
    int value;
    int index;

    do {
        printf("\n1. PUSH\n2. POP\n3. Display\n4. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            return 1;
        }
        switch (choice) {
            case 1:
                if (top == CAPACITY - 1) {
                    printf("Stack overflow: stack is full.\n");
                    break;
                }
                printf("Enter value to push: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid stack value.\n");
                    return 1;
                }
                stack[++top] = value; /* Move top first, then fill that slot. */
                printf("Pushed %d.\n", value);
                break;
            case 2:
                if (top == -1) {
                    printf("Stack underflow: stack is empty.\n");
                    break;
                }
                printf("Popped %d.\n", stack[top--]); /* Read before lowering top. */
                break;
            case 3:
                if (top == -1) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Top to bottom: ");
                    for (index = top; index >= 0; index--) {
                        printf("%d%s", stack[index], index == 0 ? "\n" : " ");
                    }
                }
                break;
            case 4:
                printf("Goodbye.\n");
                break;
            default:
                printf("Choose an option from 1 to 4.\n");
        }
    } while (choice != 4);

    return 0;
}
