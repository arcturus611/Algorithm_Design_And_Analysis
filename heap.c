	/*
		Heap functions
	*/
	
	#define MAIN_HEAP_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include<math.h>
	#include "heap.h"
	
	void swap(int *x, int* y){
		int temp = *x; 
		*x = *y;
		*y = temp; 
		return;
	}
	
	int get_parent_idx(int x){
		if(x%2) parent_idx = floor(x/2);
		else parent_idx = x/2 - 1; 
		return parent_idx;
	}
	
	struct heap* init_heap(void){
		struct heap* h = (struct heap *)malloc(sizeof(struct heap)); 
		h->arr = (int* )malloc(MAX_HEAP_SIZE*sizeof(int)); 
		for(int i = 0; i<MAX_HEAP_SIZE; i++){
			h->arr[i] = 0;
		}
		h->size = -1; //pointer to last element in heap. if none present yet, -1
		return h;
	}
		
	struct heap* insert_in_heap(struct heap* h, int x){
		// first insert in last position
		int new_pos = h->size + 1; 
		h->size = new_pos; 
		int* p = h->arr;
		*(p + new_pos) = x;
		
		//now bubble up
		//first check if this was the very first element of heap
		if (new_pos==0) return h; 
		//next, initialize for bubble up
		int parent_idx = get_parent_idx(new_pos);
		
		while(*(p+parent_idx) > *(p + new_pos)){
			swap(p+parent_idx, p+new_pos);
			new_pos = parent_idx; 
			parent_idx = get_parent_idx(parent_idx); 
			if(parent_idx == -1) break; 
		}
		
		return h;	
	}
	
	void print_heap(struct heap* h){
		int sz = h->size;
		printf("Heap contents are...\n");
		for(int i = 0; i<sz; i++){
			printf("%d, ", h->arr[i]); 
		}
		printf("\n");
		return;
	}
	
