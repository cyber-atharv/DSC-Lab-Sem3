# Experiment 1 – Array Operations

## 1. Aim
Create an array and perform traversal, insertion, and deletion at a selected position.

## 2. Problem Statement
Write a menu-driven program that creates an integer array, displays its values, inserts an item, and deletes an item.

## 3. Theory
An array stores same-type values in consecutive memory. Its index allows direct access, but middle insertion and deletion require shifting values.

## 4. Important Terminology
- **Array:** A contiguous indexed collection of values of one type.
- **Invariant:** count marks the active prefix values[0..count-1]. Shift right from the end on insertion and shift left from the deleted position on deletion.
- **Precondition:** Insert position is 1..count+1; delete position is 1..count; insertion also needs free capacity.
- **Edge case:** An empty array has count zero. Position 1 is valid for insertion; deletion is invalid.
- **Complexity:** Traversal is O(n); insertion/deletion are O(n) worst case because of shifts. Fixed storage is O(MAX_SIZE), with O(1) extra space.

## 5. Working Principle
count marks the active prefix values[0..count-1]. Shift right from the end on insertion and shift left from the deleted position on deletion.

## 6. Algorithm
1. Read and validate the item count and values
2. Repeatedly show the menu
3. Validate each position
4. Shift and update count for insert/delete
5. Stop on Exit.

## 7. Program Explanation
stdio.h supplies checked console input/output. A fixed integer array provides bounded storage, while count records the live elements. display() handles an empty array. The switch dispatches menu actions and the do-while loop repeats. Insertion walks backward to avoid overwriting data; deletion walks forward. User positions are 1-based, so position-1 is used as the C index.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `array_operations.c`

```c

#include <stdio.h>

#define MAX_SIZE 100

static void display(const int values[], int count)
{
    int index;

    /* A zero count means there are no active array elements to print. */
    if (count == 0) {
        printf("Array is empty.\n");
        return;
    }

    printf("Array: ");
    for (index = 0; index < count; index++) {
        printf("%d%s", values[index], index == count - 1 ? "\n" : " ");
    }
}

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int choice;
    int position;
    int value;
    int index;

    printf("Enter initial number of elements (0-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 0 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }

    printf("Enter %d integer(s):\n", count);
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
    }

    do {
        printf("\n1. Display\n2. Insert\n3. Delete\n4. Exit\nChoice: ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid menu input.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                display(values, count);
                break;
            case 2:
                if (count == MAX_SIZE) {
                    printf("Array is full; insertion is not possible.\n");
                    break;
                }
                printf("Enter 1-based position (1-%d) and value: ", count + 1);
                if (scanf("%d %d", &position, &value) != 2) {
                    fprintf(stderr, "Invalid position or value.\n");
                    return 1;
                }
                if (position < 1 || position > count + 1) {
                    printf("Invalid position.\n");
                    break;
                }
                /* Shift backward so existing values are not overwritten. */
                for (index = count; index >= position; index--) {
                    values[index] = values[index - 1];
                }
                values[position - 1] = value;
                count++;
                printf("Inserted %d.\n", value);
                break;
            case 3:
                if (count == 0) {
                    printf("Array is empty; nothing to delete.\n");
                    break;
                }
                printf("Enter 1-based position to delete (1-%d): ", count);
                if (scanf("%d", &position) != 1) {
                    fprintf(stderr, "Invalid position.\n");
                    return 1;
                }
                if (position < 1 || position > count) {
                    printf("Invalid position.\n");
                    break;
                }
                value = values[position - 1];
                /* Shift forward to close the gap left by the deleted value. */
                for (index = position - 1; index < count - 1; index++) {
                    values[index] = values[index + 1];
                }
                count--;
                printf("Deleted %d.\n", value);
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

### `array_operations.c`

**Sample input**

```text
3
10 20 30
1
2
2 15
1
3
3
1
4
```

**Actual program output**

```text
Enter initial number of elements (0-100): Enter 3 integer(s):

1. Display
2. Insert
3. Delete
4. Exit
Choice: Array: 10 20 30

1. Display
2. Insert
3. Delete
4. Exit
Choice: Enter 1-based position (1-4) and value: Inserted 15.

1. Display
2. Insert
3. Delete
4. Exit
Choice: Array: 10 15 20 30

1. Display
2. Insert
3. Delete
4. Exit
Choice: Enter 1-based position to delete (1-4): Deleted 20.

1. Display
2. Insert
3. Delete
4. Exit
Choice: Array: 10 15 30

1. Display
2. Insert
3. Delete
4. Exit
Choice: Goodbye.
```

## 10. Dry Run
Start [10,20,30]. Insert 15 at position 2: shift 30 right, then 20 right; write 15. Result [10,15,20,30]. Delete position 3: move 30 left; result [10,15,30].

| Action | Values | Count |\n|---|---|---:|\n| Start | 10, 20, 30 | 3 |\n| Insert 15 at 2 | 10, 15, 20, 30 | 4 |\n| Delete position 3 | 10, 15, 30 | 3 |

## 11. Time and Space Complexity
Traversal is O(n); insertion/deletion are O(n) worst case because of shifts. Fixed storage is O(MAX_SIZE), with O(1) extra space.

## 12. Advantages and Disadvantages
- **Advantages:** Simple storage and O(1) direct access by index.
- **Disadvantages:** Fixed capacity; middle updates shift elements.

## 13. Applications
Small fixed-size tables, marks lists, lookup tables, and bounded collections.

## 14. Common Errors
Using a 1-based position directly as a C index; shifting insertion in the wrong direction; forgetting to update count; accessing an empty array.

## 15. POE Viva Questions and Answers
1. **Q: What is a array?**  
   A: A contiguous indexed collection of values of one type.
2. **Q: What is the aim of Experiment 1?**  
   A: Create an array and perform traversal, insertion, and deletion at a selected position.
3. **Q: What important rule should be preserved?**  
   A: count marks the active prefix values[0..count-1]. Shift right from the end on insertion and shift left from the deleted position on deletion.
4. **Q: What precondition must be checked?**  
   A: Insert position is 1..count+1; delete position is 1..count; insertion also needs free capacity.
5. **Q: How should the important edge case be handled?**  
   A: An empty array has count zero. Position 1 is valid for insertion; deletion is invalid.
6. **Q: What is the time and space complexity?**  
   A: Traversal is O(n); insertion/deletion are O(n) worst case because of shifts. Fixed storage is O(MAX_SIZE), with O(1) extra space.
7. **Q: State one advantage.**  
   A: Simple storage and O(1) direct access by index.
8. **Q: State one limitation.**  
   A: Fixed capacity; middle updates shift elements.
9. **Q: Give one practical application.**  
   A: Small fixed-size tables, marks lists, lookup tables, and bounded collections.
10. **Q: Name a common programming error.**  
   A: Using a 1-based position directly as a C index; shifting insertion in the wrong direction; forgetting to update count; accessing an empty array.
11. **Q: Why does insertion shift from right to left?**  
   A: So an old element is not overwritten before it has been copied.
12. **Q: Can an item be inserted at count+1?**  
   A: Yes, that position appends, as long as capacity remains.
13. **Q: What is traversal?**  
   A: Visiting the current elements one by one, usually from index 0 to count-1.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Start [10,20,30]. Insert 15 at position 2: shift 30 right, then 20 right; write 15. Result [10,15,20,30]. Delete position 3: move 30 left; result [10,15,30].
2. Test the program's edge case: An empty array has count zero. Position 1 is valid for insertion; deletion is invalid.
3. Explain the central rule without looking at the source: count marks the active prefix values[0..count-1]. Shift right from the end on insertion and shift left from the deleted position on deletion.
4. Compare this structure or algorithm with its alternative: Arrays provide direct indexing; linked lists avoid shifting but require sequential traversal.
5. Discuss this program's performance: Traversal is O(n); insertion/deletion are O(n) worst case because of shifts. Fixed storage is O(MAX_SIZE), with O(1) extra space.

## 17. Important Exam Points
- Distinguish C's zero-based indexes from the program's 1-based positions
- Check capacity and position before shifting
- Only the active prefix is valid.
