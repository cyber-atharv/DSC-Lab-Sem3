# Experiment 2 – Searching: Linear and Binary Search

## 1. Aim
Locate a key with linear search or binary search and report its position.

## 2. Problem Statement
Implement linear search for any array and binary search for sorted data.

## 3. Theory
Linear search checks values in order and needs no sorted input. Binary search compares the middle value and discards half the remaining sorted range.

## 4. Important Terminology
- **Search:** Finding whether a key is in a collection and where it occurs.
- **Invariant:** Linear search stops at a match or end. Binary search maintains an inclusive low/high range, calculates its midpoint, and moves one bound after each comparison.
- **Precondition:** Binary search requires sorted values; linear search has no ordering precondition.
- **Edge case:** A missing key ends at the end of linear input or when low becomes greater than high.
- **Complexity:** Linear search best O(1), worst O(n). Binary search best O(1), worst O(log n). Both use O(1) extra space; sorting cost is not included.

## 5. Working Principle
Linear search stops at a match or end. Binary search maintains an inclusive low/high range, calculates its midpoint, and moves one bound after each comparison.

## 6. Algorithm
1. Read a bounded array and key. For linear search, inspect each item. For binary search, validate non-decreasing order, set low=0/high=n-1, repeatedly compare the midpoint, and stop on a match or empty range.

## 7. Program Explanation
The two independent files use stdio.h, a bounded integer array, and checked scanf calls. Linear search returns immediately on its first match. Binary search rejects unsorted input, uses an overflow-safe midpoint expression, and updates low or high so the range shrinks. Both convert a zero-based index to a 1-based displayed position.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `linearsearch.c`

```c

#include <stdio.h>

#define MAX_SIZE 100

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int key;
    int index;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter %d elements: ", count);
    /* Check every item because the input does not need to be sorted. */
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
    }
    printf("Enter value to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid search value.\n");
        return 1;
    }

    for (index = 0; index < count; index++) {
        if (values[index] == key) {
            printf("%d found at position %d.\n", key, index + 1);
            return 0;
        }
    }

    printf("%d was not found.\n", key);
    return 0;
}
```
### `binarysearch.c`

```c

#include <stdio.h>

#define MAX_SIZE 100

int main(void)
{
    int values[MAX_SIZE];
    int count;
    int key;
    int index;
    int low;
    int high;

    printf("Enter number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &count) != 1 || count < 1 || count > MAX_SIZE) {
        fprintf(stderr, "Invalid number of elements.\n");
        return 1;
    }
    printf("Enter %d elements in non-decreasing order: ", count);
    for (index = 0; index < count; index++) {
        if (scanf("%d", &values[index]) != 1) {
            fprintf(stderr, "Invalid array element.\n");
            return 1;
        }
        if (index > 0 && values[index] < values[index - 1]) {
            fprintf(stderr, "Input must be sorted in non-decreasing order.\n");
            return 1;
        }
    }
    printf("Enter value to search: ");
    if (scanf("%d", &key) != 1) {
        fprintf(stderr, "Invalid search value.\n");
        return 1;
    }

    low = 0;
    high = count - 1;
    /* Each comparison discards half of the remaining sorted range. */
    while (low <= high) {
        int middle = low + (high - low) / 2;

        if (values[middle] == key) {
            printf("%d found at position %d.\n", key, middle + 1);
            return 0;
        }
        if (values[middle] < key) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }

    printf("%d was not found.\n", key);
    return 0;
}
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `linearsearch.c`

**Sample input**

```text
5
12 5 8 20 7
8
```

**Actual program output**

```text
Enter number of elements (1-100): Enter 5 elements: Enter value to search: 8 found at position 3.
```
### `binarysearch.c`

**Sample input**

```text
5
2 4 6 8 10
8
```

**Actual program output**

```text
Enter number of elements (1-100): Enter 5 elements in non-decreasing order: Enter value to search: 8 found at position 4.
```

## 10. Dry Run
For [2,4,6,8,10], search 8: low=0/high=4, middle=2 gives 6, so keep the right half. Next middle=3 gives 8; it is found at position 4.

| Step | low | high | middle | Value | Action |\n|---:|---:|---:|---:|---:|---|\n| 1 | 0 | 4 | 2 | 6 | Keep right half |\n| 2 | 3 | 4 | 3 | 8 | Found at position 4 |

## 11. Time and Space Complexity
Linear search best O(1), worst O(n). Binary search best O(1), worst O(log n). Both use O(1) extra space; sorting cost is not included.

## 12. Advantages and Disadvantages
- **Advantages:** Linear search is simple; binary search is fast for large sorted arrays.
- **Disadvantages:** Linear search may inspect every item; binary search requires sorted random-access data.

## 13. Applications
Searching IDs, sorted indexes, dictionaries, and small unsorted lists.

## 14. Common Errors
Using binary search on unsorted values; incorrect inclusive bounds; not shrinking the range; confusing index and displayed position.

## 15. POE Viva Questions and Answers
1. **Q: What is a search?**  
   A: Finding whether a key is in a collection and where it occurs.
2. **Q: What is the aim of Experiment 2?**  
   A: Locate a key with linear search or binary search and report its position.
3. **Q: What important rule should be preserved?**  
   A: Linear search stops at a match or end. Binary search maintains an inclusive low/high range, calculates its midpoint, and moves one bound after each comparison.
4. **Q: What precondition must be checked?**  
   A: Binary search requires sorted values; linear search has no ordering precondition.
5. **Q: How should the important edge case be handled?**  
   A: A missing key ends at the end of linear input or when low becomes greater than high.
6. **Q: What is the time and space complexity?**  
   A: Linear search best O(1), worst O(n). Binary search best O(1), worst O(log n). Both use O(1) extra space; sorting cost is not included.
7. **Q: State one advantage.**  
   A: Linear search is simple; binary search is fast for large sorted arrays.
8. **Q: State one limitation.**  
   A: Linear search may inspect every item; binary search requires sorted random-access data.
9. **Q: Give one practical application.**  
   A: Searching IDs, sorted indexes, dictionaries, and small unsorted lists.
10. **Q: Name a common programming error.**  
   A: Using binary search on unsorted values; incorrect inclusive bounds; not shrinking the range; confusing index and displayed position.
11. **Q: Why must binary-search input be sorted?**  
   A: Sorted order tells the program which half cannot contain the key.
12. **Q: What does low<=high mean?**  
   A: There is still at least one candidate index to inspect.
13. **Q: Does this binary search guarantee the first duplicate?**  
   A: No. It reports a matching occurrence, which may not be the first.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: For [2,4,6,8,10], search 8: low=0/high=4, middle=2 gives 6, so keep the right half. Next middle=3 gives 8; it is found at position 4.
2. Test the program's edge case: A missing key ends at the end of linear input or when low becomes greater than high.
3. Explain the central rule without looking at the source: Linear search stops at a match or end. Binary search maintains an inclusive low/high range, calculates its midpoint, and moves one bound after each comparison.
4. Compare this structure or algorithm with its alternative: Binary search reduces comparisons but is not valid for unsorted input.
5. Discuss this program's performance: Linear search best O(1), worst O(n). Binary search best O(1), worst O(log n). Both use O(1) extra space; sorting cost is not included.

## 17. Important Exam Points
- Linear search works on unsorted values
- Binary search needs sorted values
- Update inclusive bounds so the search range always shrinks.
