	/*
	Weighted graph code data structures
	*/
	
	#ifndef WEIGHTED_GRAPH_FUNCTIONS_H
	#define WEIGHTED_GRAPH_FUNCTIONS_H
	
	#include<stdbool.h>
	
	#define MAX_NEIGHBOURS 1000
	#define MAX_NEIGHBOUR_STR_LEN 1000
	#define INIT_ASSUMED_MIN_EDGE_COST 1000000
	#define INIT_ASSUMED_MIN_EDGE_ENDPOINT -1
	
	/*#ifdef MAIN_WEIGHTED_GRAPH_FILE
		// Global variables 
		int edge_list_count = 0; 
	#else
		extern int edge_list_count; 
	#endif*/
	/* Defining all data structures */
	
	struct adj_list_node{
		int val; //could represent node index or edge_weight
		bool explored; //boolean indicating if node/edge is in set X or not
		struct adj_list_node* next;
	};
	
	struct adj_list{
		struct adj_list_node* head_node;	
		struct adj_list_node* head_edgeWeight;
	};
	
	struct weighted_graph{
		int V;
		struct adj_list* array; 			
	};
	
	struct min_path_info{
		int len;
		int end2;
	};
	
	/* End of data structures */
	
	/* List of functions */
	struct weighted_graph* create_graph(int);
	struct weighted_graph* read_graph(int); 
	void print_graph(struct weighted_graph*);
	
	struct adj_list_node* new_adj_list_node(int);
	void add_edge_to_graph(struct weighted_graph*, int, int, int);
	/* End of list of functions */
	
	#endif
