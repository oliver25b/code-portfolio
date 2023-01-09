// Please add your name below
// Name: Oliver Bartz

// FILE: sorttest2.cpp
// This file tests and compares different sorting algorithms

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include "sort.h"
#include "sort.cpp"

using namespace std;

// PROTOTYPES for functions used by main
void print_menu( ); 
char get_user_command( ); 
bool check_ordered(string data[], size_t n);

int main()
{
	string inputfilename; 				// input filename
	cout << "Please specify the file with data to be sorted: ";
	getline(cin, inputfilename);

	ifstream inputfile(inputfilename); 	// file stream for input text file

	assert(inputfile);					// assert no file open errors
	
	int number = 0;						//number of data to read/sort
	string empty;						//empty string
	inputfile >> number; 				//getting the number to use
	getline(inputfile, empty);			//gets rid of newline issue even though it's kinda dumb
	string data[number]; 				//going to have the strings from the file
	
	for (int i = 0; i < (number); i++){ //reading the rest of the data into data[]
		getline(inputfile, data[i]);
	}
		
	inputfile.close(); 					// close the input file
	
	print_menu( ); 						// print menu
	char choice = get_user_command( ); 	// get user selection
	
	// Record the start time
	clock_t nStart = clock();

	// call sort function based on user selection
	switch (choice)
    {
		case '1': 
			bubblesort(data, number);
			break;
		case '2':
			selectionsort(data, number);
			break;
        case '3': 
			insertionsort(data, number);
            break;
        case '4': 
			shellsort(data, number);
            break;
        case '5': 
			quicksort(data, number);
            break;
		case '6': 

			mergesort(data, number);
			break;
        default:  
			cerr << choice << " is invalid. Sorry." << endl;
			return 1;
    }
	
	// Record the end time
	clock_t nEnd = clock();

	// Print out total execution time for sorting
	cout << "Time elapsed: " << (nEnd-nStart)*1.0/CLOCKS_PER_SEC*1000 << " msec.\n";
	
		
	if (!check_ordered(data, number)) return 1; 	// Check if words array is sorted	
	
	cout << "Please specify a file name to hold the sorted data: ";
	string outputfilename;  						// output filename
	cin.ignore();
	getline(cin, outputfilename); 
	ofstream outputfile(outputfilename); 			// file stream for output text file
 	
	for (int i = 0; i < number; i++){				//write output strings to file
		outputfile << data[i];
		if (i < (number - 1) ) outputfile << "\n";	//avoids empty line at the end of outputfile
	}
	
	outputfile.close(); 							// close the output file
	return 0;
}

// Print menu choices to cout
void print_menu( )
{
	cout << endl; // Print blank line before the menu
	cout << "The following choices are available: " << endl;
	cout << " 1   Run bubblesort" << endl;
	cout << " 2   Run selectionsort" << endl;
	cout << " 3   Run insertionsort" << endl;
	cout << " 4   Run shellsort" << endl;
	cout << " 5   Run quicksort" << endl;
	cout << " 6   Run mergesort" << endl;
}

// Get user menu selection from cin
char get_user_command( )
{
	char command;

	cout << "Enter choice: ";
	cin >> command; // Input of characters skips blanks and newline character

	return command;
}

// Check whether a string array is sorted and print result
bool check_ordered(string data[], size_t n)
{
	for (unsigned int i = 0; i < (n - 1); i++) {
		if (data[i] > data[i + 1]){
//			cout << "Error: not sorted at line " << (i + 1) << "\n";
			return false;
		}
	}
	return true;
}
