#include "bha.h"

/* It executes the Black Hole Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate agents
arg: list of additional arguments */
void runBHA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue, sum, rand, dist, radius;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runBHA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _BHA_, Evaluate, arg); /* Initial evaluation of the search space */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
            
        sum = 0;
	
        /* Changing the position of each star according to Equation 3 */
	for(i = 0; i < s->m; i++){
	    va_copy(arg, argtmp);
	    
	    rand = GenerateUniformRandomNumber(0,1);
	    
	    for(j = 0; j < s->n; j++)
		s->a[i]->x[j] += rand * (s->g[j] - s->a[i]->x[j]);
	    
	    CheckAgentLimits(s, s->a[i]);
	    s->a[i]->fit = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */
	    
	    tmp = CopyAgent(s->a[i], _BHA_);
	    if(s->a[i]->fit < s->gfit){
		fitValue = s->gfit;
		s->gfit = s->a[i]->fit;
		s->a[i]->fit = fitValue;
		for(j = 0; j < s->n; j++){
		    tmp->x[j] = s->g[j];
		    s->g[j] = s->a[i]->x[j];
		    s->a[i]->x[j] = tmp->x[j];
		}
	    }
	    DestroyAgent(&tmp, _BHA_);
	    sum = sum + s->a[i]->fit;
	}
	
	/* Event Horizon and evaluating the solutions */
	radius = s->gfit/sum;
	for(i = 0; i < s->m; i++){
	    dist = EuclideanDistance(s->g, s->a[i]->x, s->n); /* It obtains the euclidean distance */
	    if(dist > radius){
		DestroyAgent(&(s->a[i]), _BHA_);
		s->a[i] = GenerateNewAgent(s, _BHA_);
	    }
	}
        
        EvaluateSearchSpace(s, _BHA_, Evaluate, arg);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    va_end(arg);
}