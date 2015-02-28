	/*
	Depth first search using stack
	gcc -g -O2 -std=c99 -D_GLIBCXX_DEBUG -Wall depth_first_search_using_stack.c stack.c graph.c -o depth_first_search_using_stack.bin
	*/
	
	#include "depth_first_search.h"
	#include "graph.h"
	#include "stack.h"
	
	void test_stack(void){
	    int no, ch, e;
	 
	    printf("\n 1 - Push");
	    printf("\n 2 - Pop");
	    printf("\n 3 - Top");
	    printf("\n 4 - Empty");
	    printf("\n 5 - Exit");
	    printf("\n 6 - Display");
	    printf("\n 7 - Stack Count");
	    printf("\n 8 - Destroy stack");
	 
	    create_stack();
	 
	    while (1)
	    {
		printf("\n Enter choice : ");
		scanf("%d", &ch);
	 
		switch (ch)
		{
		case 1:
		    printf("Enter data : ");
		    scanf("%d", &no);
		    push_to_stack(no);
		    break;
		case 2:
		    printf("Popping from stack pops out data %d\n", pop_from_stack());
		    break;
		case 3:
		    printf("Front of stack is %d\n", stack_front());
		    break;
		case 4:
		    if(is_stack_empty()) printf("Stack empty\n");
		    else printf("Stack not empty\n");
		    break;
		case 5:
		    exit(0);
		case 6:
		    display_stack();
		    break;
		case 7:
		    printf("The stack size is %d\n", stack_size());
		    break;
		case 8:
		    destroy_stack();
		    break;
		default :
		    printf(" Wrong choice, Please enter correct choice  ");
		    break;
		}
	    }
	}
	
	void depth_first_search(struct graph* G, int s){
		//local vars
		int top_int, next_unexplored_neighbour; 
		struct adj_list_node* curr_neighbour = NULL; 
	
		//Mark s as explored
		G->array[s].explored = 1; 
		
		//Initialize stack with s in it
		create_stack(); 
		push_to_stack(s); 
		
		//While stack is not empty
		while(!is_stack_empty()){
			//get top element and initialize its next unexplored neighbour to -1
			top_int = stack_front(); 
			next_unexplored_neighbour = -1;
			
			//Pick next unexplored neighbour
			curr_neighbour = G->array[top_int].head; 
			while(curr_neighbour){
				if(G->array[curr_neighbour->idx].explored)
					curr_neighbour = curr_neighbour->next;
				else{
					next_unexplored_neighbour = curr_neighbour->idx; 
					G->array[next_unexplored_neighbour].explored = 1; 
					push_to_stack(next_unexplored_neighbour);
					break; 
				}
			}
			
			//pop topmost element if all its neighbours are explored
			if(next_unexplored_neighbour==-1)
				pop_from_stack();
			
		}
	
		//Show explored nodes
		for(int i = 0; i<8; i++){
			if(G->array[i].explored) printf("Explored node %d\n", i);
			else printf("Node %d unexplored\n", i); 
		}
	
		return;
	}

	int main(int argc, char* argv[]){
		//test_stack();
		int V = 8;
		struct graph* G = read_graph(V); 
		depth_first_search(G, 2); 
		return 0;
	}
	
	
