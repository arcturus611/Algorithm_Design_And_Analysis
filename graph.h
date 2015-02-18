	/*
	Graph code data structures
	*/
	
	#ifndef GRAPH_FUNCTIONS_H
	#define GRAPH_FUNCTIONS_H
	
	#include<stdbool.h>
	
	#define MAX_NEIGHBOURS 1000
	#define MAX_NEIGHBOUR_STR_LEN 1000
	
	#ifdef MAIN_GRAPH_FILE
		/* Global variables */
		struct edge* edge_list_head = NULL; 
		int edge_list_count = 0; 
	#else
		extern struct edge* edge_list_head; 
		extern int edge_list_count; 
	#endif
	/* Defining all data structures */
	
	struct adj_list_node{
		int idx;
		struct adj_list_node* next;
	};
	
	struct adj_list{
		bool explored; 
		struct adj_list_node* head;	
	};
	
	struct graph{
		int V;
		struct adj_list* array; 			
	};
	
	struct edge{
		int idx; 
		int end1; 
		int end2;
		struct edge* next; 
	};
	
	/* End of data structures */
	
	/* List of functions */
	struct graph* create_graph(int);
	struct graph* read_graph(int); 
	void print_graph(struct graph*); 
	
	struct adj_list_node* new_adj_list_node(int);
	struct edge* new_edge(int, int);
	
	void add_edge_to_graph(struct graph*, int, int);	
	void add_to_edge_list(int, int);
	
	/* End of list of functions */
	
	#endif
