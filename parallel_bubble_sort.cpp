#include <iostream>
#include <vector>
#include <omp.h>

void parallelBubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool sorted = false;

    #pragma omp parallel
    {
        while (!sorted) {
            sorted = true;

            #pragma omp for
            for (int i = 0; i < n - 1; i++) {
                if (arr[i] > arr[i + 1]) {
                    #pragma omp critical
                    {
                        std::swap(arr[i], arr[i + 1]);
                        sorted = false;
                    }
                }
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

    parallelBubbleSort(arr);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
/* 
Explantion : 
In this code, the parallelBubbleSort function implements the parallel bubble sort algorithm using OpenMP. It takes an input array and sorts it in ascending order.

Inside the function, we first initialize a boolean variable sorted to false, which will be used to check if any swap occurs during a pass of the bubble sort.

Next, we enter a parallel region using the #pragma omp parallel directive. Each thread executes a portion of the sorting process.

Within the parallel region, we have a while loop that continues until the array is sorted. In each iteration of the loop, we set sorted to true initially.

Then, we use the #pragma omp for directive to parallelize the outer loop of the bubble sort. Each thread works on a subset of the array, performing the bubble sort operation.

If a thread finds that two adjacent elements are out of order, it enters a critical section using #pragma omp critical. This ensures that only one thread at a time can perform the swap operation, avoiding data races.

After a complete iteration of the loop, each thread checks if any swap occurred during its portion of the array. If a swap occurred, sorted is set to false, indicating that the array is not yet fully sorted.

The while loop continues until all threads observe a fully sorted array, at which point the sorting process is complete.

In the main function, we create an array, print the original array, call the parallelBubbleSort function to sort the array in parallel, and then print the sorted array.

When the program runs, it will output the original and sorted arrays. The sorting process is performed in parallel, utilizing the available threads provided by OpenMP.
*/