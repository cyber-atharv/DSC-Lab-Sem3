# Experiment 4 – Stack Using an Array

## 1. Aim
Implement PUSH, POP, and display with overflow and underflow checks.

## 2. Problem Statement
Build a fixed-capacity array stack supporting PUSH, POP, and display.

## 3. Theory
A stack is a LIFO structure: the last value pushed is the first value popped. Both operations use the top end.

## 4. Important Terminology
- **Stack:** A linear collection that removes the most recently inserted item first.
- **Invariant:** top=-1 means empty. PUSH checks top==capacity-1 before adding. POP checks top==-1 before reading and decrementing.
- **Precondition:** PUSH requires space; POP requires a non-empty stack.
- **Edge case:** top=-1 is empty; top=CAPACITY-1 is full.
- **Complexity:** PUSH and POP are O(1); display is O(n). Storage is O(CAPACITY).

## 5. Working Principle
top=-1 means empty. PUSH checks top==capacity-1 before adding. POP checks top==-1 before reading and decrementing.

## 6. Algorithm
1. Initialize top=-1. Repeat the menu. PUSH checks full, reads a value, then stores at ++top. POP checks empty, prints stack[top], and decrements. Display scans from top down.

## 7. Program Explanation
stdio.h handles console interaction. stack is a fixed integer array and top is the last occupied index. The switch selects an operation and the do-while repeats. Checks precede array access, preventing overflow and underflow. No dynamic memory is needed.

In each listing, local variables hold the current data and control state. Input checks happen before values are used. Loops perform repeated operations or traversal, and conditions select success, failure, and boundary cases. Where helper functions are used, they isolate operations; where pointers are used, links are updated before memory is released.

## 8. Complete C Code
These complete programs are included verbatim from the source files in this folder.

### `stack_array.c`

```c
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
```

## 9. Sample Input and Output
The examples below were executed with GCC; the output is captured from the matching executable.

### `stack_array.c`

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
Start top=-1. PUSH 10 gives top=0; PUSH 20 gives top=1. Display prints 20 then 10. POP returns 20 and changes top to 0.

| Action | Bottom-to-top | top |\n|---|---|---:|\n| Start | empty | -1 |\n| PUSH 10 | 10 | 0 |\n| PUSH 20 | 10, 20 | 1 |\n| POP | 10 | 0 |

## 11. Time and Space Complexity
PUSH and POP are O(1); display is O(n). Storage is O(CAPACITY).

## 12. Advantages and Disadvantages
- **Advantages:** Simple constant-time insertion and removal at the top.
- **Disadvantages:** Capacity is fixed and only the newest item is directly accessible.

## 13. Applications
Function calls, undo history, expression evaluation, and backtracking.

## 14. Common Errors
Initializing top to zero; checking full after writing; reading stack[-1]; decrementing before saving the popped value.

## 15. POE Viva Questions and Answers
1. **Q: What is a stack?**  
   A: A linear collection that removes the most recently inserted item first.
2. **Q: What is the aim of Experiment 4?**  
   A: Implement PUSH, POP, and display with overflow and underflow checks.
3. **Q: What important rule should be preserved?**  
   A: top=-1 means empty. PUSH checks top==capacity-1 before adding. POP checks top==-1 before reading and decrementing.
4. **Q: What precondition must be checked?**  
   A: PUSH requires space; POP requires a non-empty stack.
5. **Q: How should the important edge case be handled?**  
   A: top=-1 is empty; top=CAPACITY-1 is full.
6. **Q: What is the time and space complexity?**  
   A: PUSH and POP are O(1); display is O(n). Storage is O(CAPACITY).
7. **Q: State one advantage.**  
   A: Simple constant-time insertion and removal at the top.
8. **Q: State one limitation.**  
   A: Capacity is fixed and only the newest item is directly accessible.
9. **Q: Give one practical application.**  
   A: Function calls, undo history, expression evaluation, and backtracking.
10. **Q: Name a common programming error.**  
   A: Initializing top to zero; checking full after writing; reading stack[-1]; decrementing before saving the popped value.
11. **Q: Why initialize top to -1?**  
   A: No array index is occupied when the stack starts empty.
12. **Q: When does overflow occur?**  
   A: When top is already CAPACITY-1 and another PUSH is requested.
13. **Q: What does POP remove?**  
   A: The current top, which is the most recently pushed value.

## 16. Practice Questions
1. Trace the main operation for the small example in the dry run: Start top=-1. PUSH 10 gives top=0; PUSH 20 gives top=1. Display prints 20 then 10. POP returns 20 and changes top to 0.
2. Test the program's edge case: top=-1 is empty; top=CAPACITY-1 is full.
3. Explain the central rule without looking at the source: top=-1 means empty. PUSH checks top==capacity-1 before adding. POP checks top==-1 before reading and decrementing.
4. Compare this structure or algorithm with its alternative: A stack is LIFO; a queue is FIFO.
5. Discuss this program's performance: PUSH and POP are O(1); display is O(n). Storage is O(CAPACITY).

## 17. Important Exam Points
- Remember LIFO
- Check full and empty before indexing
- Print from top downward to show stack order.
