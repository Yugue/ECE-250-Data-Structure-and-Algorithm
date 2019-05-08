
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  y862chen@uwaterloo.ca
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

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

// Constructor
template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

// Destructor
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

// Replace the root with an input
template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}


// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)

// You can modify this function however you want:  it will not be tested


/*           --- Accessors ---            */
// Return true if the heap is empty, false otherwise
template <typename Type>
bool Leftist_heap<Type>::empty() const {
	if (heap_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// Return the number of nodes in the heap
template <typename Type>
int Leftist_heap<Type>::size() const {
	return heap_size;
}

// Returns the null-path length of the root node
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
	return (root_node -> null_path_length());
}

// Return the number of instances of the argument in the heap
template <typename Type>
int Leftist_heap<Type>::count(const Type &obj) const {
	return (root_node -> count(obj));
}

// Return the number at the top of the heap
template <typename Type>
Type Leftist_heap<Type>::top() const {
	if (empty()) {
		throw underflow();
	}
	else {
		return (root_node -> retrieve());
	}
}

/* 			--- Mutators ---			*/
// Insert the new element into the heap 
template <typename Type>
void Leftist_heap<Type>::push(const Type &obj) {				
	Leftist_node<Type> *a;
	a = new Leftist_node<Type>(obj);						// Put the input parameter as a node
		
	a -> push(a, root_node);						// push the new node to the existing tree from the root, root_node as a secondary argument
	heap_size++;
}

// Pop the root node
template <typename Type>
Type Leftist_heap<Type>::pop() {
	if (empty()) {								// If the root node is empty, throw an underflow;
		throw underflow();
	}
	else {
		Leftist_node<Type> *right;								
		Leftist_node<Type> *temp;
		temp = root_node;										// Create a temporary pointer pointing to the node to be deleted
		right = root_node -> right();							// Set the right node pointing to the right branch of the tree
		root_node = root_node -> left();						// Set the left branch as the main tree
		root_node -> push(right, root_node);					// Push the original right branch to the main tree
		
		Type retVal = temp -> retrieve();							
		delete temp;											// Delete the element
		heap_size--;											// Decrease the heap size by 1
		return retVal;											// Return the element in the popped node
	}
}

// Clear the whole tree starting from the root_node;
template <typename Type>
void Leftist_heap<Type>::clear() {
	if (empty()) {											// Return if the function is empty
		return;
	}
	root_node -> Leftist_node<Type>::clear();				// Calling the clear function from Leftist_node 
	heap_size = 0;											// The size becomes 0
}


template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
