#include "ba.h"

/* It updates the velocity of an agent (bat)
Parameters:
S: search space
i: particle's index */
void UpdateBatVelocity(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateBatVelocity.\n");
        exit(-1);
    }
     
    int j;
    
    for(j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->a[i]->v[j]+(s->a[i]->x[j]-s->g[j])*s->a[i]->f;
}

/* It sets the frequency of an agent (bat)
Parameters:
S: search space
i: particle's index */ 
void SetBatFrequency(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @SetBatFrequency.\n");
        exit(-1);
    }
    
    double beta = GenerateRandomNumber(0,1);
    s->a[i]->f = s->f_min+(s->f_max-s->f_min)*beta;
}

/* It evaluates the entire search space
Parameters:
s: search space
EvaluateFun: pointer to the function used to evaluate particles (agents)
arg: list of additional arguments */
void EvaluateBats(SearchSpace *s, prtFun Evaluate, va_list arg){
    va_list argtmp;
    int i, j;
    double fit;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @EvaluateBats.\n");
        exit(-1);
    }
    
    va_copy(argtmp, arg);
    for(i = 0; i < s->m; i++){
        fit = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */
                    
        s->a[i]->fit = fit;
        if(s->a[i]->fit < s->gfit){ /* It updates the global best value and position */
            s->gfit = s->a[i]->fit;
        
            for(j = 0; j < s->n; j++)
                s->g[j] = s->a[i]->x[j];
        }
        
        va_copy(arg, argtmp);
    }
}

/* It generates an agent (bat) near the best one
 * This code was based on the one available at http://www.mathworks.com/matlabcentral/fileexchange/37582-bat-algorithm--demo-
Paremeters:
s: search space */
Agent *GenerateNewBatNearBest(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @GenerateNewBatNearBest.\n");
        exit(-1);
    }
    
    Agent *a = NULL;
    int j;
    
    a = CreateAgent(s->n, _BA_);
    for(j = 0; j < s->n; j++)
        a->x[j] = s->g[j]+0.001*GenerateRandomNumber(0,1); /* The factor 0.001 limits the step sizes of random walks */ 
    
    return a;
}

/* It executes the Bat Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runBA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double beta, prob, fitValue;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runBA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, Evaluate, arg); /* Initial evaluation of the search space */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
            
        /* for each bat */
       for(i = 0; i < s->m; i++){
            va_copy(arg, argtmp);
            SetBatFrequency(s, i); /* Equation 1 */
            UpdateBatVelocity(s, i); /* Equation 2 */
            
            /* Equation 3
            Here, we generate a temporary agent (bat) */
            tmp = CopyAgent(s->a[i], _BA_);
            for(j = 0; j < s->n; j++)
                tmp->x[j] = tmp->x[j]+tmp->v[j];
            /**************/
            
            CheckAgentLimits(s, s->a[i]);
            
            prob = GenerateRandomNumber(0,1);
            if(prob > s->r){
                DestroyAgent(&tmp, _BA_);
                tmp = GenerateNewBatNearBest(s);
            }
            
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _BA_);
                s->a[i] = CopyAgent(tmp, _BA_);
                s->a[i]->fit = fitValue;
            }
            
            DestroyAgent(&tmp, _BA_);
        }
	        			
	//EvaluateBats(s, Evaluate, arg);
	        
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/