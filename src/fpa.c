#include "fpa.h"

/* It executes the Flower Pollination Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFPA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double beta, prob, fitValue;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runFPA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, Evaluate, arg); /* Initial evaluation of the search space */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
            
        /* for each flower */
       for(i = 0; i < s->m; i++){
            va_copy(arg, argtmp);
       }
       
       va_copy(arg, argtmp);
       //EvaluateBats(s, Evaluate, arg);
       
       fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}