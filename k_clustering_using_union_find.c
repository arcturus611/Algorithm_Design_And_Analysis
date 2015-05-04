	/*
		Clustering by Union-Find data structure
	*/
	
	/*
		1. Read the graph as an array of edges. An edge is a struct with edgelength and two node indices
		2. Sort the edges by edgelength values
		3. For n-k iterations where n = #nodes, k = #required clusters, UNIONize the nodes of the cheapest edge IF there are no CYCLES with that union
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	#include "union_find.h"
	#define MAX_LEN 20
	
	struct edge{
		int len; 
		int end1; 
		int end2;
	}; 
	
	void graph_stats(char* filename, int* num_nodes, int* num_edges){
		int e = 0;
		char line[MAX_LEN]; 
		
		FILE* fp = fopen(filename, "r"); 
		
		//getting the #edges and nodes
		fgets(line, MAX_LEN, fp);
		*num_nodes = atoi(line);  
		
		while(fgets(line, MAX_LEN, fp)!=NULL){
			e++; 
		}
		*num_edges = e; 
		printf("We have %d nodes and %d edges\n", *num_nodes, *num_edges); 
		
		fclose(fp); 
		return;
	}	
	
	struct edge* read_graph(char* filename, int num_edges){
		//actually reading values
		int end1, end2, len, edge_idx=0;
		char line[MAX_LEN];
		
		struct edge* my_graph = (struct edge *)malloc(num_edges*sizeof(struct edge)); 
				
		FILE* fp = fopen(filename, "r"); 
		fgets(line, MAX_LEN, fp);
				
		while(fscanf(fp, "%d %d %d", &end1, &end2, &len)!=EOF){
			my_graph[edge_idx].end1 = end1; 
			my_graph[edge_idx].end2 = end2; 
			my_graph[edge_idx].len = len;
			edge_idx++;
		}
		
		fclose(fp); 
		
		return my_graph;	
	}
	
	int cmpfnc(const void* a, const void* b){
		struct edge* e_a = (struct edge* )a;
		struct edge* e_b = (struct edge* )b; 
		return ((e_a->len) - (e_b->len)); 
	}
	
	int isCycle(struct component* C, int x, int y){
		return ((find_component(C, x)!=find_component(C, y)) ? 0 : 1);
	}
	
	int k_cluster(int k, int num_edges, struct edge* graph, int num_nodes, struct component* components){
		qsort(graph, num_edges, sizeof(struct edge), cmpfnc);//sort all the edge lengths
	
		int num_edges_in_clusters = 0; 
		int edge_idx = 0;
		int spacing;
		
		//we only need to find num_nodes - k good edges, and then we're done (it'll be nicely k-clustered at that point)
		while(num_edges_in_clusters<(num_nodes-k)){//we want to keep going until #edges = V-k
			if(!isCycle(components, graph[edge_idx].end1, graph[edge_idx].end2)){
				union_components(components, graph[edge_idx].end1, graph[edge_idx].end2); 
				num_edges_in_clusters++;
			}
		
			edge_idx++;
		}
		
		//we are out of the while loop when we have k clusters. so now the very first edge that's not creating a cycle is
		//the min spacing edge. 
		while(edge_idx<num_edges){
			if(!isCycle(components, graph[edge_idx].end1, graph[edge_idx].end2)){
				spacing = graph[edge_idx].len;
				break;
			}
			edge_idx++;
		}
			
		return spacing;	
	}
	
	int main(int argc, char* argv[]){
		int num_nodes, num_edges;
		char* filename = "clustering2.txt";
		
		graph_stats(filename, &num_nodes, &num_edges);
		
		struct component* my_components = create_components(num_nodes); 

		struct edge* my_graph = read_graph(filename, num_edges); 
		
		int max_spacing = k_cluster(4, num_edges, my_graph, num_nodes, my_components);
			
		printf("\n~~~ Okay done. Max spacing is %d~~~\n", max_spacing);
		return 0;
	}
