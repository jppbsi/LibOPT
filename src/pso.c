#include "pso.h"

/* PSO-related functions */
/* It updates the velocity of an agent (particle)
Parameters:
S: search space
i: particle's index */ 
void UpdateParticleVelocity(SearchSpace *s, int i){
    double r1, r2;
    int j;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateParticleVelocity.\n");
        exit(-1);
    }
    
    r1 = GenerateUniformRandomNumber(0,1);
    r2 = GenerateUniformRandomNumber(0,1);
    
    for(j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->w*s->a[i]->v[j]+s->c1*r1*(s->a[i]->xl[j]-s->a[i]->x[j])+s->c2*r2*(s->g[j]-s->a[i]->x[j]);    
}

/* It updates the position of an agent (particle)
Parameters:
S: search space
i: particle's index */ 
void UpdateParticlePosition(SearchSpace *s, int i){
    int j;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateParticlePosition.\n");
        exit(-1);
    }
    
    for(j = 0; j < s->n; j++)
        s->a[i]->x[j] = s->a[i]->x[j]+s->a[i]->v[j];
}

/* It executes the Particle Swarm Optimization for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runPSO(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i;
    double beta, prob;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runPSO.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _PSO_, Evaluate, arg); /* Initial evaluation */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);
            
        /* for each particle */
        for(i = 0; i < s->m; i++){
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }
	        			
	EvaluateSearchSpace(s, _PSO_, Evaluate, arg);
	        
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/

/* AIWPSO-related functions */
/* It executes the Particle Swarm Optimization with Adpative Inertia Weight for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runAIWPSO(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i;
    double beta, prob;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runAIWPSO.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, _PSO_, Evaluate, arg); /* Initial evaluation */
    
    for(i = 0; i < s->m; i++)
        s->a[i]->pfit = s->a[i]->fit;
    
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);
            
        /* for each particle */
        for(i = 0; i < s->m; i++){
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }
	        			
	EvaluateSearchSpace(s, _PSO_, Evaluate, arg);
        prob = ComputeSuccess(s); /* Equations 17 and 18 */
        s->w = (s->w_max-s->w_min)*prob+s->w_min; /* Equation 20 */
        
        va_copy(arg, argtmp);            
	
        for(i = 0; i < s->m; i++)
            s->a[i]->pfit = s->a[i]->fit;
        
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}

/* It computes the pecentage of success concerning the whole search space
Parameters:
s: search space */
double ComputeSuccess(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @ComputeSuccess.\n");
        exit(-1);
    }
    
    int i;
    double p = 0;
    
    for(i = 0; i < s->m; i++){
        if(s->a[i]->fit < s->a[i]->pfit) p++;
    }
    
    return p/s->m;
}
/****************************/