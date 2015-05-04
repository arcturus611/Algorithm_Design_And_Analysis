	/*
		Pointer confusion
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	
	struct test_obj{
		int val;
	};
	
	void init_arr(int* x){
		for(int i = 0; i<10; i++)
			x[i] = i; 
		return;
	}
	
	void modify_arr(int* x){
		x[0] = 100;
		x[5] = 500;
		return;
	}
	
	void print_arr(int* x){
		for(int i = 0; i<10; i++)
			printf("%d, ", x[i]);  
		printf("\n");
		return;
	}
	
	void init_spl_arr(struct test_obj* x){
		for(int i = 0; i<10; i++)
			(x+i)->val = i; 
		return;
	}
	
	void modify_spl_arr(struct test_obj* x){
		x[0].val = 100;
		(x+5)->val = 500;
		return;
	}
	
	void print_spl_arr(struct test_obj* x){
		printf("Printing spl arr...\n");
		for(int i = 0; i<10; i++)
			printf("%d, ", x[i].val);  
		printf("\n");
		return;
	}
	
	
	
	int main(int argc, char* argv[]){
		/*int* A = (int *)malloc(10*sizeof(int)); 
		init_arr(A);
		print_arr(A);
		
		modify_arr(A);
		print_arr(A);*/
		
		struct test_obj* T = (struct test_obj* )malloc(10*sizeof(struct test_obj)); 
		init_spl_arr(T);
		print_spl_arr(T);
		
		modify_spl_arr(T);
		print_spl_arr(T);
		return 0;
	}
