#include <iostream>
#include <vector>
#include <omp.h>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void parallelQuickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelQuickSort(arr, low, pivotIndex - 1);
            }
            #pragma omp section
            {
                parallelQuickSort(arr, pivotIndex + 1, high);
            }
        }
    }
}

int main() {
    std::vector<int> arr = {9, 3, 2, 7, 5, 1, 8, 4, 6};

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    parallelQuickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
/* Explantion : 
In this code, the partition function takes an array arr and partitions it based on a pivot element. It rearranges the elements such that all elements smaller than the pivot are placed before it and all elements greater than the pivot are placed after it. The function returns the index of the pivot element.

The parallelQuickSort function implements the parallel QuickSort algorithm using OpenMP. It takes an input array arr, the low and high indices representing the portion of the array to be sorted. It recursively partitions the array and performs parallel QuickSort on the partitions.

Inside the parallelQuickSort function, if the low index is less than the high index, the function calls the partition function to obtain the pivot index. Then, it enters a parallel region using the #pragma omp parallel sections directive.

Within the parallel region, the two recursive calls to parallelQuickSort are performed in separate sections, dividing the work between multiple threads.

The partition operation is not parallelized as it involves modifying the array in a way that can lead to data races. Instead, parallelism is achieved through the divide-and-conquer nature of the QuickSort algorithm.

In the main function, we create an array, print the original array, call the parallelQuickSort function to sort the array in parallel, and then print the sorted array.

When the program runs, it will output the original and sorted arrays. The sorting process is performed in parallel, utilizing the available threads provided by OpenMP. The array is partitioned based on pivot elements and recursively sorted in parallel.

Note that the efficiency of parallel QuickSort depends on the size of the array, the number of available threads, and the pivot selection strategy. Experimentation and profiling can help determine the optimal conditions for achieving better performance.
*/