#include <stdio.h>

// Usefull funcions
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}



    /* Selection sort 
    * Selection sort is a simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest) element 
    * from the unsorted portion of the list and moving it to the sorted portion of the list.
    * The algorithm repeatedly selects the smallest (or largest) element from the unsorted portion of the list and swaps it with the first element of the unsorted portion.
    * This process is repeated for the remaining unsorted portion of the list until the entire list is sorted.
    * One variation of selection sort is called “Bidirectional selection sort” which goes through the list of elements by alternating between the smallest and largest element,
    * this way the algorithm can be faster in some cases.
    */
void selectionSort(int arr[], int n) {
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
           if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

    /*
    * Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in the wrong order.
    * This algorithm is not suitable for large data sets as its average and worst-case time complexity is quite high.
    */
void bubbleSort(int arr[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)
 
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

    /*
    *   Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands.
    *   The array is virtually split into a sorted and an unsorted part.
    *   Values from the unsorted part are picked and placed at the correct position in the sorted part.
    *       Characteristics of Insertion Sort:
    *   - This algorithm is one of the simplest algorithm with simple implementation
    *   - Basically, Insertion sort is efficient for small data values
    *   - Insertion sort is adaptive in nature, i.e. it is appropriate for data sets which are already partially sorted.
    */
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

    /*
    *   Merge sort is defined as a sorting algorithm that works by dividing an array into smaller subarrays,
    *   sorting each subarray, and then merging the sorted subarrays back together to form the final sorted array.
    *   In simple terms, we can say that the process of merge sort is to divide the array into two halves, sort each half, and then merge the sorted halves back together.
    *   This process is repeated until the entire array is sorted.
    * 
    *   Merge sort is a popular choice for sorting large datasets because it is relatively efficient and easy to implement.
    *   It is often used in conjunction with other algorithms, such as quicksort, to improve the overall performance of a sorting routine.
    * 
    * 
    *   Merges two subarrays of arr[].
    *   First subarray is arr[l..m]
    *   Second subarray is arr[m+1..r]
    */
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// l is for left index and r is right index of the sub-array of arr to be sorted
void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
 
        merge(arr, l, m, r);
    }
}

    /*
    *   QuickSort is a sorting algorithm based on the Divide and Conquer algorithm
    *   that picks an element as a pivot and partitions the given array around the picked pivot by placing the pivot in its correct position in the sorted array.
    * 
    *   The key process in quickSort is a partition().
    *   The target of partitions is to place the pivot (any element can be chosen to be a pivot) at its correct position in the sorted array
    *   and put all smaller elements to the left of the pivot, and all greater elements to the right of the pivot.
    *   This partition is done recursively which finally sorts the array.
    */
// Partition the array using the last element as the pivot
int partition(int arr[], int low, int high)
{
    // Choosing the pivot
    int pivot = arr[high];
     
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
         
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
             
            // Increment index of smaller element
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
         
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = partition(arr, low, high);
         
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}