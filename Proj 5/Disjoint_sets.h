
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

// Constructor
Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	for (int i = 0; i<n; i++) {
		nodes[i] = new ll_entry;	
		sets[i]= new set_info;	
													// Make the array inside array only one element
		sets[i] -> head = nodes[i];													// set the head and tail of the set to point to the node itself
		sets[i] -> tail = nodes[i];
		sets[i] -> size = 1;	
															// each set size is 1
		nodes[i] -> content = i;													// update the content of each node
		nodes[i] -> next = nullptr;													// each node's next pointer is nullptr, since they are not linked yet
		nodes[i] -> ptr_to_info = sets[i];											// each node is pointing to its connected set node
	}	
}

// Destructor
Disjoint_set::~Disjoint_set() {
	for(int i=0;i<initial_num_sets;i++){
		delete nodes[i];
		delete sets[i];
	}
	delete[] nodes;
	delete[] sets;
	set_counter = 0;
}

// Returns the representative (head node value) of the set that the node item belongs to
int Disjoint_set::find_set(int item) const{
	if (item < 0 || item >= initial_num_sets) {
		throw illegal_argument();
	}
	else{
		return (nodes[item] -> ptr_to_info -> head -> content);     					// If >2 nodes have been merged to one set, the set number is always the item number of the first node
	}
}

// Return the number of set currently stored
int Disjoint_set::num_sets() const {
	return set_counter;
}

// Unites the sets that contain node_index1 and node_index2
void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 					// assume ni2 contains the largest set node
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;
	
	/* iterate through the shorter list and modify the pointers
	while (has not reached the end of set) {
		....
	}*/
	si2 = nodes[ni2] -> ptr_to_info;
	nodes[ni1] -> ptr_to_info -> tail -> next = nodes[ni2] -> ptr_to_info -> head;	// connect set 1 (larger set) to set 2 (smaller set)
	
	ll_entry* temp = nodes[ni2] -> ptr_to_info -> head;								// temp points to the head of set 2

	
	do {
		temp -> ptr_to_info = nodes[ni1] -> ptr_to_info;							// Iterate through set 2 and modify each node's pointer to set to the 1st set
		temp = temp -> next;
	} while (temp != nullptr);
	
	nodes[ni1] -> ptr_to_info -> tail = si2 -> tail;			// update the tail pointer of set 1 to point the tail pointer of set 2
	nodes[ni1] -> ptr_to_info -> size += si2 -> size;        	// keep the inserted arrays sorted?

	si2 -> head = nullptr;
	si2 -> tail = nullptr;
	si2 -> size = 0;
	set_counter--;																	// update set counter
}


#endif
