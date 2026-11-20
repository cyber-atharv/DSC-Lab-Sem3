# Experiment 3 – Sorting: Bubble, Selection, and Insertion Sort

## 1. Aim
Sort integers in ascending order with three elementary algorithms.

## 2. Problem Statement
Implement Bubble Sort, Selection Sort, and Insertion Sort as separate executable programs.

## 3. Theory
Bubble Sort swaps adjacent out-of-order values, Selection Sort selects the smallest remaining value, and Insertion Sort inserts each next value into a sorted prefix.

## 4. Important Terminology
- **Sorting:** Rearranging values into an order, here ascending numeric order.
- **Invariant:** Each method preserves a different invariant: bubbling moves large values right, selection fixes the next minimum, and insertion keeps the processed prefix sorted.
- **Precondition:** Any valid sequence can be sorted; input need not already be ordered.
- **Edge case:** A one-item sequence is already sorted.
- **Complexity:** All are O(n^2) average/worst. Bubble with early stop and Insertion are O(n) best case. Selection uses O(n^2) comparisons even when sorted. Each uses O(1) extra space.

## 5. Working Principle
Each method preserves a different invariant: bubbling moves large values right, selection fixes the next minimum, and insertion keeps the processed prefix sorted.

## 6. Algorithm
1. Read and validate n values. Run the chosen algorithm's passes: adjacent swaps (Bubble), minimum selection (Selection), or save/shift/insert key (Insertion). Print the final sequence.

## 7. Program Explanation
Each source uses stdio.h, MAX_SIZE storage, and checked input. Nested loops perform comparisons and moves. Bubble Sort resets a swapped flag on each pass and can stop early. Selection Sort stores the minimum index and swaps once per pass. Insertion Sort saves key before shifting larger prefix values.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `bubblesort.c`

```c

#include <stdio.h>

#define MAX_SIZE 100

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int pass;
    int index;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter %d integers: ", count);
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
    }

    /* Each pass moves the largest unsorted value toward the end. */
    for (pass = 0; pass < count - 1; pass++) {
        int swapped = 0;
        for (index = 0; index < count - pass - 1; index++) {
            if (values[index] > values[index + 1]) {
                int temporary = values[index];
                values[index] = values[index + 1];
                values[index + 1] = temporary;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }

    printf("Sorted array: ");
    for (index = 0; index < count; index++) {
        printf("%d%s", values[index], index == count - 1 ? "\n" : " ");
    }
    return 0;
}
```
### `selectionsort.c`

```c
#include <stdio.h>

#define MAX_SIZE 100

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int index;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter %d integers: ", count);
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
    }

    /* Place the smallest remaining value at the start of each suffix. */
    for (index = 0; index < count - 1; index++) {
        int smallest = index;
        int scan;

        for (scan = index + 1; scan < count; scan++) {
            if (values[scan] < values[smallest]) {
                smallest = scan;
            }
        }
        if (smallest != index) {
            int temporary = values[index];
            values[index] = values[smallest];
            values[smallest] = temporary;
        }
    }

    printf("Sorted array: ");
    for (index = 0; index < count; index++) {
        printf("%d%s", values[index], index == count - 1 ? "\n" : " ");
    }
    return 0;
}
```
### `insertionsort.c`

```c

#include <stdio.h>

#define MAX_SIZE 100

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int index;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter %d integers: ", count);
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
    }

    /* Insert each key into the already sorted prefix to its left. */
    for (index = 1; index < count; index++) {
        int key = values[index];
        int previous = index - 1;

        while (previous >= 0 && values[previous] > key) {
            values[previous + 1] = values[previous];
            previous--;
        }
        values[previous + 1] = key;
    }

    printf("Sorted array: ");
    for (index = 0; index < count; index++) {
        printf("%d%s", values[index], index == count - 1 ? "\n" : " ");
    }
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `bubblesort.c`

**Sample input**

```text
5
5 1 4 2 3
```

**Actual program output**

```text
Enter number of elements (1-100): Enter 5 integers: Sorted array: 1 2 3 4 5
```
### `selectionsort.c`

**Sample input**

```text
5
5 1 4 2 3
```

**Actual program output**

```text
Enter number of elements (1-100): Enter 5 integers: Sorted array: 1 2 3 4 5
```
### `insertionsort.c`

**Sample input**

```text
5
5 1 4 2 3
```

**Actual program output**

```text
Enter number of elements (1-100): Enter 5 integers: Sorted array: 1 2 3 4 5
```

## 10. Dry Run
Insertion sort on [5,1,4,2,3]: insert 1 -> [1,5,4,2,3]; insert 4 -> [1,4,5,2,3]; insert 2 -> [1,2,4,5,3]; insert 3 -> [1,2,3,4,5].

| Stage | Array |\n|---|---|\n| Start | 5, 1, 4, 2, 3 |\n| Insert 1 | 1, 5, 4, 2, 3 |\n| Insert 4 | 1, 4, 5, 2, 3 |\n| Insert 2 | 1, 2, 4, 5, 3 |\n| Insert 3 | 1, 2, 3, 4, 5 |

## 11. Time and Space Complexity
All are O(n^2) average/worst. Bubble with early stop and Insertion are O(n) best case. Selection uses O(n^2) comparisons even when sorted. Each uses O(1) extra space.

## 12. Advantages and Disadvantages
- **Advantages:** Easy to trace; Insertion and Bubble are stable in these versions; Insertion performs well on nearly sorted input.
- **Disadvantages:** Quadratic time makes them unsuitable for large data; Selection Sort is not stable here.

## 13. Applications
Small lists, teaching sorting invariants, and nearly sorted short data.

## 14. Common Errors
Losing key during insertion; wrong adjacent indexes; not resetting swapped; assuming Selection Sort has a best-case O(n) comparison count.

## 15. POE Viva Questions and Answers
1. **Q: What is a sorting?**  
   A: Rearranging values into an order, here ascending numeric order.
2. **Q: What is the aim of Experiment 3?**  
   A: Sort integers in ascending order with three elementary algorithms.
3. **Q: What important rule should be preserved?**  
   A: Each method preserves a different invariant: bubbling moves large values right, selection fixes the next minimum, and insertion keeps the processed prefix sorted.
4. **Q: What precondition must be checked?**  
   A: Any valid sequence can be sorted; input need not already be ordered.
5. **Q: How should the important edge case be handled?**  
   A: A one-item sequence is already sorted.
6. **Q: What is the time and space complexity?**  
   A: All are O(n^2) average/worst. Bubble with early stop and Insertion are O(n) best case. Selection uses O(n^2) comparisons even when sorted. Each uses O(1) extra space.
7. **Q: State one advantage.**  
   A: Easy to trace; Insertion and Bubble are stable in these versions; Insertion performs well on nearly sorted input.
8. **Q: State one limitation.**  
   A: Quadratic time makes them unsuitable for large data; Selection Sort is not stable here.
9. **Q: Give one practical application.**  
   A: Small lists, teaching sorting invariants, and nearly sorted short data.
10. **Q: Name a common programming error.**  
   A: Losing key during insertion; wrong adjacent indexes; not resetting swapped; assuming Selection Sort has a best-case O(n) comparison count.
11. **Q: Which algorithms here are stable?**  
   A: Bubble Sort and Insertion Sort, because equal items are not moved past each other.
12. **Q: Which makes at most one swap per outer pass?**  
   A: Selection Sort.
13. **Q: Why can Bubble Sort stop early?**  
   A: A full pass with no swap means the sequence is already ordered.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Insertion sort on [5,1,4,2,3]: insert 1 -> [1,5,4,2,3]; insert 4 -> [1,4,5,2,3]; insert 2 -> [1,2,4,5,3]; insert 3 -> [1,2,3,4,5].
2. Test the program's edge case: A one-item sequence is already sorted.
3. Explain the central rule without looking at the source: Each method preserves a different invariant: bubbling moves large values right, selection fixes the next minimum, and insertion keeps the processed prefix sorted.
4. Compare this structure or algorithm with its alternative: Insertion suits nearly sorted small data; Selection minimizes swaps; Bubble is especially easy to visualize.
5. Discuss this program's performance: All are O(n^2) average/worst. Bubble with early stop and Insertion are O(n) best case. Selection uses O(n^2) comparisons even when sorted. Each uses O(1) extra space.

## 17. Important Exam Points
- Know the invariant of each algorithm
- Save the insertion key before shifting
- Bubble's early stop improves its best case.
