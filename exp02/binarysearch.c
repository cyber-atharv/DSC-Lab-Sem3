
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
