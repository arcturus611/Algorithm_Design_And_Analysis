	/*
	Implementing queue and its functions 
	(create_queue, queue_size, enqueue, dequeue, 
	is_queue_empty, display_queue, queue_front)
	*/
	
	#define MAIN_QUEUE_FILE
	#include<stdio.h>
	#include<stdlib.h>
	#include "queue.h"

	void create_queue(void){
		front = rear = NULL; 
		return;
	}
	
	void enqueue(int data){
		
		if (rear!=NULL){
			temp = (struct queue *)malloc(sizeof(struct queue)); 
			temp->idx = data; 
			temp->next = NULL; 
			
			rear->next = temp; 
			rear = temp; 
			
			queue_count++;
		}else{
			rear = (struct queue *)malloc(sizeof(struct queue));
			rear->idx = data; 
			rear->next = NULL; 
			
			front = rear; 
			
			queue_count++;
		}
		
		return;
	}
	
	void dequeue(void){
		front1 = front; 
		
		if(front1==NULL) printf("Error: Dequeueing an empty queue!\n");
		else{
			if(front1->next != NULL){
				front1 = front1->next; 
				printf("Dequeued data is %d\n", front->idx);
				free(front); 
				front = front1;
				queue_count--;
			}else{
				printf("Dequeued data is %d\n", front->idx);
				free(front); 
				front = NULL; 
				rear = NULL; 
				queue_count--;
			
			}
		
		}
		
		return;
	}
	
	int is_queue_empty(void){
		if((front == NULL) && (rear == NULL))
			return 1; 
		else return 0; 
	}
	
	int queue_size(void){
		return queue_count; //queue_count global
	}
	
	int queue_front(void){
		if(front==NULL)
			return -1; 
		else 
			return front->idx; 
	
	}
	
	void display_queue(void){
		front1 = front; //use front1 so we don't disturb front
		
		if(front1==NULL)
			printf("Queue is empty\n");
		else{
			printf("\nThe present queue is ");
			while(front1->next != NULL){
				printf("%d -> ", front1->idx); 
				front1 = front1->next;  
			}
			printf("%d", front1->idx); 
		
		}
	
		return;
	}
	
