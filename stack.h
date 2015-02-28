	/*
	stack functions header
	*/
	
	#ifndef STACK_FUNCTIONS_H
	#define STACK_FUNCTIONS_H
	
	// defining globals
	#ifdef MAIN_STACK_FILE
		int stack_count;
	#else
		extern int stack_count;
	#endif
	
	// defining data structures
	struct stack{
		int idx; 
		struct stack* next; 
	};
	
	// ... more globals
	#ifdef MAIN_STACK_FILE
		struct stack* front, *temp;
	#else 
		extern struct stack* front, *temp; 
	#endif
	
	// function declarations
	void create_stack(void);
	
	void push_to_stack(int);
	int pop_from_stack(void);
	
	int stack_front(void);
	void display_stack(void);
	int stack_size(void);
	int is_stack_empty(void); 
	
	void destroy_stack(void);
	
	#endif
	
