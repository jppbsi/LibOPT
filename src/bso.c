#include "bso.h"

/* BSO-related functions */

/* It clusters the agents and returns a pointer with the best agent's ID per cluster.
Parameters:
s: search space */
int *k_means(SearchSpace *s){
    int *best = NULL, i, j, r;
    char *is_chosen = NULL, OK;
    double **mean = NULL;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @k_means.\n");
        exit(-1);
    }
        
    best = (int *)malloc(s->k*sizeof(int));
    mean = (double **)malloc(s->k*sizeof(double *));
    is_chosen = (char *)calloc(s->m,sizeof(char));
    
    /* initializing k centers with samples choosen at random */
    for (i = 0; i < s->k; i++){
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
    
    for (i = 0; i < s->k; i++)
   	free(mean[i]);
    free(mean);
    free(is_chosen);
    
    return best;
}
/****************************/

/* It executes the Brain Storm Optimization for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runBSO(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int i, t;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runBSO.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _BSO_, Evaluate, arg); /* Initial evaluation */

    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each idea */
        for(i = 0; i < s->m; i++){
	    //k_means
        }

	//EvaluateSearchSpace(s, _PSO_, Evaluate, arg);

	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/