#include <stdio.h>

int insert(int arr[], int n, int pos, int value) {
    if (pos < 0 || pos > n) {
        printf("Invalid position!\n");
        return n;
    }

    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1]; 
    }

    arr[pos] = value;
    return n + 1; 
}

void display(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[100] = {10, 20, 30, 40, 50}; 
    int n = 5; 

    printf("Original array:\n");
    display(arr, n);

    int value = 25;
    int pos = 2;  

    n = insert(arr, n, pos, value);

    printf("After inserting %d at position %d:\n", value, pos);
    display(arr, n);

    return 0;
}

