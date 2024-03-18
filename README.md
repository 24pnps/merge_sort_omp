# Parallel Merge Sort via OpenMP
This project is a team project for the ITCS443 Parallel and Distributed Systems course. We implement sorting algorithms, specifically merge sort, using parallel programming with OpenMP.

## Table of contents
* [Prerequisites](#prerequisites)
* [Installation steps](#installation-steps)
* [Compilation and Execution](#compilation-and-execution)

## Prerequisites
1. Using PuTTY(on Windows) to Run the Program:
    - Ensure that you have PuTTY installed on your computer.

## Installation steps
1. Download the `merge_sort_omp.zip`
2. Locate the `merge_sort_omp.zip` file in the directory where it was downloaded.
3. Right-click on the file and select "Extract" or "Extract Here" from the context menu, depending on your operating system.
4. The file will be extracted and its contents will be available in the same directory or a specified extraction location.
5. Log in to both PuTTY and WinSCP.
6. Drag the extracted `MergeSortOMP.c` file into WinSCP.
7. Open PuTTY to run it.
8. Type the following commands to change the directory to the `merge_sort_omp` folder:
    `$ cd Downloads`  # This step depends on where you have the files extracted.
    `$ cd merge_sort_omp`

## Compilation and Execution
1. The source code is located in the MergeSortOMP.c file.
    - Compile it with the GCC compiler and enable OpenMP support using the `-fopenmp` flag:
    `$ gcc -o -fopenmp MergeSortOMP MergeSortOMP.c`

2. Run the Merge Sort Algorithm:
    - Execute the compiled program by running the following command:
    `$ ./MergeSortOMP`

3. View the Results
    - After executing the program, the results of the parallel merge sort will be displayed in the terminal.
    
