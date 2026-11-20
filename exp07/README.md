# Experiment 7 – Implement a Stack Using Queues

## 1. Aim
Reproduce stack behavior by combining two FIFO queues.

## 2. Problem Statement
Implement PUSH, POP, and display for a stack using queue operations.

## 3. Theory
The program makes PUSH expensive: enqueue the new value into a helper queue, transfer older values behind it, then swap queue roles. The primary front is always the stack top.

## 4. Important Terminology
- **Stack Using Queues:** A stack abstraction built from queue operations while preserving LIFO behavior.
- **Invariant:** PUSH puts the new value first in the new primary queue. POP removes its front. Thus the primary queue is maintained in top-first order.
- **Precondition:** Both queues are bounded; PUSH is rejected when all capacity is used.
- **Edge case:** An empty primary queue makes POP underflow.
- **Complexity:** PUSH is O(n), POP is O(1), and display is O(n). Two fixed queues use O(CAPACITY) storage each.

## 5. Working Principle
PUSH puts the new value first in the new primary queue. POP removes its front. Thus the primary queue is maintained in top-first order.

## 6. Algorithm
1. Initialize two queues. For PUSH, check capacity, enqueue the new item in helper, transfer all primary items, then swap. For POP, dequeue primary or report underflow. Display primary from front.

## 7. Program Explanation
Queue contains a fixed array, front, and count. initialize_queue, enqueue, and dequeue implement FIFO operations with modulo indexing. The main switch builds stack operations from these helpers. During PUSH the helper receives the new top then all old items; swapping structures establishes the invariant. The code checks input and capacity.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `stack_using_queues.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `stack_using_queues.c`

**Sample input**

```text
1
10
1
20
3
2
3
4
```

**Actual program output**

```text

1. PUSH
2. POP
3. Display
4. Exit
Choice: Enter value to push: Pushed 10.

1. PUSH
2. POP
3. Display
4. Exit
Choice: Enter value to push: Pushed 20.

1. PUSH
2. POP
3. Display
4. Exit
Choice: Top to bottom: 20 10

1. PUSH
2. POP
3. Display
4. Exit
Choice: Popped 20.

1. PUSH
2. POP
3. Display
4. Exit
Choice: Top to bottom: 10

1. PUSH
2. POP
3. Display
4. Exit
Choice: Goodbye.
```

## 10. Dry Run
Push 10 -> primary [10]. Push 20 -> helper [20], transfer 10 -> helper [20,10], then swap. Pop removes 20, matching LIFO.

| Operation | Primary queue, front first | Stack top |\n|---|---|---:|\n| PUSH 10 | 10 | 10 |\n| PUSH 20 | 20,10 | 20 |\n| POP | 10 | 10 |

## 11. Time and Space Complexity
PUSH is O(n), POP is O(1), and display is O(n). Two fixed queues use O(CAPACITY) storage each.

## 12. Advantages and Disadvantages
- **Advantages:** Keeps POP constant-time using only queue operations.
- **Disadvantages:** PUSH transfers all values and is O(n); two arrays are needed.

## 13. Applications
ADT composition and cases where only queue primitives are available.

## 14. Common Errors
Not emptying the helper before a push; swapping too early; reversing transfer order; reporting the wrong top.

## 15. POE Viva Questions and Answers
1. **Q: What is a stack using queues?**  
   A: A stack abstraction built from queue operations while preserving LIFO behavior.
2. **Q: What is the aim of Experiment 7?**  
   A: Reproduce stack behavior by combining two FIFO queues.
3. **Q: What important rule should be preserved?**  
   A: PUSH puts the new value first in the new primary queue. POP removes its front. Thus the primary queue is maintained in top-first order.
4. **Q: What precondition must be checked?**  
   A: Both queues are bounded; PUSH is rejected when all capacity is used.
5. **Q: How should the important edge case be handled?**  
   A: An empty primary queue makes POP underflow.
6. **Q: What is the time and space complexity?**  
   A: PUSH is O(n), POP is O(1), and display is O(n). Two fixed queues use O(CAPACITY) storage each.
7. **Q: State one advantage.**  
   A: Keeps POP constant-time using only queue operations.
8. **Q: State one limitation.**  
   A: PUSH transfers all values and is O(n); two arrays are needed.
9. **Q: Give one practical application.**  
   A: ADT composition and cases where only queue primitives are available.
10. **Q: Name a common programming error.**  
   A: Not emptying the helper before a push; swapping too early; reversing transfer order; reporting the wrong top.
11. **Q: Why transfer old items during PUSH?**  
   A: So the newly pushed item is at the primary queue front.
12. **Q: What is the time cost of PUSH?**  
   A: O(n), since existing items may be transferred.
13. **Q: Why is POP O(1)?**  
   A: The stack top is already the primary queue's front.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Push 10 -> primary [10]. Push 20 -> helper [20], transfer 10 -> helper [20,10], then swap. Pop removes 20, matching LIFO.
2. Test the program's edge case: An empty primary queue makes POP underflow.
3. Explain the central rule without looking at the source: PUSH puts the new value first in the new primary queue. POP removes its front. Thus the primary queue is maintained in top-first order.
4. Compare this structure or algorithm with its alternative: A direct array stack has O(1) PUSH and POP; this implementation trades slower PUSH for an instructive construction.
5. Discuss this program's performance: PUSH is O(n), POP is O(1), and display is O(n). Two fixed queues use O(CAPACITY) storage each.

## 17. Important Exam Points
- Primary front is the stack top
- Helper is emptied by role swapping
- The queue primitives remain FIFO even though the resulting abstraction is LIFO.
