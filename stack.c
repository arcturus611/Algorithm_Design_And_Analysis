	/*
	Stack implementation- push, pop and display
	*/
	
	#define MAIN_STACK_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include "stack.h"
	
	void create_stack(void){
		front = NULL; 
		return;
	}
	
	void push_to_stack(int data){
		if(front==NULL){
			front = (struct stack *)malloc(sizeof(struct stack)); 
			front->idx = data;
			front->next = NULL; 
			stack_count++; 
		}else{
			temp = front; 
			front = (struct stack *)malloc(sizeof(struct stack));
			front->idx = data; 
			front->next = temp; 
			stack_count++;
		}
		return;
	}
	
	int pop_from_stack(void){
		if(front==NULL){
			printf("Error: Trying to pop empty stack!\n"); 
			return -1; //-1 indicates empty stack because we only put nodes in the stack, and they can only have non-neg indices
		}else{
			int pop_idx = front->idx; 
			temp = front; 
			temp = temp->next; 
			free(front); 
			front = temp; 
			stack_count--; 
			return pop_idx; 
		}
		return 0;
	}

	int stack_front(void){
		if(front!=NULL)
			return front->idx;
		else return -1;  
	}
	
	void display_stack(void){
		temp = front; 
		if(temp){
			while(temp->next){
				printf("%d -> ", temp->idx);
				temp = temp->next;
			}
			if(temp){
				printf("%d\n", temp->idx);
			}
		}else{
			printf("Stack empty\n"); 
		}
		return;
	}
	
	int is_stack_empty(void){
		if(front==NULL) return 1; 
		else return 0;
	}
	
	int stack_size(void){
		return stack_count; 
	}
	
	void destroy_stack(void){
		while(front){
			temp = front;
			temp = temp->next;
			free(front);
			front = temp; 
		}
		stack_count = 0; 
		return;
	}
