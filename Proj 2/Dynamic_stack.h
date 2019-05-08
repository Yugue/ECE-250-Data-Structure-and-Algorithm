/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y862chen @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

// Constructor, default size is 10;
Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	if (array_size < 1) {										// If the input size is less than 1, set it to 1
		array_size = 1;
		initial_size = array_size;
	}
	array = new int[array_size];						// create a interger array of size n
}

// Destructor
Dynamic_stack::~Dynamic_stack() {
	delete[] array;										// delete the whole array
	array_size = 0;										// set the size to 0
	count = 0;											// set the count to the first element				
}

// Return the element on top of the stack
int Dynamic_stack::top() const {
	if (count > 0) {
		return array[(count - 1)];							// return the item previous to the counter		
	}
	else {
		throw underflow();
	}
}

// return the number of elements stored, excluding empty arrays
int Dynamic_stack::size() const {
	return count;										
}

// Check if the stack is empty
bool Dynamic_stack::empty() const {
	if (count > 0) {
		return false;
	}
	else {
		return true;
	}
}

// Return the size of the array
int Dynamic_stack::capacity() const {
	return array_size;
}

// Insert a new item at the head of the array, double the size if full.
void Dynamic_stack::push( int const &obj ) {
	if (count == array_size) {
		int *old_array;	
		old_array = array;											// Create a pointer pointing to the old array
		array = new int [array_size * 2];							// Create a new double-sized empty array if full
		for (int i = 0; i < count; i++) {							// Copy each value
			array[i] = old_array[i];
		}
		array_size = array_size * 2;								// Increase the size by 2 
		array[count] = obj;											// Insert the new value
		delete[] old_array;											// Get rid of the old array;
		count++;													// Move count
	}
	else {
		array[count] = obj;
		count++;
	}
}

// Remove the element at the top of the stack, if empty, error
int Dynamic_stack::pop() {
	if (count > 0) {
		count--;													// Move count back 1 index, values are left out inside the array
		return array[count];										// Return the element on top of the list
	}
	else {
		throw underflow();
	}
}

// Clear the whole stack, reset to initial size
void Dynamic_stack::clear() {
	count = 0;														// Move count to the 0 index
	
	if (array_size != initial_size) {
		int *old_array;		
		old_array = array;											// Create a pointer pointing to the old array
		array = new int [initial_size];								// Create a new array of initial size, no need to copy value, since empty
		array_size = initial_size;
		delete[] old_array;											// delete old array
	}
}
#endif
