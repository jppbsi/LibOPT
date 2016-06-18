#include "gp.h"

/* It executes the Genetic Programming for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runGP(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, n_reproduction, n_mutation, n_crossover;
    int *reproduction = NULL, *mutation = NULL, *crossover = NULL;
    double beta, prob;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runGP.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _GP_, Evaluate, arg); /* Initial evaluation */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        
	/* Calcultating the number of individuals to be reproducted */
	n_reproduction = round(s->m*s->pReproduction);
	reproduction = RouletteSelection(s, n_reproduction);
	
	/* Calcultating the number of individuals to be mutated */
	n_mutation = round(s->m*s->pMutation);
	mutation = RouletteSelection(s, n_mutation);
	
	/* Calcultating the number of individuals to perform the crossover */
	n_crossover = s->m-(n_reproduction+n_mutation);
	crossover = RouletteSelection(s, n_crossover);
		
	//for(i = 0; i < s->m; i++){
	  //  va_copy(arg, argtmp);
	//}
	
	free(reproduction);
	free(mutation);
	free(crossover);
	
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/