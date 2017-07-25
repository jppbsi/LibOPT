#include "bso.h"

/* BSO-related functions */

/* It clusters the agents and returns a pointer with the best agent's ID per cluster.
Parameters:
s: search space
k: number of clusters */
int *k_means(SearchSpace *s, int k){
    int *best = NULL, i, j, r;
    char *is_chosen = NULL, OK;
    double **mean = NULL;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @k_means.\n");
        exit(-1);
    }
    
    if (k < 1){
	fprintf(stderr,"\nInvalid input (k < 1) @k_means.\n");
        exit(-1);
    }
    
    best = (int *)malloc(k*sizeof(int));
    mean = (double **)malloc(k*sizeof(double *));
    is_chosen = (char *)calloc(s->m,sizeof(char));
    
    /* initializing k centers with samples choosen at random */
    for (i = 0; i < k; i++){
	    mean[i] = (double *)malloc(s->n*sizeof(double));
	    OK = j = 0;
	    do{
		j++;
		r = (int)GenerateUniformRandomNumber(0, s->m);
		if(!is_chosen[r]){
		    is_chosen[r] = 1;
		    OK = 1;
		}
	    }while((!OK) && (j <= s->m));
	    if(j > s->m){
		fprintf(stderr,"\nProblems initializing the k centers @k_means. Probably k is too large.\n");
		exit(-1);
	    }
	    for (j = 0; j < s->n; j++) mean[i][j] = s->a[r]->x[j];
    }
    
    for (i = 0; i < k; i++)
   	free(mean[i]);
    free(mean);
    free(is_chosen);
    
    return best;
}
/****************************/
