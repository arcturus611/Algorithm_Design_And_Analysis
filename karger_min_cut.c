	/*
	karger's min-cut algorithm
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	#include<time.h>
	#define AVG_LEN 100
	#define MAX_LEN_NODE_LIST 1000
	#define MAX_DIG_LEN 20
	
	/* Defining all data structures */
	
	struct adj_list_node{
		int idx;
		struct adj_list_node* next;
	};
	
	struct adj_list{
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
	
	/* Global variables */
	struct edge* edge_head = NULL; 
	int edge_count = 0; 
	
	/* Declaring all functions */
	struct adj_list_node* new_adj_list_node(int);
	struct edge* new_edge(int, int);
	struct graph* create_graph(int);
	struct graph* read_graph(int); 
	
	void add_edge(struct graph*, int, int);
	void delete_edge(struct graph*, int, int); 
	
	void create_edge_in_list(int, int);
	void delete_edge_in_list(int, int);
	
	void delete_node(struct graph*, int);
	void edge_contraction(struct graph*, int);
	void delete_self_loop(struct graph*, int);	
	
	void print_graph(struct graph*); 
	void print_edge_list(struct edge*); 
	
	struct graph* copy_graph(struct graph*, int);
	struct edge* copy_edge_list(struct edge*); 
	
	/*Defining all declared functions*/
	struct adj_list_node* new_adj_list_node(int idx){
		struct adj_list_node* new_node = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
		new_node->idx = idx; 
		new_node->next = NULL;
		return new_node;	
	}

	struct edge* new_edge(int e1, int e2){
		struct edge* e = (struct edge *)malloc(sizeof(struct edge)); 
		e->idx = edge_count; 
		e->end1 = e1; 
		e->end2 = e2; 
		e->next = NULL;	
		return e; 
	}
	
	struct graph* create_graph(int V){
		struct graph* new_graph = (struct graph *)malloc(sizeof(struct graph)); // line a
		
		new_graph->V = V;
		new_graph->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); //what happens if you don;t do this? why is this required if we already have line a?
		
		for(int i = 0; i<V; i++){
			new_graph->array[i].head = NULL; 
		}
		
		return new_graph;
	}
	
	void add_edge(struct graph* G, int src, int sink){
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
			if (src<=sink)	create_edge_in_list(src, sink); 
			else create_edge_in_list(sink, src); 
		}
		
		return;
	}
	
	void delete_edge(struct graph* G, int src, int sink){
		//printf("[DELETE EDGE] Delete %d from the neighbour list of %d\n", sink, src); 
		
		//From the list of neighbours of src, delete sink
		struct adj_list_node* curr = G->array[src].head; 
		int curr_idx; 
		struct adj_list_node* temp = NULL; 
		
		//if the head (very first neighbour listed) is the sink
		while(curr){
			temp = curr;
			curr_idx = curr->idx;
			if(curr_idx == sink){
				curr = curr->next; 
				G->array[src].head = curr; //else you only change local variable  
				free(temp); 
			}else break; 
		}
		
		// else search for the sink in rest of the linked list
		if(curr==NULL){
			//printf("This node has been NULLed out\n**[END DELETE EDGE]**\n");
			return;
		}
		else{
			temp = curr; 
			curr = curr->next;
		}
	
		while(curr){			

			curr_idx = curr->idx; 
			
			if(curr_idx == sink){
				temp->next = curr->next; 
				free(curr);
				curr = temp->next; 
			}else{
				temp = curr;
				curr = curr->next; 
			}

		}
		
		//printing the neighbours after deletion of the neighbour 'sink'
		curr = G->array[src].head; 
		//printf("Post deletion neighbours of %d are\n", src);
		while(curr){
		//	printf(" %d -> ", curr->idx);
			curr = curr->next; 
		}
		//printf("\n"); 
		//printf("**[END DELETE EDGE]**\n");
		return;
	}

	void create_edge_in_list(int e1, int e2){
		//printf("[CREATE EDGE IN LIST]\n"); 
		
		edge_count++;
			
		if(edge_head == NULL){
			edge_head = new_edge(e1, e2);
			return;
		}
		
		struct edge* curr = edge_head; 
		struct edge* last = NULL; 
		
		while(curr){
			last = curr;
			curr = curr->next;
		} 
		 
		last->next = new_edge(e1, e2);
		//printf("**[END OF CREATE EDGE IN LIST]**\n"); 
		return;
	}
	
	void delete_edge_in_list(int e1, int e2){
		struct edge* curr = NULL;
		struct edge* temp = NULL; 
		int curr_e1, curr_e2; 
		
		//printf("[DELETE EDGE IN LIST] Edge end points %d and %d\n", e1, e2); 
		
		if(edge_head==NULL) return; //no more edges left to be deleted
		
		//check if edge to be deleted happens to be the edge_head
		while((edge_head!=NULL) && (edge_head->end1 == e1) && (edge_head->end2==e2)){
			temp = edge_head; 
			edge_head = edge_head->next; 
			free(temp);
			edge_count--;
		//	printf("Post deletion edge count = %d\n", edge_count); 
		}
		
		//if edge to be deleted is somewhere down the linked list of edges...	
		if(edge_head==NULL) return; 
		else{
			temp = edge_head; 
			curr = edge_head->next; 
		}
		
		while(curr){
			//temp = curr; 
			curr_e1 = curr->end1; 
			curr_e2 = curr->end2; 
			//curr = curr->next;
		
			if((curr_e1 == e1) && (curr_e2 ==e2)){
				temp->next = curr->next; 
				free(curr);
				curr = temp->next; 
				edge_count--; 
			//	printf("Post deletion edge count is %d\n", edge_count); 
			}else{
				temp = curr; 
				curr = curr->next; 
			}
		}
		
		//printf("**[END OF DELETE EDGE FROM LIST]**\n"); 
		
		return;
	}
	
		
	void delete_node(struct graph* G, int del){
		//disconnect it from all other nodes
		struct adj_list_node* curr = G->array[del].head; 
		//printf("[DELETE NODE] %d\n", del); 

		int iter = 0; 
		int curr_idx;
		
		while(curr){
			iter++;
			//printf("Cutting %d from neighbour %d\n", del, iter);
			
			curr_idx = curr->idx; 

			delete_edge(G, curr_idx, del);
			delete_edge(G, del, curr_idx); 

			if(del<=curr_idx)
				delete_edge_in_list(del, curr_idx);
			else 
				delete_edge_in_list(curr_idx, del); 
				
			//print_edge_list(edge_head); 
			
			curr = G->array[del].head; 
		}
		
		
		//printf("**[END OF DELETE NODE]**\n"); 
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
	
	void print_edge_list(struct edge* e1){
		struct edge* e = e1; 
		
		printf("[PRINT_EDGE_LIST]: ");
		while(e){
			printf("[%d] ( %d , %d ) -> ", e->idx, e->end1, e->end2);
			e = e->next; 
		}
		printf("\n");
		
		return;
	}
	
	void delete_self_loop(struct graph* G, int src){
		struct adj_list_node* curr = G->array[src].head; 
		
		struct adj_list_node* temp = curr; 
		int curr_idx = curr->idx; 
		
		while((curr!=NULL) && (curr_idx == src)){
			//printf("[DELETE SELF LOOP]\n"); 
			temp = curr; 
			
			curr = curr->next;
			G->array[src].head = curr;  
			curr_idx = curr->idx; 

			free(temp); 
		}	
		
		while(curr){
			temp = curr;
			curr_idx = curr->idx; 
			
			if(curr_idx == src){
			//	printf("[DELETE SELF LOOP]\n"); 
				free(temp);
			}
			
			curr = curr->next;
		}
		
		return;
	}
	
	void edge_contraction(struct graph* G, int edge_idx){
		//We wish to get the endpoints of the edge with id edge_idx 
		//and merge sink into src
		
		//Step 0: Get edge end points
		struct edge* e = edge_head; 
		int src, sink;
		int count = 1; 
		
		while(e){
			if(count == edge_idx){ //Pick one of N existing edges. 
				src = e->end1; 
				sink = e->end2; 
			//	printf("[EDGE CONTRACTION] Chose edge at index %d with endpoints %d and %d\n", edge_idx, src, sink); 
				break;
			}
			count++;
			e = e->next;
		}
		
		//Step 1: append to src all the neighbours of sink
		struct adj_list_node* curr_sink = G->array[sink].head; 
		
		while(curr_sink){
			add_edge(G, src, curr_sink->idx);
			curr_sink = curr_sink->next;
		}
		//printf("[EDGE CONTRACTION] Contracted edge %d; current edge count is %d\n", edge_idx, edge_count);
		//print_graph(G);
		//print_edge_list(edge_head); 
		
		//Step 2: null-ify the node
		delete_node(G, sink); 
		//printf("[EDGE CONTRACTION] Nullified sink %d; current edge count is %d\n", sink, edge_count);
		//print_graph(G); 
		//print_edge_list(edge_head); 
		
		return;
	}
	
	int karger_min_cut(struct graph* G, int V){
		//printf("[KARGER MIN CUT] Before we begin, the graph and edge list are \n");
		//print_graph(G); 
		//print_edge_list(edge_head);
		
		int edge_idx, min_cut;
		
		for(int i = 1; i<=V-2; i++){
			//pick a random edge
			edge_idx = rand()%edge_count + 1;
			
			//do edge_contraction
			edge_contraction(G, edge_idx); 
		}	
		 
		//print_graph(G);
		//print_edge_list(edge_head); 
		
		min_cut = edge_count; 
		
		//printf("The min cut value is %d\n", min_cut);
		
		return min_cut; 
	}
	
	struct adj_list_node* copy_adj_list_node(struct adj_list_node* n){
		struct adj_list_node* n2 = NULL, *prev = NULL; 
		
		while(n){
			struct adj_list_node* temp = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
			temp->idx = n->idx; 
			temp->next = NULL; 
			
			if(n2==NULL){
				n2 = temp; 
				prev = temp;
			}else{
				prev->next = temp; 
				prev = temp; 
			}
			
			n = n->next; 
		}
		
		return n2;
	}
	
	struct graph* copy_graph(struct graph* g, int v){
		struct graph* g2 = (struct graph *)malloc(sizeof(struct graph));
		
		g2->V = v; 
		g2->array = (struct adj_list *)malloc(v*sizeof(struct adj_list)); 
		
		for(int i = 0; i<v; i++){
			g2->array[i].head = copy_adj_list_node(g->array[i].head); 
		}
		
		return g2; 
		
	}
	
	struct edge* copy_edge_list(struct edge* e){
		struct edge* e2 = NULL, *prev = NULL; 
		
		while(e){
			struct edge* temp = (struct edge *)malloc(sizeof(struct edge));
			temp->idx = e->idx; 
			temp->end1 = e->end1;
			temp->end2 = e->end2; 
			temp->next = NULL;
			
			if(e2==NULL){
				e2 = temp; 
				prev = temp; 
			}else{
				prev->next = temp;
				prev = temp; 
			}
			
			e = e->next;
		}
		
		return e2; 
	}
	
	struct graph* read_graph(int V){
		FILE* fp; 
		fp = fopen("karger_min_cut.txt", "r"); 
		
		struct graph* G = (struct graph *)malloc(sizeof(struct graph)); 
		G->V = V; 
		G->array = (struct adj_list *)malloc(V*sizeof(struct adj_list)); 
		
		char line[MAX_LEN_NODE_LIST]; 
		char* p = NULL,*n = NULL; 
		int count = 0;
		int node_val;
		
		while(fgets(line, MAX_LEN_NODE_LIST, fp)!=NULL){
			char num[MAX_DIG_LEN]; 
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
							add_edge(G, count, node_val-1); 
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
	
	int cmp_fnc(const void* a, const void* b){
		return (*(int*)a - *(int*)b); 	
	}
	
	int main(int argc, char* argv[]){
		
		time_t t;
		
		srand((unsigned) &t);
		printf("\nNumber of edges is....%d\n", edge_count); 
		int V = 200; 
		struct graph* G = read_graph(V); 
		
		printf("\n\nOriginal graph....\n");
		print_graph(G); 
	/*	printf("\n\nCopied graph...\n"); */
		int orig_edge_count = edge_count; 
		struct graph* orig_graph = copy_graph(G, V); 
	//	print_graph(orig_graph); 
		struct edge* orig_edge_list = copy_edge_list(edge_head); 
	//	print_edge_list(edge_head); 
	//	print_edge_list(orig_edge_list); 
			
		int min_cut_vals[AVG_LEN];
		
		for(int i = 0; i<AVG_LEN; i++){
			edge_count = orig_edge_count; 
			G = copy_graph(orig_graph, V); 
			edge_head = copy_edge_list(orig_edge_list); 
			
			//printf("\n\nGraph is...\n\n"); 
			//print_graph(G); 
		
			min_cut_vals[i] = karger_min_cut(G, V); 
			printf("%d, ", min_cut_vals[i]); 
		}
			
		qsort(min_cut_vals, AVG_LEN, sizeof(int), cmp_fnc);
			
		printf("FINAL ANSWER OF KARGERs MIN CUT METHOD APPLIED many TIMES is %d\n", min_cut_vals[0]);
		print_graph(G);
		
		return 0;
	}
	
