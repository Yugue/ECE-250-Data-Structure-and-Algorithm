
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
		
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this
// Empty the current node
template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

/*      --- Accessors ---       */
// return the element stored in this node (whatever the node the user specify, ex. root.retrive(), etc)
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return (this -> element);
}

// Return the address of the left sub-tree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	return (this -> left_tree);
}

// Return the address of the right sub-tree
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	return (this -> right_tree);
}

// Return the null-path length of this node
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (this == nullptr) {
		return -1;																					// -1 if the node itself is empty;
	}	
	return (heap_null_path_length);
}

// return the number of times the argument is found in the tree
template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const {
	if (this == nullptr) {
		return 0;
	}
	int count = 0;
	if (this -> element == obj){
		count ++;
	}
	count += left_tree -> count(obj);												// Recursion call to count the left portion
	count += right_tree -> count(obj);												// Recursion call to count the right portion
																					// Count is increased by 1 if one element matches
	return count;	
}

/*         --- Mutators ---        */
template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ) {
	Leftist_node *temp;
	if (new_heap == nullptr) {														// If the new_heap is empty, return
		return;
	}
	if (ptr_to_this == nullptr) {															// If the current pointer is empty, link the new_heap 
		ptr_to_this = new_heap;
		return;
	}

	if (ptr_to_this -> element <= new_heap -> element) {							// If the current pointer's value is higher than the heap's one
		push(new_heap, ptr_to_this -> right_tree);										// Recursion call and carry on
		// ptr_to_this = ptr_to_this -> right_tree;
	}
	else {
		std::swap(new_heap, ptr_to_this);   										// If the current pointer's value is lower than the heap's one
		push(new_heap, ptr_to_this -> right_tree);											// New_heap is the current tree, and the existing one becomes the heap
		/*temp = ptr_to_this;
		ptr_to_this = new_heap;														// Doing the same thing as swap, but used an intermediate temp pointer.
		new_heap = temp;
		push(new_heap, ptr_to_this -> right_tree);*/
	}
	
	if ((ptr_to_this -> left_tree -> null_path_length()) < (ptr_to_this -> right_tree -> null_path_length())) {
		std::swap(ptr_to_this -> left_tree, ptr_to_this -> right_tree);				// swap if left tree's HNPL is smaller than the right's one once recursions are all over
		ptr_to_this -> heap_null_path_length = (ptr_to_this -> right_tree -> null_path_length()) + 1;		// update the current node's HNPL once recursion is done
		return;
	}
	else {
		ptr_to_this -> heap_null_path_length = (ptr_to_this -> right_tree -> null_path_length()) + 1;		// update the current node's HNPL once recursion
		return;
	}
	
}

// Clear the tree starting from this node
template <typename Type>
void Leftist_node<Type>::clear() {
	if (this == nullptr) {							// return if the tree is empty
		return;										// note cannot delete this, since hte branches will have memory leak
	}
	left_tree -> clear();							// when left tree reaches null, return to parent
	//delete this;									
	//return;
	right_tree -> clear();							// reach to the right tree
	
	delete this;									// delete the parent
	this -> heap_null_path_length = -1;				// update the empty's node's null path length to -1
	return;
}

#endif
