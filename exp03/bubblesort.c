
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
