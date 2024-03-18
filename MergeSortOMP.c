#include <stdio.h>
#include <stdlib.h>
#include <omp.h> // OpenMP library for parallel programming
#include <time.h>

#define THRESHOLD 1000 // Threshold for using local sorting

// Function to merge two sub-arrays of arr[]
void merge(int arr[], int left, int mid, int right)
{
    //n1 and n2 is to calculate the sizes of two sub-arrays to be merged.
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = (int *)malloc(n1 * sizeof(int));
    int *rightArr = (int *)malloc(n2 * sizeof(int));

    int i;
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];

    int j;
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    //Merging the Two Sub-arrays
    i = 0;
    j = 0;
    int k;
    k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1)

    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
    // Free dynamically allocated memory
    free(leftArr);
    free(rightArr);
}

// Function to perform insertion sort on a sub-array of arr[]
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        // sorting by using insertion sort algorithm
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// Function to perform merge sort on a sub-array of arr[]
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        //mid index is calculated as the average of left and right, using integer arithmetic to prevent overflow.
        int mid = left + (right - left) / 2;

        //THRESHOLD Check for Insertion Sort: 
        if (right - left + 1 <= THRESHOLD)
        {
            insertionSort(arr + left, right - left + 1);
        }
        else
        {
            #pragma omp task //executed in parallel by the OpenMP runtime.
            mergeSort(arr, left, mid);

            #pragma omp task
            mergeSort(arr, mid + 1, right);

            #pragma omp taskwait //used to wait for all the parallel tasks to complete before proceeding to the next step.
            merge(arr, left, mid, right);
        }
    }
}

// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    printf("Sorted Data: ");
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    srand(123456);                                                // Set random seed
    int num_threads[] = {1, 4, 8, 12, 16};                        // Array for thread counts
    int data_sizes[] = {10000, 100000, 500000, 1000000, 2000000}; // Array for data sizes
    printf("Data Size (N) | Num Threads | Execution Time (seconds)\n");
    printf("======================================================\n");
    int i, t;
    for (i = 0; i < 5; i++) // Loop over different data sizes
    {
        int size = data_sizes[i];                     // Current data size
        int *arr = (int *)malloc(size * sizeof(int)); // Array to be sorted
        // Generate random numbers for the array
        int j;
        for (j = 0; j < size; j++)
        {
            arr[j] = rand() % 100000; // Set each element randomly to 0-99999
        }
        for (t = 0; t < 5; t++) // Loop over different thread counts
        {
            double start_time = omp_get_wtime(); // Record start time
            #pragma omp parallel num_threads(num_threads[t]) // Parallel execution with specified thread count
            {
                #pragma omp single                           // Single directive to start parallel execution with one thread
                mergeSort(arr, 0, size - 1); // Perform merge sort in parallel
            }

            double end_time = omp_get_wtime(); // Record end time
            
            // Uncomment printArray function to print data that is already sorted by merge sort.
            //printArray(arr, size);
            //printf("======================================================\n");
	        //printf("Data Size: %d, Thread number: %d\n", size, num_threads[t]);
            //printf("Execution Time (seconds): %lf\n", end_time - start_time);

            // Print execution details (threads, size, and execution time)
            printf("%10d    | %6d      |     %lf\n", size, num_threads[t], end_time - start_time);

            if (num_threads[t] == 16)
            {
                printf("======================================================\n");
            }
        }
        // Free dynamically allocated memory for this data size
        free(arr);
    }

    return 0;
}
merge.txt
6 KB