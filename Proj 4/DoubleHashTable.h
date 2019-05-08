#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  y862chen
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

// Constructor
template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

// Destructor
template<typename T>
DoubleHashTable<T >::~DoubleHashTable() {
	delete[] array;									// delete the whole array
	delete[] array_state;								// delete the whole state array
	count = 0;										// set the count to 0
	array_size = 0;									// set the array_size to 0
}

// Return the number of elements currently stored in the hash table
template<typename T >
int DoubleHashTable<T >::size() const {
   return (count);									
}

// Return the number of bins in the hash table
template<typename T >
int DoubleHashTable<T >::capacity() const {
    return (array_size);
}

// Return true if the hash table is empty, false otherwise
template<typename T >
bool DoubleHashTable<T >::empty() const {
    if (count == 0) {
    	return true;
	}
    else {
    	return false;
	}
}

// h1 hash function: determine the position in the array where the obj should go
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int position, i;
	i = static_cast<int>(obj);								// Converting the input into an integer, otherwise static_cast function cannot be used											
	position = i % array_size;								// position of the object is the remainder of obj divideded by the array size
	if (position < 0) {
		position += array_size;								// add array size if position is a negative value
		return (position);									// return the position
	}
	else {
		return (position);
	}
}

// h2 hash function: determine the jump size of the function 
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int i, jump;
	i = static_cast<int>(obj);								// Convert the object to an integer
	jump = (static_cast<int>(i/array_size)) % array_size;		// apply the module fo the object / M
	if (jump < 0){
		jump += array_size;									// add M if the jump if it is negative
	}
	if (jump % 2 == 0) {
		jump ++;											// Add 1 to the jump if it is odd
	}
	return jump;
}

// Return true if obj is in the hash table, false otherwise
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int position, jump, old_position;
	old_position = h1(obj);
	position = h1(obj);
	jump = h2(obj);
	
	do {
		if (array_state[position] == EMPTY) {			// If one bin is found empty, it means the object is not found, otherwise the object could have been inserted there
			return false;
		}
		if (array_state[position] == DELETED) {
			position += jump;												// Everytime, the position is increased by "jump" if not found
		
			if (position >= array_size) {									// if the increased position is outside of M, subtract M to bring it back to the array
				position -= array_size;
			}
		}
		else {
			if (array[position] == obj) {									// If the object is found in the array, return true				
				return true;
			}
			
			position += jump;												// Everytime, the position is increased by "jump" if not found
			
			if (position >= array_size) {									// if the increased position is outside of M, subtract M to bring it back to the array
				position -= array_size;
			}
		}
	} while (position != old_position);
	return false;														
}																		

// Return the entry in bin n
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    if (array_state[n] != OCCUPIED) {									// If the bin is not filled, error
    	throw underflow();
	}
	return (array[n]);
}

// Insert the new object
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
		
	int old_position, position, jump;
	old_position = h1(obj);
	position = h1(obj);
	jump = h2(obj);
	
	do {
		if (array_state[position] != OCCUPIED ) {						// if the bin is not occupied	
			array[position] = obj;										// insert the obj to the bin
			array_state[position] = OCCUPIED;							// change the status to occupied
			count++;													// increase the count by 1
			return;														// no need of doing the rest
		}
		position += jump;												// increase the position by jump
		if (position >= array_size) {									// if position exceeds M, substract M to bring it back to the array
			position -= array_size;
		}
	} while (position != old_position);									// if the position comes back to the old position, it means that a whole traverse of the array has been made
																		// and all bins were occupied, throw underflow
	throw overflow();	
}

// Remove the obj from the hash table
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	int position, jump, old_position;
	old_position = h1(obj);
	position = h1(obj);
	jump = h2(obj);
	
	do {
		if (array_state[position] == EMPTY) {			// If one bin is found empty, it means the object is not found, otherwise the object could have been inserted there
			return false;
		}
		if (array_state[position] == DELETED) {
			position += jump;												// Everytime, the position is increased by "jump" if not found
		
			if (position >= array_size) {									// if the increased position is outside of M, subtract M to bring it back to the array
				position -= array_size;
			}
		}
		else {
			if (array[position] == obj) {									// If the object is found in the array, return true				
				array_state[position] = DELETED;							// Update the state of the bin to deleted
				count --;													// Update the count of the array
				return true;
			}
			
			position += jump;												// Everytime, the position is increased by "jump" if not found
			
			if (position >= array_size) {									// if the increased position is outside of M, subtract M to bring it back to the array
				position -= array_size;
			}
		}
	} while (position != old_position);
	return false;														
}																		
 
// Remove all the elements in the hash table
template<typename T >
void DoubleHashTable<T >::clear() {
	for ( int i = 0; i < array_size; ++i ) {							// Update every bin status to empty
		array_state[i] = EMPTY;
	}
	count = 0;															// update the count to 0
}

// Print the whole array
template<typename T >
void DoubleHashTable<T >::print() const {
    for (int i = 0; i < array_size; i++) {
    	if (array_state[i] == OCCUPIED) {
    		std::cout << array[i] << "  ";
		}
		if (array_state[i] == DELETED) {
    		std::cout << "D  ";
		}
		if (array_state[i] == EMPTY) {
    		std::cout << "E  ";
		}
	}
}

#endif
