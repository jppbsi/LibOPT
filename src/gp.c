#include "gp.h"

/* It executes the Genetic Programming for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runGP(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, z, n_reproduction, n_mutation, n_crossover;
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
    ShowSearchSpace(s, _GP_);
    
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
	for(i = 0; i < n_reproduction; i++){
	    DestroyTree(&s->T[i]);
	    s->T[i] = CopyTree(tmpTree[reproduction[i]]);
	}
	
	/* It performs the mutation */
	z = 0;
	for(j = n_reproduction; j < n_reproduction+n_mutation; j++){
	    DestroyTree(&s->T[j]);
	    if(getSizeTree(tmpTree[mutation[z]]) > 1)
		s->T[j]= Mutation(s, tmpTree[mutation[z]], PROB_MUTATION_FUNCTION);
	    else s->T[j] = GROW(s, s->min_depth, s->max_depth);
	    z++;
	}
    	    
	free(reproduction);
	free(mutation);
	free(crossover);
	
	for(i = 0; i < s->m; i++)
	    DestroyTree(&tmpTree[i]);
	
	EvaluateSearchSpace(s, _GP_, Evaluate, arg);
	
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
	va_copy(arg, argtmp);
    }
    
    free(tmpTree);
    va_end(arg);
}
/*************************/