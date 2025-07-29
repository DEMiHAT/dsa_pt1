#include <stdio.h> 

void reversing(int arr[], int n) {
	int start = 0;
	int end = n - 1; 

	while (start < end) { 
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;

		start ++;
		end--;

	}
}
void display(int arr[], int n) { 
	for (int i = 0; i < n; i++) { 
		printf("%d ", arr[i]); 
	}
	printf("\n"); 
}
int main() { 
	int arr[] = {10,20,30,40,50};
	int n = sizeof(arr) / sizeof(arr[0]);

	printf("Original Array: \n");
	display(arr, n); 
	reversing(arr, n); 

	printf("Reversed Array:\n");
	display(arr, n);

	return 0;
}
	
