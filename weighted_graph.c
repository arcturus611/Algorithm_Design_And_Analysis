	/*
	weighted graphs
	*/
		/*
	graph algorithms
	*/
	
	#define MAIN_WEIGHTED_GRAPH_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include "weighted_graph.h"
	
	struct weighted_graph* create_graph(int V){
		struct weighted_graph* new_graph = (struct weighted_graph *)malloc(sizeof(struct weighted_graph)); 
		
		new_graph->V = V;
		new_graph->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); 
		
		for(int i = 0; i<V; i++){
			new_graph->array[i].head_node = NULL; 
			new_graph->array[i].head_edgeWeight = NULL; 
		}
		
		return new_graph;
	}

	struct adj_list_node* new_adj_list_node(int val){
		struct adj_list_node* new_node = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
		new_node->val = val;
		new_node->next = NULL;
		return new_node;	
	}
		
	struct weighted_graph* read_graph(int V){
		FILE* fp = NULL; 
		fp = fopen("dijkstraData.txt", "r"); 
		
		struct weighted_graph* G = (struct weighted_graph *)malloc(sizeof(struct weighted_graph)); 
		G->V = V; 
		G->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); 
		
		char line[MAX_NEIGHBOURS]; 
		char* p = NULL,*n = NULL; 
		int count = 0;
		int node_val,edge_weight_val;
		
		while(fgets(line, MAX_NEIGHBOURS, fp)!=NULL){
			char num[MAX_NEIGHBOUR_STR_LEN]; 
			p = line; 
			n = num;
			line[strchr(line, '\n')- line] = ' ';
			line[strlen(line)] = '\0';
			printf("%s, length = %d\n", line, strlen(line)); 
			
			while(isdigit(*p)) p++; //finish reading the first node number
			
			while((*p)!='\0'){
			
				if(isdigit(*p)){
					printf("==Is digit (%c)==\n", *p); 
					*n = *p; 
					n++;
					p++;
					if((*p)==','){
						printf("Is comma\n"); 
						*n = '\0';
						n = num; //reset n to num
						node_val = atoi(num); 
						printf("Node index is %d\n", node_val);
					}else if (((*p) == ' ') || ((*p) == '\t')){
						printf("Is space\n");
						*n = '\0';
						n = num;
						edge_weight_val = atoi(num);
						printf("Edge weight is %d\n", edge_weight_val); 
						//??! WAIT, NOT YET
						if(count<node_val){ //to prevent repetition of the edge
						//	printf("Blah\n");
							add_edge_to_graph(G, count, node_val-1, edge_weight_val); 
						}
						printf("Node: %d, ", node_val); 
						
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
	
	void add_edge_to_graph(struct weighted_graph* G, int src, int sink, int edge_weight){
		//Adding a node to the neighbours list of src...
		//...as long as src!=sink.
		
		//add a node to the linked list of vertex src
		if(src!=sink){
		/*
			printf("\n\n\n~~~~ CHECKING BEFORE ADDING....\n");
			printf("\n~~~~ Edge weights for the vertex %d~~~~", src); 
			struct adj_list_node* edge_weight_node;
			edge_weight_node = G->array[src].head_edgeWeight; 
			while(edge_weight_node){
				printf(" %d-> ", edge_weight_node->val);
				edge_weight_node = edge_weight_node->next; 
			}
			printf("\n\n"); 
		*/
			//printf("[ADD EDGE] Add node %d to %d\n", sink, src); 
			struct adj_list_node* new_node = new_adj_list_node(sink);
			new_node->next = G->array[src].head_node;
			G->array[src].head_node = new_node; 
			
			struct adj_list_node* new_edge_weight = new_adj_list_node(edge_weight);
			new_edge_weight->next = G->array[src].head_edgeWeight;
			G->array[src].head_edgeWeight = new_edge_weight;
		/*
			printf("\n\n\n~~~~ CHECKING IF ADDED,RIGHT BEFORE ADDINGTOSINK....\n");
			printf("\n~~~~ Edge weights for the vertex %d~~~~", src); 
			edge_weight_node = G->array[src].head_edgeWeight; 
			while(edge_weight_node){
				printf(" %d-> ", edge_weight_node->val);
				edge_weight_node = edge_weight_node->next; 
			}
			printf("\n\n"); 
		*/	
			//since it's an undirected graph, add the opposite direction too 
			// (as long as src!=sink)
			new_node = new_adj_list_node(src); 
			new_node->next = G->array[sink].head_node; 
			G->array[sink].head_node = new_node;
		
			struct adj_list_node* new_edge_weight_2 = new_adj_list_node(edge_weight);
			new_edge_weight_2->next = G->array[sink].head_edgeWeight; 
			G->array[sink].head_edgeWeight = new_edge_weight_2;	
			
		/*	printf("\n\n\n~~~~ CHECKING IF ADDED, RIGHT BEFORE ADDING TO SINK....\n");
			printf("\n~~~~ Edge weights for the vertex %d~~~~", src); 
			edge_weight_node = G->array[src].head_edgeWeight; 
			while(edge_weight_node){
				printf(" %d-> ", edge_weight_node->val);
				edge_weight_node = edge_weight_node->next; 
			}
			printf("\n\n"); 
			
		*/
	
		}
		
		return;
	}
	
	void print_graph(struct weighted_graph* G){
		printf("[PRINT WEIGHTED GRAPH]\n"); 
		int V = G->V;	
		
		struct adj_list_node* node, *edge_weight;	
		for(int i = 0; i<V; i++){
			node = G->array[i].head_node; 
			edge_weight = G->array[i].head_edgeWeight; 
			
			printf("\n  Vertex: %d~~~~", i);
			while(node){
				printf(" %d -> ", node->val);
				node = node->next; 
			}
			
			printf("\n~~~~ Edge weights for the vertex %d~~~~", i); 
			while(edge_weight){
				printf(" %d-> ", edge_weight->val);
				edge_weight = edge_weight->next; 
			}
			printf("\n\n"); 
		}
		printf("**[END PRINT WEIGHTED GRAPH]**\n"); 
		return;
	}
	
