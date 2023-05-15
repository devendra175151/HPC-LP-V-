#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void parallelMergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {9, 3, 2, 7, 5, 1, 8, 4, 6};

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    parallelMergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

/* EXplanation : 

Certainly! Here's an example of a parallel merge sort implementation using OpenMP in C++:

cpp
Copy code
#include <iostream>
#include <vector>
#include <omp.h>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1), rightArr(n2);

    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void parallelMergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> arr = {9, 3, 2, 7, 5, 1, 8, 4, 6};

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    parallelMergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
In this code, the merge function merges two sorted subarrays. It takes an input array arr, the left and right indices representing the subarray boundaries, and the mid index dividing the subarrays. The function merges the subarrays in a sorted manner.

The parallelMergeSort function implements the parallel merge sort algorithm using OpenMP. It takes an input array arr, the left and right indices representing the portion of the array to be sorted. It recursively divides the array into smaller subarrays and performs parallel merge sort on them.

Inside the parallelMergeSort function, if the left index is less than the right index, the function calculates the mid index and enters a parallel region using the #pragma omp parallel sections directive.

Within the parallel region, the two recursive calls to parallelMergeSort are performed in separate sections, dividing the work between multiple threads.

Once the recursive calls are completed, the function calls the merge function to merge the sorted subarrays.

In the main function, we create an array, print the original array, call the parallelMergeSort function to sort the array in parallel
using parallel merge sort, and then print the sorted array.

When the program runs, it will output the original and sorted arrays. The sorting process is performed in parallel, utilizing the available threads provided by OpenMP. The array is divided into smaller subarrays, sorted individually in parallel, and then merged to obtain the final sorted array.

Note that the merge function is a sequential implementation, as merging is a difficult operation to parallelize efficiently. Parallelism is primarily achieved in the divide-and-conquer nature of the merge sort algorithm.

It's worth mentioning that the efficiency of parallel merge sort heavily depends on the size of the array and the number of available threads. In some cases, the overhead of creating and synchronizing threads may outweigh the benefits of parallelism for smaller arrays. Experimentation and profiling can help determine the optimal conditions for achieving better performance.






*/