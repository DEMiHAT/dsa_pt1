#include <stdio.h>

// Function to display array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to insert an element
int insert(int arr[], int n, int pos, int value) {
    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
    return n + 1;
}

// Function to delete an element
int deleteElement(int arr[], int n, int pos) {
    for (int i = pos; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    return n - 1;
}

int main() {
    int arr[100] = {10, 20, 30, 40, 50};
    int n = 5;

    printf("Original array:\n");
    display(arr, n);

    int posInsert = 2, value = 25;
    n = insert(arr, n, posInsert, value);
    printf("\nAfter insertion of %d at position %d:\n", value, posInsert);
    display(arr, n);

    int posDelete = 3;
    n = deleteElement(arr, n, posDelete);
    printf("\nAfter deletion at position %d:\n", posDelete);
    display(arr, n);

    return 0;
}

