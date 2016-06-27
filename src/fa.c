#include "fa.h"

/* It executes the Firefly Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int i, j, k, t;
    double beta, delta = 0.97, distance;
    double r;
    Agent **tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runFA.\n");
        exit(-1);
    }
    
    tmp = (Agent **)malloc(s->m*sizeof(Agent *));
      
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
	
	EvaluateSearchSpace(s, _FA_, Evaluate, arg); /* Initial evaluation of the search space */
	for (i = 0; i < s->m; i++)
	    tmp[i] = CopyAgent(s->a[i], _FA_);
	qsort(tmp, s->m, sizeof(Agent**), SortAgent); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */
	
	for (i = 0; i < s->m; i++){
	    for(j = 0; j < s->m; j++){
		distance = EuclideanDistance(s->a[i]->x, tmp[j]->x, s->n); /* It obtains the euclidean distance for further use */
		distance *= distance;
		if(s->a[i]->fit > tmp[j]->fit){
		    beta = s->beta_0*exp(-s->gamma*distance); /* It obtains attractiveness by Equation 1 */
		    for(k = 0; k < s->n; k++){
			r = GenerateUniformRandomNumber(0,1);
			s->a[i]->x[k] = s->a[i]->x[k] + beta * (tmp[j]->x[k] - s->a[i]->x[k]) + s->alpha * (r - 0.5); /* It updates the firefly position by Equation 2 */
		    }
		}
	    }
	}
		
	for (i = 0; i < s->m; i++){
	    CheckAgentLimits(s, s->a[i]);
	    DestroyAgent(&tmp[i], _FA_);
	}
		
	va_copy(arg, argtmp);
       
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    
    free(tmp);
    va_end(arg);
}
/*************************/