	/*
		Linked List data structure
		With a lot of help from the fantastic blog http://www.thegeekstuff.com/2012/08/c-linked-list-example/
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	
	struct node{
		int val;
		struct node* next; 
	};
	
	struct node* head = NULL;
	struct node* last = NULL; 
	
	struct node* create_node(int v){
		struct node* n = (struct node* )malloc(sizeof(struct node)); 
		if (n==NULL){
			printf("Error: Couldn't allocate memory for node\n");
			return NULL; 
		}
		
		n->val = v;
		n->next = NULL; 
		
		return n; 
	}
	
	struct node* create_list(int v){
		
		struct node* n = create_node(v);
	
		head = last = n; 
		return n; 
	}
	
	struct node* add_to_list(int v, int add_to_end){
		
		if(head==NULL){
			return create_list(v); 
		}
		
		struct node* n = create_node(v); 
		
		if(add_to_end){
			last->next = n; 
			last = n;
		}
		else{
			n->next = head; 
			head = n; 
		}
		
		return n; 	
	}
	
	struct node* find_in_list(int v, struct node** prev){
		struct node* ptr = head; 
		struct node* tmp = NULL; 
		int found = 0;
		
		while(ptr!=NULL){
			if(ptr->val == v){
				found = 1; 
				break;	
			}
			else{
				tmp = ptr; //keep a record of the previous pointer
				ptr = ptr->next;
			}
		}
	
		if(!found)
			return NULL;
		else{
			if (prev) 
				*prev = tmp; 
			return ptr; 
		}	
			
	}
	
	int delete_from_list(int val){
		struct node* prev = NULL; 
		struct node* del = NULL; 
		
		del = find_in_list(val, &prev); 
		if(del!=NULL){
			if(prev!=NULL)
				prev->next = del->next; 
			if(del==last)		
				last = prev;
			if(del==head)
				head = del->next;
				 
		}else{ //item to be deleted not in list
			return 0;
		}
		
		free(del);
		return 1; 
	}
	
	void print_list(void){
		struct node* ptr = head; 
		printf("Printing list...\n");
		while(ptr!=NULL){
			printf("%d\n", ptr->val);
			ptr = ptr->next;
		}
		printf("\nEnd of list...\n"); 
		return;
	}
	
	void test_linked_list(void){
	
		int no, ch, add_to_end;
		 
		printf("\n 1 - Create List");
		printf("\n 2 - Add to List");
		printf("\n 3 - Delete from List");
		printf("\n 4 - Display List");
		printf("\n 5 - Exit");
		while (1)
		{
			printf("\n Enter choice : ");
			scanf("%d", &ch);
			switch (ch)
			{
			case 1:
			    printf("Enter data : ");
			    scanf("%d", &no);
			    create_list(no);
			    break;
			case 2:
			    printf("Enter data : ");
			    scanf("%d", &no);
			    printf("Add to end? : ");
			    scanf("%d", &add_to_end);
			    add_to_list(no, add_to_end);
			    break;
			case 3:
			    printf("Enter data: "); 
			    scanf("%d", &no); 
			    delete_from_list(no); 
			    break;
			case 4:
			    print_list();
			    break;
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
		test_linked_list(); 
		return 0; 
	}
