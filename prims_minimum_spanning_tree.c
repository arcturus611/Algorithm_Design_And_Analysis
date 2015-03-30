	/*
		Prim's minimum spanning tree algorithm
		Code adapted from Djikstra's Shortest Path Algorithm 	
		Running time: O(mn). 
		Can be implemented faster using heaps- will do that next
	*/
		
	#include<stdio.h>
	#include<stdlib.h>
	#include "weighted_graph.h"
	
	struct min_path_info* get_cheapest_cross_edge_from_node(struct weighted_graph* G, int v){
		//Declare/initialize all variables
		struct adj_list_node* edge_ptr = NULL, *node_ptr = NULL;
		int v_min_path_len, v_min_path_end, edge_weight, curr_neighbour;
		struct min_path_info* v_min_info = (struct min_path_info *)malloc(sizeof(struct min_path_info)); 
		
		v_min_path_len = INIT_ASSUMED_MIN_EDGE_COST; //initialize to ridiculously large number
		v_min_path_end = INIT_ASSUMED_MIN_EDGE_ENDPOINT; //initialize to ridiculous node
		
		edge_ptr = G->array[v].head_edgeWeight; 
		node_ptr = G->array[v].head_node; 
		
		//explore while the present node still has neighbours
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
		
	long long int prims_minimum_spanning_tree(struct weighted_graph* G, int s, int n){
	
		struct min_path_info* v_min_info = NULL;
		int min_path_len, min_path_end, v, i, j, v_min_path_len, v_min_path_end;
		
		//initialize X and A
		int X[n]; //array of indices of nodes for which paths have been determined 
		//(ie, belonging to cut X,following Tim's lecture notation)
		int A[n]; //array of cheapest edge weights in the MST
		
		for(i = 0; i<n; i++){	
			X[i] = 0;
			A[i] = 0; 
		}
		
		X[0] = s; 
		G->array[s].head_node->explored = 1; 
		
		long long int total_MST_cost = 0;
		
		//Start exploring
		for(i = 1; i<=n-1; i++){//do until all nodes have been explored
			min_path_len = INIT_ASSUMED_MIN_EDGE_COST;
			min_path_end = INIT_ASSUMED_MIN_EDGE_ENDPOINT;
			
			for(j = 0; j<i; j++){//for already explored nodes (nodes that are in cut X)
				v = X[j]; //index of a node in cut X

				//find min edge_weight and corresponding node_idx from this node
				v_min_info = get_cheapest_cross_edge_from_node(G, v);
				v_min_path_len = v_min_info->len;
				v_min_path_end = v_min_info->end2;
					
				if (v_min_path_len < min_path_len){
					min_path_len = v_min_path_len;
					min_path_end = v_min_path_end;	
				}
					
			}
			
			X[i] = min_path_end; 
			A[min_path_end] = min_path_len;	
			total_MST_cost+=min_path_len;
			G->array[min_path_end].head_node->explored = 1; 		
		}
		
				
		return total_MST_cost;
	}
	
	struct weighted_graph* read_mst_graph(char* file_name){
		FILE* fp = fopen(file_name, "r"); 
		int num_nodes, num_edges; 
		if(fscanf(fp, "%d %d", &num_nodes, &num_edges)==0) 
			fprintf(stderr, "Error reading number of nodes and edges!\n");
		
		struct weighted_graph* G = (struct weighted_graph *)malloc(sizeof(struct weighted_graph)); 
		G->V = num_nodes;
		G->array = (struct adj_list *)malloc(num_nodes*sizeof(struct adj_list)); 
		
		int node1, node2, edge_cost;
		while(fscanf(fp, "%d %d %d", &node1, &node2, &edge_cost)!=EOF){
			add_edge_to_graph(G, node1-1, node2-1, edge_cost); //because our naming convention follows C's array element numbering convention
		}  
		
		fclose(fp);
		
		return G; 	
	}
	
	int main(int argc, char* argv[]){
		struct weighted_graph* G = read_mst_graph("prims_minimum_spanning_tree.txt");
		print_graph(G);
		printf("\nTotal MST cost is %lld\n", prims_minimum_spanning_tree(G, 0, G->V));
		return 0;
	}

