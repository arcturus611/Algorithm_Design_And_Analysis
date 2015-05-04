	/*
		Union-Find data structure
		This data structure is a great way to speed up Kruskal's algorithm 
		from its O(mn) running time to O(mlogn) time.
		http://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
		Implemented using path compression and union by rank
	*/
	
	#define MAIN_UNION_FIND_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include "union_find.h"
	
	struct component* create_components(int v){	
		//create an array of n components. 
		//these represent the nodes of the graph. 
		//we are looking at the graph separately from two perspectives: nodes and edges
		struct component* n = (struct component* )malloc(v*sizeof(struct component)); 
		if (n==NULL){
			printf("Error: Couldn't allocate memory for component array\n");
			return NULL; 
		}
		
		for(int i = 0; i<v; i++){
			(n+i)->parent = i;
			(n+i)->rank = 0; 
		}	
		
		return n; 
	}
	
	int find_component(struct component* comp_arr, int x){
		if(comp_arr[x].parent!=x){
			(comp_arr+x)->parent = find_component(comp_arr, comp_arr[x].parent); 
		}
		
		return comp_arr[x].parent; 
	}

	void union_components(struct component* comp_arr, int x, int y){
		//union of components containing x and y
		int xroot = find_component(comp_arr, x);
		int yroot = find_component(comp_arr, y); 
		printf("xroot = %d, yroot = %d\n", xroot, yroot);
		if(comp_arr[xroot].rank<comp_arr[yroot].rank){
			comp_arr[xroot].parent = yroot;
		}else if(comp_arr[xroot].rank<comp_arr[yroot].rank){
			comp_arr[yroot].parent = xroot;
		}else{
			comp_arr[xroot].parent = yroot; 
			comp_arr[yroot].rank++;	
		}
	
	}
