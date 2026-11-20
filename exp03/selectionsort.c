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
