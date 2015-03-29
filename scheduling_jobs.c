	/*
		Scheduling jobs
		Your task in this problem is to run the greedy algorithm that schedules jobs in decreasing order of the difference (weight - length). Recall from lecture that this algorithm is not always optimal. IMPORTANT: if two jobs have equal difference (weight - length), you should schedule the job with higher weight first. You should report the sum of weighted completion times of the resulting schedule.
	*/
	
	#include<stdio.h>
	#include<stdlib.h>
	
	struct job_props{
		int length;
		int weight;
		float scheduling_prop; 
	};
	
	struct jobs_info{
		struct job_props* arr;
		int num;
	};
	
	struct jobs_info* read_job_properties(char* file_name){
		
		FILE* fp = fopen(file_name, "r");
		
		int arr_len; 
		fscanf(fp, "%d", &arr_len); 
		
		struct job_props* J = (struct job_props *)malloc(arr_len*sizeof(struct job_props));
		
		for(int i = 0; i<arr_len; i++){
			fscanf(fp, "%d %d", &((J+i)->weight), &((J+i)->length)); 
		}
		
		fclose(fp); 
		
		struct jobs_info* J_I = (struct jobs_info* )malloc(sizeof(struct jobs_info* ));
		J_I->arr = J;
		J_I->num = arr_len;
		
		return J_I;
	}
	
	void print_job_properties(struct job_props* J, int num){
		for(int i = 0; i<num; i++){
			printf("Job %d has length %d, weight %d, scheduling_prop %lf\n", i, (J+i)->length, (J+i)->weight, (J+i)->scheduling_prop);
		}
		printf("\n");
		return;
	}
	
	int cmpfnc_scheduling_prop(const void* a, const void* b){
		const struct job_props* a1 = (struct job_props* )a; 
		const struct job_props* b1 = (struct job_props* )b;
		return (((a1->scheduling_prop) < (b1->scheduling_prop))-((a1->scheduling_prop) > (b1->scheduling_prop)));
	}
		
	int cmpfnc_weights(const void* a, const void* b){
		const struct job_props* a1 = (struct job_props* )a; 
		const struct job_props* b1 = (struct job_props* )b;
		return (((a1->weight) < (b1->weight))-((a1->weight) > (b1->weight)));
	}
	
	void break_ties(struct job_props* J, int num){
		int last_start = -2;
		int last_end = -1; 
		int tie = 0;
		int curr_end;
		
		for(int i = 1; i<num; i++){
			if((J[i].scheduling_prop)==(J[i-1].scheduling_prop)){
				tie = 1;
				if(last_start<last_end)
					last_start = i-1;
				curr_end = i; 
			}
			else{				
				if(tie){	
					tie = 0; 
					last_end = curr_end; 
					qsort(J+last_start, last_end-last_start+1, sizeof(struct job_props), cmpfnc_weights);
				}	
			}
		}
		
		if(tie){	
			tie = 0; 
			last_end = curr_end; 
			qsort(J+last_start, last_end-last_start+1, sizeof(struct job_props), cmpfnc_weights);
		}	
		
		return;
	}
	
	long long int sub_optimal_schedule(struct job_props* J, int num){
	
		for (int i = 0; i<num; i++){
			(J+i)->scheduling_prop = (J+i)->weight - (J+i)->length;
		}
			
		qsort(J, num, sizeof(struct job_props), cmpfnc_scheduling_prop);
		
		break_ties(J, num);
		
		long long int weighted_completion_time = 0;
		long long int unweighted_completion_time = 0;
		for(int i = 0; i<num; i++){
			unweighted_completion_time+= (J+i)->length;
			weighted_completion_time+= (unweighted_completion_time)*((J+i)->weight);
		}
		return weighted_completion_time; 
	}
	
	long long int optimal_schedule(struct job_props* J, int num){
			
		for (int i = 0; i<num; i++){
			(J+i)->scheduling_prop = (float)((J+i)->weight)/((J+i)->length);
		}

		qsort(J, num, sizeof(struct job_props), cmpfnc_scheduling_prop);
				
		long long int weighted_completion_time = 0;
		long long int unweighted_completion_time = 0;
		for(int i = 0; i<num; i++){
			unweighted_completion_time+= (J+i)->length;
			weighted_completion_time+= (unweighted_completion_time)*((J+i)->weight);
		}

		return weighted_completion_time; 
	}
	
	int main(int argc, char* argv[]){
		char file_name[] = "jobs.txt";
		struct jobs_info* J_I = read_job_properties(file_name); 

		long long int optimal_total_weighted_completion_time = optimal_schedule(J_I->arr, J_I->num);
		long long int total_weighted_completion_time = sub_optimal_schedule(J_I->arr, J_I->num);
		printf("Weighted completion time optimal is %lld\n", optimal_total_weighted_completion_time); 
		printf("Suboptimal: %lld\n", total_weighted_completion_time); 
		return 0;
	}
	
