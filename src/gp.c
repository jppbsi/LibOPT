#include "gp.h"

/* It executes the Genetic Programming for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runGP(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i;
    double beta, prob;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runGP.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _GP_, Evaluate, arg); /* Initial evaluation */
        
    /*for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);
            
        /* for each particle */
        /*for(i = 0; i < s->m; i++){
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }
	        			
	EvaluateSearchSpace(s, _PSO_, Evaluate, arg);
        va_copy(arg, argtmp);            
	        
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }*/

    va_end(arg);
}
/*************************/