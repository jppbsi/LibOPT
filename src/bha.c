#include "bha.h"

/* It executes the Black Hole Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate agents
arg: list of additional arguments */
void runBHA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue;
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
            
        
       
        va_copy(arg, argtmp);
        
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    va_end(arg);
}
