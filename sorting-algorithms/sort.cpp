// Please add your name below
// Name: Oliver Bartz

// FILE: sort.cpp
// Implementation of sorting functions.

#include "sort.h"
#include <cstdlib>
using namespace std;

static
void swap(string & s1, string & s2)	//swaps two strings
{
	string temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}

//////////////// Bubble Sort ////////////////////////////
void bubblesort(string data[ ], size_t n)
{									//(provided by Dr. Chen)
	size_t k = 0;
	bool switched = true;
	while (k < n-1 && switched) 
	{
		switched = false;
		k++;
		for (size_t i = 0; i < n-k; ++i) 
		{
			if (data[i] > data[i+1]) 
			{ 
				swap(data[i], data[i+1]);
				switched = true;
			}
		}
	}
}

//////////////// Selection Sort /////////////////////////
void selectionsort(string data[ ], size_t n)
{
	unsigned int smallest = 0;			//index of smallest string found in the given iteration
	for (unsigned int i = 0; i < (n-1); i++){		//i = iteration # (lowest member of unsorted section)
		smallest = i;					//necessary to avoid a few random missorts
		for (unsigned int s = (i + 1); s < n; s++){	//s = subiteration # (runs through all elements of data[] to compare to i)
			if ((data[i] > data[s]) && (data[s] < data[smallest])){	//case: a new smallest string has been found
				smallest = s;			//update the index of the smallest string
			}
		}
		if (smallest != i){				//if a swap needs to occur
			swap(data[i], data[smallest]);
		}
	}	
}

//////////////// Insertion Sort /////////////////////////
void insertionsort(string data[ ], size_t n)
{
	for (unsigned int u = 1; u < n; u++){//u = index of lowest unsorted element. begins at 1 and holds return location
		int i = u;						//i = index of current element in question
		while ((data[i] < data[i-1])){	//compare i with its predecessor. if it's lower, swap
			swap(data[i], data[i-1]);
			i--;						//continue checking against predecessor until it is higher or equal
			if ((i-1) < 0) break;		//avoids checking against nonexistent data element
		}								//return to i = u+1 to check next element
	}									//complete when u > n	
}

//////////////// Shell Sort ////////////////////////////
void shellsort(string data[ ], size_t n)
{
	for (int k = (n/3); k >= 1; k = (k/2)){				//k is gap value: defines number of shells
		for (int j = 0; j < k; j++){					//j is offset value: switches shell
			for (unsigned int i = (j + k); i < n; i = (i + k)){	//i is current value for sorting
				int u = i;								//u is current value for pushing values down into position
				while ((data[u] < data[u-k])){
					swap(data[u], data[u-k]);
					u = u - k;
					if ((u-k) < 0) break;				//avoids comparison with nonexistent element
				}
			}			
		}
	}
}

////////////////// Quick Sort ///////////////////////////
static
size_t partition(string data[ ], size_t n);

void quicksort(string data[ ], size_t n)
{	
	if (n > 1)
	{
		size_t pivot_index; // Array index for the pivot element
		size_t n1;          // Number of elements before the pivot element
		size_t n2;          // Number of elements after the pivot element
		
		// Partition the array, and set the pivot index
		pivot_index = partition(data, n);

		// Compute the sizes of the subarrays
		n1 = pivot_index + 1;
		n2 = n - n1;

		// Recursive calls to sort the subarrays
		quicksort(data, n1);
		quicksort((data + pivot_index + 1), n2);
	}
}

static
size_t partition(string data[ ], size_t n)
{
	bool complete = false;
	unsigned int i = 0;							//holds low index
	unsigned int j = n-1;						//holds high index
	unsigned int pivot_index = (n/2);			//pivot index
	string pivot_value = data[pivot_index];		//holds pivot value for comparing against

	while(complete == false){
		while ((data[i] < pivot_value)){		//while low value in correct half, increment
			i++;
		}
		while ((data[j] > pivot_value)){		//while high value in correct half, increment
			j--;
		}
		if (j < i){								//if high and low index have swapped, all have been partitioned
			complete = true;
		}
		else{									//two values must be swapped and partitioning continues
			swap(data[i], data[j]);
			i++;
			j--;
		}
	}
	return j;									//returns index of top of lower valued list
}


////////////////// (Top-Down) Merge Sort /////////////////
static
void merge(string data[ ], size_t n1, size_t n2);

void mergesort(string data[ ], size_t n)
{
	if (n > 1)
	{		
		// Compute the sizes of the subarrays
		size_t n1 = n/2;
		size_t n2 = n - n1;

		// Sort two subarrays
		mergesort(data, n1);
		mergesort(data + n1, n2);
		
		// Merge the two sorted halves
		merge(data, n1, n2);
    }
}

static
void merge(string data[ ], size_t n1, size_t n2)
{
	string* s1 = new string[n1];				//holds first half of sorted input
	string* s2 = new string[n2];				//holds second half of sorted input

	for (unsigned int a = 0; a < n1; a++){		//puts data into s1
		s1[a] = data[a];
	}
	for (unsigned int b = 0; b < n2; b++){		//puts data into s2
		s2[b] = data[b + n1];
	}
												//data[] may now be overwritten
	unsigned int i = 0;							//s1 current index
	unsigned int j = 0;							//s2 current index
	
	for (unsigned int k = 0; k < (n1 + n2); k++){//loop until data[] is filled
		if ((i < n1) && (j < n2)){				//if both s1 and s2 are not filled
			if (s1[i] <= s2[j]){				//s1 has lowest value, put into data[]
				data[k] = s1[i];
				i++;
			}
			else {								//s2 has lowest value, put into data[]
				data[k] = s2[j];
				j++;
			}
		}
		else if (i >= n1){						//if s1 has been fully depleted, copy all of s2 into data[]
			data[k] = s2[j];
			j++;
		}
		else {									//if s2 has been fully depleted, copy all of s1 into data[]
			data[k] = s1[i];
			i++;
		}
	}
	delete[] s1;								//avoid memory leak
	delete[] s2;
}
