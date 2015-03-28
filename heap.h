	/*
		Heap data structures
	*/
	
	#ifndef HEAP_FUNCTIONS_H
	#define HEAP_FUNCTIONS_H
	
	#define MAX_HEAP_SIZE 500
	
	/* Data structure */
	struct heap{
		int* arr; 
		int size; 
	};
	
	/* Functions */
	struct heap* init_heap(void); 
	
	struct heap* insert_in_heap(struct heap*, int); 
	
	void print_heap(struct heap*); 
	
	int extract_min_from_heap(struct heap*); 
	
	void delete_from_heap(struct heap*); 
	
	#endif
