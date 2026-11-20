
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
