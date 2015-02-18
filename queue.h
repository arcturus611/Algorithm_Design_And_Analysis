	/*
	All queue related functions. Writing this for BFS, hopefully will be useful later too!
	*/
	
	#ifndef QUEUE_FUNCTIONS_H
	#define QUEUE_FUNCTIONS_H
	
	/* Defining all data structures and globals */
	#ifdef MAIN_QUEUE_FILE
		int queue_count; 
	#else 
		extern int queue_count; 
		//http://tinyurl.com/SO-extern
		//http://tinyurl.com/shared-globals-C
	#endif
	
	struct queue{
		int idx;
		struct queue* next; 
	}; 
		
	#ifdef MAIN_QUEUE_FILE		
		struct queue *front, *rear, *front1, *temp;	
	#else
		extern struct queue *front, *rear, *front1, *temp; 
	#endif 
	/* End of data structures */
	
	/* List of functions */
	void create_queue(void);
	
	void enqueue(int);
	void dequeue(void); 
	
	void display_queue(void); 
	int queue_front(void); 
	int queue_size(void);
	int is_queue_empty(void); 
	
	/* End of list of functions */
	
	#endif 
