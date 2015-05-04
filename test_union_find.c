	
	#include<stdio.h>
	#include<stdlib.h>
	#include "union_find.h"
	
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
			    printf("How many components? : ");
			    scanf("%d", &x);
			    A = create_components(x);
			    break;
			case 2:
			    printf("Which component do you want to find? (0 to N-1) : ");
			    scanf("%d", &x);
			    printf("Parent of %d is %d\n", x, find_component(A, x));
			    break;
			case 3:
			    printf("Which components to merge? (indices): "); 
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
