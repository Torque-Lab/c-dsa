#include <stdio.h>

int binarysearch(int arr[], int size, int element) {
    int low, mid, high;
    low = 0;
    high = size - 1;
    
    while (low <= high) {
        mid = low + (high - low) / 2;
        
        if (arr[mid] == element) {
            return mid;
        } else if (arr[mid] < element) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    return -1; // Element not found
}

int main() {
    int arr[] = {1, 2, 2, 3, 45, 12, 23, 234, 45, 4554, 455, 56, 45, 565, 43};
    int size = sizeof(arr) / sizeof(int);
    int element = 455;
    int search_index = binarysearch(arr, size, element);
    
    if (search_index != -1) {
        printf("The element %d found at index %d\n",search_index);
    } else {
        printf("Element %d not found\n", element);
    }
    
    return 0;
}
