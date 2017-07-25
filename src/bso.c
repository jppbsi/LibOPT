#include "bso.h"

/* BSO-related functions */

/* It clusters the agents and returns a pointer with the best agent's ID per cluster.
Parameters:
s: search space
k: number of clusters */
int *k_means(SearchSpace *s, int k){
    int *best = NULL;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @k_means.\n");
        exit(-1);
    }
    
    if (k < 1){
	fprintf(stderr,"\nInvalid input (k < 1) @k_means.\n");
        exit(-1);
    }
    
    return best;
}
/****************************/
