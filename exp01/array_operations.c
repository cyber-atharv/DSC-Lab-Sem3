
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
