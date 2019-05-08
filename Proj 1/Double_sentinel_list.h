/*****************************************
 * UW User ID:  y862chen
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;

		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

// constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	list_head = new Double_sentinel_list::Double_node;			// create head sentinel node
	list_tail = new Double_sentinel_list::Double_node;			// create tail sentinel node
	list_head -> previous_node = nullptr;						// previous pointer of head points to null
	list_head -> next_node = list_tail;							// next pointer of head points to tail
	list_tail -> previous_node = list_head;						// previous pointer of tail points to head
	list_tail -> next_node = nullptr;							// next pointer of tail points to null
}

// copy constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	// empty new list creation
	list_head = new Double_sentinel_list::Double_node;			
	list_tail = new Double_sentinel_list::Double_node;			
	list_head -> previous_node = nullptr;						
	list_head -> next_node = list_tail;							
	list_tail -> previous_node = list_head;						
	list_tail -> next_node = nullptr;	
	
	// traverse throught original list
	Double_node *ori_head = list.list_head->next_node;						// pointer to the first node of original list
	Double_node *temp; 														// create temporary pointers
	Double_node *temp1;
	temp1 = list_head;
	while ((ori_head -> next_node) != nullptr) {
		temp = new Double_sentinel_list::Double_node;						// new node
		temp -> node_value = ori_head -> node_value;						// copy node value. Note that head and tail nodes are ignored
		temp1 -> next_node = temp;											// Assign proper linking
		temp -> previous_node = temp1;
		temp1 = temp1 -> next_node;											// update the temp1 pointer
		ori_head = ori_head -> next_node;									// update the ori_head pointer
	}		
	temp1 -> next_node = list_tail;											// update the tail pointers	
	list_tail -> previous_node = temp1;	
	list_size = list.list_size;												// copy list size as well
}

// move constructor
template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ):
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
	list_head = new Double_sentinel_list::Double_node;						// construct an empty list
	list_tail = new Double_sentinel_list::Double_node;			
	list_head -> previous_node = nullptr;						
	list_head -> next_node = list_tail;							
	list_tail -> previous_node = list_head;						
	list_tail -> next_node = nullptr;	
	
	swap(list);																// swap list with empty list
	list.~Double_sentinel_list();											// delete list
}

// destructor
template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	Double_node *temp, *temp1;
	temp = list_head;									// starting with the head
	while (temp -> next_node != nullptr) {
		temp1 = temp;									// temp1 points to targeting node
		temp = temp -> next_node;						// temp 
		delete temp1;
	}
	temp = list_tail;
	delete temp;	
	list_size = 0;
}


// Accessors
template <typename Type>
int Double_sentinel_list<Type>::size() const {
	return list_size;										// Return the size of the list
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	return (list_size == 0?true:false);						// Check if list has 0 node
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	if ((list_head->next_node->next_node) != nullptr) {
		return (list_head->next_node->node_value);			// if the head sentinel is not followed by a tail sentinel, print the value of the 1st node	
	}
	else {
		throw underflow();
	}
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	if ((list_tail->previous_node->previous_node) != nullptr) {
		return (list_tail->previous_node->node_value);		// if the head sentinel is not followed by a tail sentinel, print the value of the last node	
	}
	else {
		throw underflow();
	}
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
	return (list_head->next_node);							// Return the address stored by "next" of head sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
	return (list_tail);										// Return the address of the tail sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
	return (list_tail->previous_node);						// Return the address stored by "previous" of tail sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
	return (list_head);										// Return the address of head sentinel
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
	Double_node *temp;
	temp = list_head -> next_node;							// set the pointer to the 1st node
	while ((temp -> next_node) != nullptr) {
		if (temp -> node_value == obj) {					// check if the node matches, return if yes, keep searching otherwise
			return (temp);
			break;
		}
		temp = temp -> next_node;
	}
	return end();											// return end() if while loop exhausted -> not found
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	int node_count = 0;										// set the counter to 0
	Double_node *temp;
	temp = list_head -> next_node;							// set the pointer to the 1st node
	while ((temp -> next_node) != nullptr) {
		if (temp -> node_value == obj) {					// check if the node matches, increase counter if yes
			node_count++;
		}
		temp = temp -> next_node;
	}
	return node_count;										
}


// Mutators
template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	Double_node *temp; 
	Double_node *first_node;
	temp = new Double_sentinel_list::Double_node;			// create a new node
	temp -> node_value = obj;								// store input value into the new node
	first_node = list_head -> next_node;					// set the first_node to point to the original first node
	
	list_head -> next_node = temp;							// set the pointers of the new node
	temp -> previous_node = list_head;
	first_node -> previous_node = temp;
	temp -> next_node = first_node;
	list_size++;											// increase list size by 1
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	Double_node *temp; 
	Double_node *last_node;
	temp = new Double_sentinel_list::Double_node;			// create a new node
	temp -> node_value = obj;								// store input value into the new node
	last_node = list_tail -> previous_node;					// set the first_node to point to the original first node
	
	last_node -> next_node = temp;
	temp -> previous_node = last_node;
	list_tail -> previous_node = temp;
	temp -> next_node = list_tail;
	list_size++;											// increase list size by 1
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	Double_node *first_node;
	Double_node *second_node;
	first_node = list_head -> next_node;
	second_node = first_node -> next_node;
	
	if (list_size != 0) {									// if the list is not empty
		list_head -> next_node = second_node;				// rerouting head sentinel to second node
		second_node -> previous_node = list_head;
		delete first_node;									// delete the first node
		list_size--;										
	}
	else {
		throw underflow();
	}
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	Double_node *last_node;
	Double_node *secondlast_node;
	last_node = list_tail -> previous_node;
	secondlast_node = last_node -> previous_node;
	
	if (list_size != 0) {									// if the list is not empty
		list_tail -> previous_node = secondlast_node;		// rerouting tail sentinel to secondlast node
		secondlast_node -> next_node = list_tail;
		delete last_node;									// delete the last node
		list_size--;										
	}
	else {
		throw underflow();
	}
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	int erase_count = 0;
	Double_node *temp, *before, *after, *temp1;
	temp = list_head -> next_node;								// set temp to the first node
	while ((temp -> next_node) != nullptr) {			
		before = temp -> previous_node;							// before and after are the nodes surrounding the tracking node
		after = temp -> next_node;
		temp1 = temp;
		bool result = false;									// false -> not deleting, true -> deleting the current node
		if (temp -> node_value == obj) {
			before -> next_node = after;
			after -> previous_node = before;
			result = true;
			erase_count++;
		}
		temp = temp -> next_node;
		if (result == true) {
			delete temp1;
			list_size--;
		}
	}
	return erase_count;
}


// Double_node constructor
template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	node_value = nv;     // or node_value = *nv, what type is nv?
	previous_node = pn;
	next_node = nn;
}

// Double_node Methods
template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
