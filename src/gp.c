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
    Node **tmpTree = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runGP.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _GP_, Evaluate, arg); /* Initial evaluation */
    tmpTree = (Node **)malloc(s->m*sizeof(Node *));
    
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
	
	for(i = 0; i < s->m; i++)
	    tmpTree[i] = CopyTree(s->T[i]);
        
	/* Calcultating the number of individuals to be reproducted */
	n_reproduction = round(s->m*s->pReproduction);
	reproduction = RouletteSelection(s, n_reproduction);
	
	/* Calcultating the number of individuals to be mutated */
	n_mutation = round(s->m*s->pMutation);
	mutation = RouletteSelection(s, n_mutation);
	
	/* Calcultating the number of individuals to perform the crossover */
	n_crossover = s->m-(n_reproduction+n_mutation);
	crossover = RouletteSelection(s, n_crossover);
	
	/* It performs the reproduction */
	//for(i = 0; i < n_reproduction; i++)
	  //  s->T[i] = CopyTree(tmp_T[reproduction, i]);
		    
	//for(i = 0; i < s->m; i++){
	  //  va_copy(arg, argtmp);
	//}
	
	free(reproduction);
	free(mutation);
	free(crossover);
	
	for(i = 0; i < s->m; i++)
	    DestroyTree(&tmpTree[i]);
	
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    
    free(tmpTree);
    va_end(arg);
}
/*************************/