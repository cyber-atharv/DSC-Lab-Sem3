#include <stdio.h>

#define CAPACITY 5

int main(void)
{
    int queue[CAPACITY];
    int front = 0;
    int count = 0;
    int choice;
    int value;
    int index;

    do {
        printf("\n1. INSERT\n2. DELETE\n3. Display\n4. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            return 1;
        }
        switch (choice) {
            case 1:
                if (count == CAPACITY) {
                    printf("Queue overflow: circular queue is full.\n");
                    break;
                }
                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid queue value.\n");
                    return 1;
                }
                /* Modulo wraps the rear slot back to zero when needed. */
                queue[(front + count) % CAPACITY] = value;
                count++;
                printf("Inserted %d.\n", value);
                break;
            case 2:
                if (count == 0) {
                    printf("Queue underflow: queue is empty.\n");
                    break;
                }
                printf("Deleted %d.\n", queue[front]);
                front = (front + 1) % CAPACITY;
                count--;
                break;
            case 3:
                if (count == 0) {
                    printf("Queue is empty.\n");
                    break;
                }
                printf("Front to rear: ");
                for (index = 0; index < count; index++) {
                    int slot = (front + index) % CAPACITY;
                    printf("%d%s", queue[slot], index == count - 1 ? "\n" : " ");
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
