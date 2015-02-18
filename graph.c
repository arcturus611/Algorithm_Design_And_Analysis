	/*
	graph algorithms
	*/
	
	#define MAIN_GRAPH_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include "graph.h"
	
	struct graph* create_graph(int V){
		struct graph* new_graph = (struct graph *)malloc(sizeof(struct graph)); // line a
		
		new_graph->V = V;
		new_graph->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); //what happens if you don;t do this? why is this required if we already have line a?
		
		for(int i = 0; i<V; i++){
			new_graph->array[i].explored = 0; 
			new_graph->array[i].head = NULL; 
		}
		
		return new_graph;
	}
		
	struct graph* read_graph(int V){
		FILE* fp; 
		fp = fopen("breadth_first_search.txt", "r"); 
		
		struct graph* G = (struct graph *)malloc(sizeof(struct graph)); 
		G->V = V; 
		G->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); 
		
		char line[MAX_NEIGHBOURS]; 
		char* p = NULL,*n = NULL; 
		int count = 0;
		int node_val;
		
		while(fgets(line, MAX_NEIGHBOURS, fp)!=NULL){
			char num[MAX_NEIGHBOUR_STR_LEN]; 
			p = line; 
			n = num;
			line[strchr(line, '\n')- line] = '\0';
			printf("%s, length = %d\n", line, strlen(line)); 
			
			while(isdigit(*p)) p++; 
			
			while((*p)!='\0'){
			
				if(isdigit(*p)){
					//printf("Is digit (%c)\n", *p); 
					*n = *p; 
					n++;
					p++;
					if(!isdigit(*p)){
						//printf("Is space\n"); 
						*n = '\0';
						n = num; 
						node_val = atoi(num); 
						printf("Node: %d, ", node_val); 
						if(count<node_val){
						//	printf("Blah\n");
							add_edge_to_graph(G, count, node_val-1); 
						}
					}
				}else{
					n = num; //reset
					p++;			
				}
			}
			printf("\n"); 
			count++;
		}
	
		
		return G; 
	}

	struct adj_list_node* new_adj_list_node(int idx){
		struct adj_list_node* new_node = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
		new_node->idx = idx;
		new_node->next = NULL;
		return new_node;	
	}

	struct edge* new_edge(int e1, int e2){
		struct edge* e = (struct edge *)malloc(sizeof(struct edge)); 
		e->idx = edge_list_count; 
		e->end1 = e1; 
		e->end2 = e2; 
		e->next = NULL;	
		return e; 
	}
	
	void add_edge_to_graph(struct graph* G, int src, int sink){
		//Adding a node to the neighbours list of src...
		//...as long as src!=sink.
		
		//add a node to the linked list of vertex src
		if(src!=sink){
			//printf("[ADD EDGE] Add node %d to %d\n", sink, src); 
			struct adj_list_node* new_node = new_adj_list_node(sink);
			new_node->next = G->array[src].head;
			G->array[src].head = new_node; 
		
			//since it's an undirected graph, add the opposite direction too 
			// (as long as src!=sink)
			new_node = new_adj_list_node(src); 
			new_node->next = G->array[sink].head; 
			G->array[sink].head = new_node;

			//in the edge list, create an edge between source and sink
			// (again, as long as it's not a self-loop)
			if (src<=sink) add_to_edge_list(src, sink); 
			else add_to_edge_list(sink, src); 
		}
		
		return;
	}
	
	void add_to_edge_list(int e1, int e2){
		//printf("[CREATE EDGE IN LIST]\n"); 
		
		edge_list_count++;
			
		if(edge_list_head == NULL){
			edge_list_head = new_edge(e1, e2);
			return;
		}
		
		struct edge* curr = edge_list_head; 
		struct edge* last = NULL; 
		
		while(curr){
			last = curr;
			curr = curr->next;
		} 
		 
		last->next = new_edge(e1, e2);
		//printf("**[END OF CREATE EDGE IN LIST]**\n"); 
		return;
	}
	
	void print_graph(struct graph* G){
		printf("[PRINT GRAPH]\n"); 
		int V = G->V;	
		
		struct adj_list_node* node;	
		for(int i = 0; i<V; i++){
			node = G->array[i].head; 
			printf("\n Vertex: %d", i);
			while(node){
				printf("-> %d ", node->idx);
				node = node->next; 
			}
			printf("\n"); 
		}
		printf("**[END PRINT GRAPH]**\n"); 
		return;
	}
	
