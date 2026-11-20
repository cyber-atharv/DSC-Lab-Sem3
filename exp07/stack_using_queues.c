#include <stdio.h>

#define CAPACITY 100

typedef struct {
    int items[CAPACITY];
    int front;
    int count;
} Queue;

static void initialize_queue(Queue *queue)
{
    queue->front = 0;
    queue->count = 0;
}

static int enqueue(Queue *queue, int value)
{
    int rear;

    if (queue->count == CAPACITY) {
        return 0;
    }
    rear = (queue->front + queue->count) % CAPACITY;
    queue->items[rear] = value;
    queue->count++;
    return 1;
}

static int dequeue(Queue *queue, int *value)
{
    if (queue->count == 0) {
        return 0;
    }
    *value = queue->items[queue->front];
    queue->front = (queue->front + 1) % CAPACITY;
    queue->count--;
    return 1;
}

int main(void)
{
    Queue primary;
    Queue helper;
    int choice;
    int value;

    initialize_queue(&primary);
    initialize_queue(&helper);

    do {
        printf("\n1. PUSH\n2. POP\n3. Display\n4. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            return 1;
        }
        switch (choice) {
            case 1:
                if (primary.count == CAPACITY) {
                    printf("Stack overflow: stack is full.\n");
                    break;
                }
                printf("Enter value to push: ");
                if (scanf("%d", &value) != 1) {
                    fprintf(stderr, "Invalid stack value.\n");
                    return 1;
                }
                enqueue(&helper, value);
                /* Put the new item first so the primary front is the stack top. */
                while (dequeue(&primary, &value)) {
                    enqueue(&helper, value);
                }
                {
                    Queue temporary = primary;
                    primary = helper;
                    helper = temporary;
                }
                printf("Pushed %d.\n", primary.items[primary.front]);
                break;
            case 2:
                if (!dequeue(&primary, &value)) {
                    printf("Stack underflow: stack is empty.\n");
                } else {
                    printf("Popped %d.\n", value);
                }
                break;
            case 3:
                if (primary.count == 0) {
                    printf("Stack is empty.\n");
                } else {
                    int index;
                    printf("Top to bottom: ");
                    for (index = 0; index < primary.count; index++) {
                        int slot = (primary.front + index) % CAPACITY;
                        printf("%d%s", primary.items[slot],
                               index == primary.count - 1 ? "\n" : " ");
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
