// Author: Joshua Matni
// CS 302 Hw 5
// Purpose: Implementing different sorting algorithms

#include <iostream>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <chrono> // for run times
#include <cstring> // for memcpy()
#include <string> // for to_string() 
using namespace std;
#include "metrics.h"

#define NUM_RUNS 10
#define SIZE1 1000
#define SIZE2 10000
#define SIZE3 100000

void generateRandomNumbers(int [], int);
void bubble_sort(int [], int, Metrics&);
void merge_sort(int [], int, int, Metrics&);
void insertion_sort(int arr[], int size, Metrics& metrics);
void writeToFile(const string& algorithm, int size, Metrics unsortedMetrics[], Metrics sortedMetrics[]);

int main()
{
    int sizes[] = {SIZE1, SIZE2, SIZE3};
    string algorithms[] = {"bubble", "merge", "insertion"};

    // range based loop (referenced from stackOverflow) for algorithm in algorithms[]
    for(string& algorithm : algorithms)
    {
        for(int size : sizes) // for size in sizes
        {
            // allocate memory for the random and sorted arrays
            int* arr = new int[size];
            int* sortedArr = new int[size];
            Metrics unsortedMetrics[NUM_RUNS], sortedMetrics[NUM_RUNS];

            generateRandomNumbers(arr, size);

            // create a copy of the random array to be sorted
            memcpy(sortedArr, arr, sizeof(int) * size); // from stackOverflow

            // sort the copied array using the selected algorithm
            Metrics sortMetrics;
            if(algorithm == "bubble")
            {
                bubble_sort(sortedArr, size, sortMetrics);
            } 
            else if(algorithm == "merge") 
            {
                merge_sort(sortedArr, 0, size - 1, sortMetrics);
            } 
            else if(algorithm == "insertion") 
            {
                insertion_sort(sortedArr, size, sortMetrics);
            }

            // perform multiple runs for each algorithm on both unsorted and sorted data
            for(int i = 0; i < NUM_RUNS; i++) 
            {
                // create a temp copy of the unsorted array for sorting
                int* tempArr = new int[size];
                memcpy(tempArr, arr, sizeof(int) * size); // from stackOverflow
                auto start = chrono::high_resolution_clock::now();

                if (algorithm == "bubble") 
                {
                    bubble_sort(tempArr, size, unsortedMetrics[i]);
                } 
                else if(algorithm == "merge") 
                {
                    merge_sort(tempArr, 0, size - 1, unsortedMetrics[i]);
                } 
                else if(algorithm == "insertion") 
                {
                    insertion_sort(tempArr, size, unsortedMetrics[i]);
                }

                auto stop = chrono::high_resolution_clock::now();
                unsortedMetrics[i].runTime = chrono::duration_cast<chrono::microseconds>(stop - start).count();

                delete[] tempArr;

                // create a temp copy of the sorted array for sorting
                tempArr = new int[size];
                memcpy(tempArr, sortedArr, sizeof(int) * size); // from stackOverflow
                start = chrono::high_resolution_clock::now();

                if (algorithm == "bubble") 
                {
                    bubble_sort(tempArr, size, sortedMetrics[i]);
                } 
                else if (algorithm == "merge") 
                {
                    merge_sort(tempArr, 0, size - 1, sortedMetrics[i]);
                } 
                else if (algorithm == "insertion") 
                {
                    insertion_sort(tempArr, size, sortedMetrics[i]);
                }

                // record the stop time and calculate the runtime
                stop = chrono::high_resolution_clock::now(); 
                sortedMetrics[i].runTime = chrono::duration_cast<chrono::microseconds>(stop - start).count();

                delete[] tempArr;
            }

            writeToFile(algorithm, size, unsortedMetrics, sortedMetrics);
            delete[] arr;
            delete[] sortedArr;
        }
    }

    return 0;
}

void generateRandomNumbers(int arr[], int size) // from geeks4geeks
{
    srand(time(0)); // seed the random number generator

    for (int i = 0; i < size; i++) 
    {
        arr[i] = rand() % 1000001; // generate a random number between 0 and 1,000,000
    }
}

void bubble_sort(int arr[NUM_RUNS], int size, Metrics& metrics)
{
    bool swapped; 

    for(int i = 0; i < size - 1; i++) // -1 b/c comparing with next element
    {
        swapped = false; // reset for each outer loop iteration

        for(int j = 0; j < size - i - 1; j++) // size - i - 1 b/c last i elements are already in place
        {
            metrics.comparisons++;
            if(arr[j] > arr[j+1]) // compare element to the right
            {
                int temp = arr[j]; // c=a
                arr[j] = arr[j+1]; // a=b
                arr[j+1] = temp; // b=c

                metrics.swaps++;
                swapped = true;
            }
        }

        if(!swapped) // case for if no elements were swapped in inner loop --> array is sorted
        {
            break;
        }
    }
}

void merge_sort(int arr[], int left, int right, Metrics& metrics)
{
    // base case
    if(left >= right)
    {
        return;
    }

    // get middle point to divide array
    int middle = left + (right - left) / 2;

    // sort first half
    merge_sort(arr, left, middle, metrics);

    // sort second half
    merge_sort(arr, middle+1, right, metrics);

    // merging process
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int leftArr[n1], rightArr[n2];

    // copy data to temp arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[middle + 1 + j];

    // merge temp arrays back into arr[left to right]
    int i = 0, j = 0;
    int k = left;

    while((i < n1) && (j < n2)) 
    {
        metrics.comparisons++;
        if(leftArr[i] <= rightArr[j]) 
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

    // copy the remaining elements of lef and right arr, if any
    while(i < n1) 
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while(j < n2) 
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void insertion_sort(int arr[], int size, Metrics& metrics) 
{
    for(int i = 1; i < size; i++) 
    {
        int key = arr[i];
        int j = i - 1;

        // move elements of arr[0 to i-1] that are greater than key
        // to one position ahead of their current position
        metrics.comparisons++;  // initial comparison in loop
        while((j >= 0) && (arr[j] > key))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            metrics.swaps++;  // for each shift operation
            
            if(j >= 0) 
            {
                metrics.comparisons++;  // case for following comparisons in loop
            }
        }
        arr[j + 1] = key;
    }
}


void writeToFile(const string& algorithm, int size, Metrics unsortedMetrics[], Metrics sortedMetrics[])
{
    string filename = algorithm + to_string(size) + ".csv"; 
    ofstream outFile(filename);

    if(!outFile.is_open())
    {
        cout << "Could not open " << filename << endl;
        return;
    }

    // headers
    outFile << "Run Time,Comparisons,Swaps" << endl;

    // unsorted metrics
    outFile << "Unsorted,," << endl;
    for(int i = 0; i < NUM_RUNS; i++)
    {
        outFile << unsortedMetrics[i].runTime << "," << unsortedMetrics[i].comparisons << "," << unsortedMetrics[i].swaps << endl;
    }

    // sorted metrics
    outFile << "Sorted,," << endl;
    for(int i = 0; i < NUM_RUNS; i++)
    {
        outFile << sortedMetrics[i].runTime << "," << sortedMetrics[i].comparisons << "," << sortedMetrics[i].swaps << endl;
    }

    outFile.close();
}