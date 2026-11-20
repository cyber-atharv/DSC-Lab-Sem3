
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
