#include<stdio.h>
#include<stdlib.h>

void printArray(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int partition(int A[], int low, int high) {
    int pivot = A[low];
    int i = low + 1;
    int j = high;
    int temp;

    do {
        while (i <= high && A[i] <= pivot) {
            i++;
        }

        while (j >= low && A[j] > pivot) {
            j--;
        }

        if (i < j) {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    } while (i < j);

    // Swap pivot with A[j]
    temp = A[low];
    A[low] = A[j];
    A[j] = temp;

    return j;
}

void QuickSort(int A[], int low, int high, int size) {
    int partitionIndex;
    if (low < high) {
        partitionIndex = partition(A, low, high);
        printArray(A, size);  // Print intermediate array after partitioning
        QuickSort(A, low, partitionIndex - 1, size);  // Sort left subarray
        QuickSort(A, partitionIndex + 1, high, size); // Sort right subarray
    }
}

int main() {
    int A[] = {3, 5, 6, 7, 56, 45, 35, 2, 33, 1, 0, 99, 200};
    int size_of_array = sizeof(A) / sizeof(A[0]);  // Calculate size of the array

    printf("Original Array:\n");
    printArray(A, size_of_array);

    QuickSort(A, 0, size_of_array - 1, size_of_array);  // Pass array size to QuickSort

    printf("Sorted Array:\n");
    printArray(A, size_of_array);

    return 0;
}
