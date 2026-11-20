#include <stdio.h>

#define CAPACITY 5

int main(void)
{
    int queue[CAPACITY];
    int front = 0;
    int rear = -1;
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
                if (rear == CAPACITY - 1) {
                    printf("Queue overflow: no free slot at the rear.\n");
                    break;
                }
                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid queue value.\n");
                    return 1;
                }
                queue[++rear] = value; /* New values join at the rear. */
                printf("Inserted %d.\n", value);
                break;
            case 2:
                if (front > rear) {
                    printf("Queue underflow: queue is empty.\n");
                    break;
                }
                printf("Deleted %d.\n", queue[front++]); /* Oldest value leaves first. */
                if (front > rear) {
                    front = 0;
                    rear = -1;
                }
                break;
            case 3:
                if (front > rear) {
                    printf("Queue is empty.\n");
                    break;
                }
                printf("Front to rear: ");
                for (index = front; index <= rear; index++) {
                    printf("%d%s", queue[index], index == rear ? "\n" : " ");
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
