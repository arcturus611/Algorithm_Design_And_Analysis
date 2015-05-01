	/*
		Union-Find header
	*/
	
	#ifndef UNION_FIND_FUNCTIONS_H
	#define UNION_FIND_FUNCTIONS_H
	
	struct component{
		int parent; 
		int rank;
	};
	
	struct component* create_components(int);
	int find_component(struct component*, int); 
	void union_components(struct component*, int, int); 
	
	#endif
