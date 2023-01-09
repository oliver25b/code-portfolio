// Please add your name below
// Name: Oliver Bartz

// FILE: sorttest2.cpp
// This file tests and compares different sorting algorithms

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "sort.h"
#include "sort.cpp"

using namespace std;

// PROTOTYPES for functions used by main
void print_menu( ); 
char get_user_command( ); 
bool check_ordered(string data[], size_t n);

int main(int argc, char **argv)
{
	int file = atoi(argv[1]);
	string inputfilename = to_string(file);	// input filename
	inputfilename.append(".txt");

	ifstream inputfile(inputfilename); 	// file stream for input text file

	int number = 0;						//number of data to read/sort
	string empty;						//empty string
	inputfile >> number; 				//getting the number to use
	getline(inputfile, empty);			//gets rid of newline issue even though it's kinda dumb
	string data[number]; 				//going to have the strings from the file
	
	for (int i = 0; i < (number); i++){ //reading the rest of the data into data[]
		getline(inputfile, data[i]);
	}
		
	inputfile.close(); 					// close the input file
	
	int choice = atoi(argv[2]);
	
	// Record the start time
	clock_t nStart = clock();

	// call sort function based on user selection
	switch (choice)
    {
		case 1: 
			bubblesort(data, number);
			break;
		case 2:
			selectionsort(data, number);
			break;
        case 3: 
			insertionsort(data, number);
            break;
        case 4: 
			shellsort(data, number);
            break;
        case 5: 
			quicksort(data, number);
            break;
		case 6: 
			mergesort(data, number);
			break;
        default:  
			return -1;
    }
	
	// Record the end time
	clock_t nEnd = clock();

	// Print total execution time for sorting
	cout << (nEnd-nStart)*1.0/CLOCKS_PER_SEC*1000;

	return 0;
}