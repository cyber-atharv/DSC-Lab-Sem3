# Experiment 6 – Circular Queue Using an Array

## 1. Aim
Reuse array positions by wrapping queue indexes around the fixed array.

## 2. Problem Statement
Implement circular queue insertion, deletion, display, overflow, and underflow.

## 3. Theory
A circular queue treats the final slot as adjacent to slot zero. Modulo arithmetic wraps indexes and reuses freed positions.

## 4. Important Terminology
- **Circular Queue:** A FIFO queue whose array indexes wrap around after the last slot.
- **Invariant:** count==0 means empty and count==capacity means full. Insert slot is (front+count)%capacity; deletion advances front modulo capacity.
- **Precondition:** Insert requires count<CAPACITY; delete requires count>0.
- **Edge case:** count distinguishes full and empty even when front is a valid index in either state.
- **Complexity:** INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 5. Working Principle
count==0 means empty and count==capacity means full. Insert slot is (front+count)%capacity; deletion advances front modulo capacity.

## 6. Algorithm
1. Initialize front=0/count=0. INSERT rejects full, writes at (front+count)%capacity and increments count. DELETE rejects empty, removes at front, wraps front, and decrements count. Display walks count logical entries.

## 7. Program Explanation
queue[] stores physical slots; front/count describe logical order and occupancy. The modulo formulas map logical positions to the array. Display iterates from front for count items, so it remains correct when values wrap around. This avoids Experiment 5's false overflow, but capacity is still fixed.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `circular_queue.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `circular_queue.c`

**Sample input**

```text
1
10
1
20
1
30
2
1
40
3
4
```

**Actual program output**

```text

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 10.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 20.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 30.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Deleted 10.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Enter value to insert: Inserted 40.

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Front to rear: 20 30 40

1. INSERT
2. DELETE
3. Display
4. Exit
Choice: Goodbye.
```

## 10. Dry Run
With capacity 5, insert 10,20,30; front=0/count=3. Delete 10, so front=1/count=2. Insert 40 at (1+2)%5=3. Logical order is 20,30,40.

| Operation | front | count | Order | Slot |\n|---|---:|---:|---|---:|\n| Insert 10,20,30 | 0 | 3 | 10,20,30 | 0,1,2 |\n| Delete 10 | 1 | 2 | 20,30 | - |\n| Insert 40 | 1 | 3 | 20,30,40 | (1+2)%5=3 |

## 11. Time and Space Complexity
INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 12. Advantages and Disadvantages
- **Advantages:** Reuses freed slots without shifting values.
- **Disadvantages:** Fixed capacity and modulo bookkeeping require careful boundary handling.

## 13. Applications
Ring buffers, network/audio buffers, and repeated cyclic scheduling.

## 14. Common Errors
Forgetting modulo; confusing count full with empty; forgetting to update count; printing physical rather than logical order.

## 15. POE Viva Questions and Answers
1. **Q: What is a circular queue?**  
   A: A FIFO queue whose array indexes wrap around after the last slot.
2. **Q: What is the aim of Experiment 6?**  
   A: Reuse array positions by wrapping queue indexes around the fixed array.
3. **Q: What important rule should be preserved?**  
   A: count==0 means empty and count==capacity means full. Insert slot is (front+count)%capacity; deletion advances front modulo capacity.
4. **Q: What precondition must be checked?**  
   A: Insert requires count<CAPACITY; delete requires count>0.
5. **Q: How should the important edge case be handled?**  
   A: count distinguishes full and empty even when front is a valid index in either state.
6. **Q: What is the time and space complexity?**  
   A: INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).
7. **Q: State one advantage.**  
   A: Reuses freed slots without shifting values.
8. **Q: State one limitation.**  
   A: Fixed capacity and modulo bookkeeping require careful boundary handling.
9. **Q: Give one practical application.**  
   A: Ring buffers, network/audio buffers, and repeated cyclic scheduling.
10. **Q: Name a common programming error.**  
   A: Forgetting modulo; confusing count full with empty; forgetting to update count; printing physical rather than logical order.
11. **Q: How does an index wrap around?**  
   A: The remainder operation modulo capacity maps the next slot back into range.
12. **Q: How does this code detect full?**  
   A: When count equals CAPACITY.
13. **Q: Why keep count?**  
   A: It distinguishes full from empty and records how many values are active.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: With capacity 5, insert 10,20,30; front=0/count=3. Delete 10, so front=1/count=2. Insert 40 at (1+2)%5=3. Logical order is 20,30,40.
2. Test the program's edge case: count distinguishes full and empty even when front is a valid index in either state.
3. Explain the central rule without looking at the source: count==0 means empty and count==capacity means full. Insert slot is (front+count)%capacity; deletion advances front modulo capacity.
4. Compare this structure or algorithm with its alternative: It fixes the linear queue's wasted-front-slot problem but does not make storage grow dynamically.
5. Discuss this program's performance: INSERT and DELETE are O(1); display is O(n). Storage is O(CAPACITY).

## 17. Important Exam Points
- Use (front+count)%CAPACITY to insert and (front+1)%CAPACITY to delete
- Display in logical order.
