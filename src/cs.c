#include "cs.h"

/* It computes the number of nests that will be replaced, taking into account a probability [0,1] */
int NestLossParameter(int size, float probability){
    int value, loss;
    value = size*probability;

    if(value + 0.5 > (int)value + 1)
        loss = (int)value;
    else
        loss = (int)value + 1;

    return loss;
}

/* It executes the Cuckoo Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runCS(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, nest_i, loss;
    double prob, epsilon, *L = NULL, fitValue;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runCS.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _CS_, Evaluate, arg); /* Initial evaluation of the search space */
    qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */
    
    for(t = 1; t <= s->iterations; t++){
    	fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
            
    	va_copy(arg, argtmp);
	tmp = GenerateNewAgent(s, _CS_);
	
	/* Equation 1 */
	L = GenerateLevyDistribution(s->n, s->beta);
	for(j = 0; j < s->n; j++)
		tmp->x[j] = tmp->x[j]+L[j]*(tmp->x[j]-s->g[j]);
	free(L);
	
	/**************/
	
	CheckAgentLimits(s, tmp);
	
	nest_i = GenerateUniformRandomNumber(0, s->m-1);
	
	fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
	if(fitValue < s->a[nest_i]->fit){ /* We accept the new solution */
	    DestroyAgent(&(s->a[nest_i]), _CS_);
	    s->a[nest_i] = CopyAgent(tmp, _CS_);
	    s->a[nest_i]->fit = fitValue;
	}
	
	DestroyAgent(&tmp, _CS_);
	
	qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */
	
	va_copy(arg, argtmp);
	fprintf(stderr, "OK (minimum fitness value %lf)", s->a[0]->fit);
    }
    
    va_end(arg);
}
