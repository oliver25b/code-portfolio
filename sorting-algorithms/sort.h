// FILE: sort.h 
// PROTOTYPES for sort functions

#ifndef SORT_H
#define SORT_H

#include <string> 
#include <cstdlib>

using namespace std;

// The following functions sort elements of data in ascending order 
// i.e., data[0] <= data[1] <= ... <= data[n-1]

void bubblesort(string data[ ], size_t n);
void selectionsort(string data[ ], size_t n);
void insertionsort(string data[ ], size_t n);
void shellsort(string data[ ], size_t n);
void quicksort(string data[ ], size_t n);
void mergesort(string data[ ], size_t n);

#endif
