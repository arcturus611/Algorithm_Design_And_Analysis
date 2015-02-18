	/*
	Breadth First Search	
	*/

	#include<stdio.h>
	#include<stdlib.h>
	#include "queue.h"
	#include "graph.h"

	void test_queue(void){
	
		int no, ch, e;
		 
		printf("\n 1 - Enque");
		printf("\n 2 - Deque");
		printf("\n 3 - Front element");
		printf("\n 4 - Empty");
		printf("\n 5 - Exit");
		printf("\n 6 - Display");
		printf("\n 7 - Queue size");
		create_queue();
		while (1)
		{
			printf("\n Enter choice : ");
			scanf("%d", &ch);
			switch (ch)
			{
			case 1:
			    printf("Enter data : ");
			    scanf("%d", &no);
			    enqueue(no);
			    break;
			case 2:
			    dequeue();
			    break;
			case 3:
			    e = queue_front();
			    if (e != -1)
				printf("Front element : %d", e);
			    else
				printf("\n No front element in Queue as queue is empty");
			    break;
			case 4:
			    if(is_queue_empty()) printf("Empty\n"); 
			    else printf("Not empty!\n");
			    break;
			case 5:
			    exit(0);
			case 6:
			    display_queue();
			    break;
			case 7:
			    printf("The queue size is %d\n", queue_size());
			    break;
			default:
			    printf("Wrong choice, Please enter correct choice  ");
			    break;
			}
		}	
		
		return;
	}
	

	void test_graph(void){
		int V = 8;
		struct graph* G = read_graph(V);
		print_graph(G);
		return;
	}
	
	void breadth_first_search(struct graph* G, int s){
		//following Tim Roughgarden's notation
		int queue_front_idx;
		struct adj_list_node* curr_neighbour = NULL; 
		
		//Mark node s as explored
		G->array[s].explored = 1; 
		
		//Initialize queue with node s in it
		create_queue(); 
		enqueue(s);
		
		//While queue is not empty, 
		while(!is_queue_empty()){
//		for(int i = 0; i<10; i++){
			//Remove first node v from it, storing the value of node idx
			queue_front_idx = queue_front();
			printf("Front of queue is %d\n", queue_front_idx);
			dequeue(); 
			
			//For all neighbours of this first node:
			curr_neighbour = G->array[queue_front_idx].head;
			while(curr_neighbour){
				printf("Current neighbour is %d\n", curr_neighbour->idx); 
				//If not already explored, mark the neighbour as explored
				if(!(G->array[curr_neighbour->idx].explored)){
					G->array[curr_neighbour->idx].explored = 1;
					
					//Put neighbour in queue
					enqueue(curr_neighbour->idx);
				}
				
				display_queue();
				
				//Tackle next neighbour
				curr_neighbour = curr_neighbour->next;
			}
		} 
		
		for(int i = 0; i<8; i++){
			if(G->array[i].explored) printf("Explored node %d\n", i);
			else printf("Node %d unexplored\n", i); 
		}
		
		return;
	}
	
	int main(int argc, char* argv[]){
		int V = 8; 
		struct graph* G = read_graph(V); 
		
		int first_node_idx = 2; 
		breadth_first_search(G, first_node_idx);
		
		return 0;
	}
