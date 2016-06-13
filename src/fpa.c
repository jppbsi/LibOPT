#include "fpa.h"

/* It executes the Flower Pollination Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFPA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, flower_j, flower_k;
    double prob, epsilon, *L = NULL, fitValue;
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
            tmp = CopyAgent(s->a[i], _FPA_);
            
            prob = GenerateUniformRandomNumber(0,1);
            if(prob > s->p){ /* large-scale pollination */
                L = GenerateLevyDistribution(s->n, s->beta);
                
                /* Equation 1 */
                for(j = 0; j < s->n; j++)
                    tmp->x[j] = tmp->x[j]+L[j]*(tmp->x[j]-s->g[j]);
                /**************/
                
                free(L);
            }else{ /* local pollination */
                epsilon = GenerateUniformRandomNumber(0,1);
                flower_j = GenerateUniformRandomNumber(0, s->m-1);
                flower_k = GenerateUniformRandomNumber(0, s->m-1);
                
                /* Equation 3 */
                for(j = 0; j < s->n; j++)
                    tmp->x[j] = tmp->x[j]+epsilon*(s->a[flower_j]->x[j]-s->a[flower_k]->x[j]);
            }
            CheckAgentLimits(s, tmp);
            
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
		DestroyAgent(&(s->a[i]), _FPA_);
                s->a[i] = CopyAgent(tmp, _FPA_);
                s->a[i]->fit = fitValue;
            }
            
            if(fitValue < s->gfit){ /* update the global best */
		s->gfit = fitValue;
		for(j = 0; j < s->n; j++)
		    s->g[j] = tmp->x[j];
	    }
            
            DestroyAgent(&tmp, _FPA_);
       }
       
       va_copy(arg, argtmp);
       
       fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}