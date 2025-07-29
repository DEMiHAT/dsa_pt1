#include <stdio.h>


int deleteoccurences(int arr[], int n, int value) {
    int i, j = 0;

    for (i = 0; i < n; i++) {
        if (arr[i] != value) {
            arr[j++] = arr[i];  
        }
    }

    return j;  
}

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int value = 2;

    printf("Original array:\n");
    display(arr, n);

    n = deleteoccurences(arr, n, value);

    printf("Array after deleting all occurrences of %d:\n", value);
    display(arr, n);

    return 0;
}

