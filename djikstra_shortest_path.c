	/*djikstra's algorithm*/

	/*while(edge_ptr){
			edge_weight = edge_ptr->val; 
			printf("~~Curr edge weight is %d\n", edge_weight); 
			if(edge_weight<v_min_path_len){
				v_min_path_len = edge_weight;
				v_min_path_end_idx = count; 
			}
			count++;
			edge_ptr = edge_ptr->next; 
		}
								
		node_ptr = G->array[v].head_node; 
		count = 0;
		while(node_ptr){
			if(count == v_min_path_end_idx){
				v_min_path_end = node_ptr->val; 
				break;
			}
			count++;
			node_ptr = node_ptr->next;
		}
	*/
		
	#include<stdio.h>
	#include<stdlib.h>
	#include "weighted_graph.h"
	
	struct min_path_info* find_min_path_from_v(struct weighted_graph* G, int v){
		printf("^^^ Finding min path from %d ^^^\n", v); 
		//Declare/initialize all variables
		struct adj_list_node* edge_ptr = NULL, *node_ptr = NULL;
		int v_min_path_len, v_min_path_end, edge_weight, curr_neighbour;
		struct min_path_info* v_min_info = (struct min_path_info *)malloc(sizeof(struct min_path_info)); 
		
		v_min_path_len = 1000000; //initialize to ridiculously large number
		v_min_path_end = 0;
		
		edge_ptr = G->array[v].head_edgeWeight; 
		node_ptr = G->array[v].head_node; 
		
		while(node_ptr){
			curr_neighbour = node_ptr->val;
			edge_weight = edge_ptr->val;
			if(G->array[curr_neighbour].head_node->explored == 0){//only look at nodes yet not in set X
				if(edge_weight<v_min_path_len){//get min path & corresponding node from v
					v_min_path_len = edge_weight;
					v_min_path_end = curr_neighbour;
				}
			}
			node_ptr = node_ptr->next;
			edge_ptr = edge_ptr->next;
		}
		
		v_min_info->len = v_min_path_len; 
		v_min_info->end2 = v_min_path_end; 
		
		return v_min_info; 
	}
	
	void djikstra_shortest_path(struct weighted_graph* G, int s, int n){
	
		struct min_path_info* v_min_info = NULL;
		int min_path_len, min_path_end, v, i, j, v_min_path_len, v_min_path_end;
		
		//initialize X and A
		int X[n]; //array of indices of nodes for which paths have been determined 
		//(ie, belonging to set X,following Tim's lecture notation)
		int A[n]; //array of shortest path lengths from source s
		for(i = 0; i<n; i++){	
			X[i] = 0;
			A[i] = 0; 
		}
		X[0] = s; 
		G->array[s].head_node->explored = 1; 
				
		for(i = 1; i<=n-1; i++){//do until all nodes have been explored
			min_path_len = 1000000;
			min_path_end = 0;
			printf("<<<<<Iteration %d >>>>>\n", i);
			
			for(j = 0; j<i; j++){//for already explored nodes
				v = X[j]; //index of a node in set X
				printf("~Considering node %d from set X\n", v); 
				if(A[v]<=min_path_len){//if path {s-v} is already longer than the min we have, ignore. 
					//find min edge_weight and corresponding node_idx from this node
					v_min_info = find_min_path_from_v(G, v);
					v_min_path_len = v_min_info->len;
					v_min_path_end = v_min_info->end2;
					printf("~From node %d in set X, the shortest path to a non-X node is to %d, with length %d\n", v, v_min_path_end, v_min_path_len); 
					
					if ((v_min_path_len + A[v]) < min_path_len){
						min_path_len = v_min_path_len + A[v];
						min_path_end = v_min_path_end;	
					}
						
				}
				printf("~Min path len so far: %d, new min path node: %d\n", min_path_len, min_path_end);
					
			}
			
			X[i] = min_path_end; 
			A[min_path_end] = min_path_len;	
			G->array[min_path_end].head_node->explored = 1; 		
		}
		
		//testing distances for given test cases
		printf("Djikstra shortest paths for given test nodes\n");
//		int T[10] = {9,29,49,79,89,109,129,159,179,189};
		int T[10] = {7,37,59,82,99,115,133,165,188,197};
		for(i = 0; i<10; i++){
			int x = T[i]-1; 
			printf(" %d, ", A[x]); 
			/*
			Solution to sample:
			3205,  2303,  3152,  982,  2018,  2317,  1820,  2403,  3027,  2596
			*/
		}
		printf("\n"); 
		/*
		printf("Djikstra's path values...\n");
		for(i = 0; i<7; i++){
			printf(" %d, ", A[i]);
		}
		*/	
		
		return;
	}
	
	int main(int argc, char* argv[]){
		int num_nodes = 200;
		struct weighted_graph* G = read_graph(num_nodes);
		//print_graph(G);
		djikstra_shortest_path(G, 0, num_nodes);
		return 0;
	}

