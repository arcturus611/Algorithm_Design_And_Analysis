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
		int parent_idx; 
		if(x%2) parent_idx = floor(x/2);
		else parent_idx = x/2 - 1; 
		return parent_idx;
	}
	
	int get_left_child_idx(int x){
		return x*2+1; 
	}
	
	void bubble_up(int* p, int parent_idx, int new_pos){
		//bubble up
		while(*(p+parent_idx) > *(p + new_pos)){
			swap(p+parent_idx, p+new_pos);
			new_pos = parent_idx; 
			parent_idx = get_parent_idx(parent_idx); 
			if(parent_idx == -1) break; 
		}
		
		return;
	}
	
	void bubble_down(int* p, int left_child_idx, int curr_pos, int max_pos){
		//bubble down
		while(*(p+left_child_idx) < *(p+curr_pos)){
			swap(p+left_child_idx, p+curr_pos);
			curr_pos = left_child_idx; 
			left_child_idx = get_left_child_idx(left_child_idx);
			if(left_child_idx == max_pos) break;
		}
		
		return;
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
		//and now bubble up
		bubble_up(p, parent_idx, new_pos);
		
		return h;	
	}
	
	int extract_min_from_heap(struct heap* h){
		//root 
		int min_heap = h->arr[0]; 
		
		//decrement size
		(h->size)--;
		int sz = h->size;
		if (sz==-1) return min_heap; 
		
		//replace root with biggest latest-gen child (and then bubble it down)
		int* p = h->arr; 
		int last_child = p[sz+1]; //last child before we decremented size (this is horrible code)
		p[0] = last_child; 
		
		// bubble down
		int left_child_idx = get_left_child_idx(0); 
		bubble_down(p, left_child_idx, 0, sz+1); 
	 
	 	return min_heap;
	}
	
	void print_heap(struct heap* h){
		int sz = h->size;
		printf("Heap size is %d, and its contents are...\n", sz);
		for(int i = 0; i<=sz; i++){
			printf("%d, ", h->arr[i]); 
		}
		printf("\n");
		return;
	}
	
