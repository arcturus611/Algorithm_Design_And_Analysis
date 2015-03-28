	/*
		Testing heap code
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include "heap.h"
	
	int main(int argc, char* argv[]){
		struct heap* H = init_heap();
		print_heap(H); 
		for(int i = 5; i>0; i--){
			insert_in_heap(H, i*10); 
			print_heap(H);
		}
		printf("\nAnd minimum of heap so far is.... %d\n", extract_min_from_heap(H));
		print_heap(H);
		return 0;
	}
