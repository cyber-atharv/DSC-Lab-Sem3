# Experiment 5 – Queue Using a Linear Array

## 1. Aim
Implement FIFO insertion, deletion, and display using a simple linear array.

## 2. Problem Statement
Create an array queue with INSERT, DELETE, display, overflow, and underflow behavior.

## 3. Theory
A queue is FIFO: values enter at rear and leave at front. In this linear version, deleted positions before front are not reused until the queue becomes empty.

## 4. Important Terminology
- **Queue:** A collection where the earliest inserted value is removed first.
- **Invariant:** The empty state is front=0/rear=-1. INSERT writes at ++rear; DELETE reads at front++. After the last deletion, reset both indexes.
- **Precondition:** INSERT needs a slot after rear; DELETE needs front<=rear.
- **Edge case:** The final deletion resets indexes to the initial empty state.
- **Complexity:** INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 5. Working Principle
The empty state is front=0/rear=-1. INSERT writes at ++rear; DELETE reads at front++. After the last deletion, reset both indexes.

## 6. Algorithm
1. Initialize front and rear. INSERT checks rear against the last slot. DELETE checks front>rear, removes front, then resets if empty. Display prints front through rear.

## 7. Program Explanation
The queue array uses front and rear indexes. The switch dispatches operations and scanf results are checked. The linear overflow test may report full when rear reaches the final slot even though earlier positions were deleted; this is the false-overflow limitation fixed by Experiment 6.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `linear_queue.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `linear_queue.c`

**Sample input**

```text
1
11
1
22
3
2
3
4
```

**Actual program output**

```text

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 11.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 22.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Front to rear: 11 22

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Deleted 11.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Front to rear: 22

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Goodbye.
```

## 10. Dry Run
Insert 11,22: front=0/rear=1. Delete 11: front=1; 22 remains. Delete 22: front>rear, so reset to front=0/rear=-1.

| Step | front | rear | Logical queue |\n|---|---:|---:|---|\n| Start | 0 | -1 | empty |\n| Insert 11,22 | 0 | 1 | 11,22 |\n| Delete 11 | 1 | 1 | 22 |\n| Delete 22 | 0 | -1 | empty |

## 11. Time and Space Complexity
INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 12. Advantages and Disadvantages
- **Advantages:** Preserves arrival order with constant-time basic operations.
- **Disadvantages:** Freed slots at the front can be wasted, causing false overflow.

## 13. Applications
Simple service lines, print queues, and FIFO examples.

## 14. Common Errors
Using rear alone as empty test after deletions; forgetting reset after final delete; confusing FIFO order.

## 15. POE Viva Questions and Answers
1. **Q: What is a queue?**  
   A: A collection where the earliest inserted value is removed first.
2. **Q: What is the aim of Experiment 5?**  
   A: Implement FIFO insertion, deletion, and display using a simple linear array.
3. **Q: What important rule should be preserved?**  
   A: The empty state is front=0/rear=-1. INSERT writes at ++rear; DELETE reads at front++. After the last deletion, reset both indexes.
4. **Q: What precondition must be checked?**  
   A: INSERT needs a slot after rear; DELETE needs front<=rear.
5. **Q: How should the important edge case be handled?**  
   A: The final deletion resets indexes to the initial empty state.
6. **Q: What is the time and space complexity?**  
   A: INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).
7. **Q: State one advantage.**  
   A: Preserves arrival order with constant-time basic operations.
8. **Q: State one limitation.**  
   A: Freed slots at the front can be wasted, causing false overflow.
9. **Q: Give one practical application.**  
   A: Simple service lines, print queues, and FIFO examples.
10. **Q: Name a common programming error.**  
   A: Using rear alone as empty test after deletions; forgetting reset after final delete; confusing FIFO order.
11. **Q: Which end accepts new values?**  
   A: The rear.
12. **Q: Which value is deleted first?**  
   A: The front value, which has waited the longest.
13. **Q: What is false overflow?**  
   A: The rear is at the final slot although earlier deleted slots are free.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insert 11,22: front=0/rear=1. Delete 11: front=1; 22 remains. Delete 22: front>rear, so reset to front=0/rear=-1.
2. Test the program's edge case: The final deletion resets indexes to the initial empty state.
3. Explain the central rule without looking at the source: The empty state is front=0/rear=-1. INSERT writes at ++rear; DELETE reads at front++. After the last deletion, reset both indexes.
4. Compare this structure or algorithm with its alternative: Experiment 6 wraps around and reuses freed positions; this experiment does not.
5. Discuss this program's performance: INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 17. Important Exam Points
- Queue means FIFO
- Insert at rear and delete at front
- This linear implementation can waste freed slots.
