	/*
		Union-Find data structure
		This data structure is a great way to speed up Kruskal's algorithm 
		from its O(mn) running time to O(mlogn) time.
		http://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
		Implemented using path compression and union by rank
	*/
	
	
	#include<stdio.h>
	#include<stdlib.h>
	
	struct component{
		int parent; 
		int rank;
	};
	
	struct component* create_components(int v){	
		//create an array of n components. 
		//these represent the nodes of the graph. 
		//we are looking at the graph separately from two perspectives: nodes and edges
		struct component* n = (struct component* )malloc(v*sizeof(struct component)); 
		if (n==NULL){
			printf("Error: Couldn't allocate memory for component array\n");
			return NULL; 
		}
		
		for(int i = 0; i<v; i++){
			(n+i)->parent = i;
			(n+i)->rank = 0; 
		}	
		
		return n; 
	}
	
	int find_component(struct component* comp_arr, int x){
		if(comp_arr[x].parent!=x){
			(comp_arr+x)->parent = find_component(comp_arr, comp_arr[x].parent); 
		}
		
		return comp_arr[x].parent; 
	}

	void union_components(struct component* comp_arr, int x, int y){
		//union of components containing x and y
		int xroot = find_component(comp_arr, x);
		int yroot = find_component(comp_arr, y); 
		if(comp_arr[xroot].rank<comp_arr[yroot].rank){
			comp_arr[xroot].parent = yroot;
		}else if(comp_arr[xroot].rank<comp_arr[yroot].rank){
			comp_arr[yroot].parent = xroot;
		}else{
			comp_arr[xroot].parent = yroot; 
			comp_arr[yroot].rank++;	
		}
	
	}
/*
	void print_component_parts(int root){
		struct node* ptr = head; 
		printf("Printing list...\n");
		while(ptr!=NULL){
			printf("%d\n", ptr->val);
			ptr = ptr->next;
		}
		printf("\nEnd of list...\n"); 
		return;
	}
	*/
	void test_union_find(void){
	
		int x, y, ch;
		struct component* A; 
		 
		printf("\n 1 - Create Components");
		printf("\n 2 - Find");
		printf("\n 3 - Union");
	//	printf("\n 4 - Display Component parts");
		printf("\n 5 - Exit");
		while (1)
		{
			printf("\n Enter choice : ");
			scanf("%d", &ch);
			switch (ch)
			{
			case 1:
			    printf("Enter data : ");
			    scanf("%d", &x);
			    A = create_components(x);
			    break;
			case 2:
			    printf("Enter data : ");
			    scanf("%d", &x);
			    printf("Parent of %d is %d\n", x, find_component(A, x));
			    break;
			case 3:
			    printf("Enter data: "); 
			    scanf("%d %d", &x, &y); 
			    union_components(A, x, y); 
			    break;
			/*case 4:
			    print_list();
			    break;*/
			case 5: 
			    exit(0); 
			default:
			    printf("Wrong choice, Please enter correct choice  ");
			    break;
			}
		}	
		
		return;
	}
	
	
	int main(int argc, char* argv[]){
		test_union_find(); 
		return 0; 
	}
