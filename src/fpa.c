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
        
    EvaluateSearchSpace(s, _FPA_, Evaluate, arg); /* Initial evaluation of the search space */
        
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
       
       fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/****************************/

/* It executes the Tensor-based Flower Pollination Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorFPA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, k, flower_j, flower_k;
    double prob, epsilon, *L = NULL, fitValue;
    double **tmp_t = NULL;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runTensorFPA.\n");
        exit(-1);
    }
        
    EvaluateTensorSearchSpace(s, _FPA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */
        
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
            
        /* for each flower */
       for(i = 0; i < s->m; i++){
            va_copy(arg, argtmp);
            tmp = CopyAgent(s->a[i], _FPA_);
            tmp_t = AllocateTensor(s->n, _QUATERNION_);
            for(j = 0; j < s->n; j++)
                for(k = 0; k < tensor_id; k++)
                    tmp_t[j][k] = s->a[i]->t[j][k];
            
            prob = GenerateUniformRandomNumber(0,1);
            if(prob > s->p){ /* large-scale pollination */
                L = GenerateLevyDistribution(s->n, s->beta);
                
                /* Equation 1 */
                for(j = 0; j < s->n; j++)
                    for(k = 0; k < tensor_id; k++)
                        tmp_t[j][k] = tmp_t[j][k]+L[j]*(tmp_t[j][k]-s->t_g[j][k]);
                /**************/
                
                free(L);
            }else{ /* local pollination */
                epsilon = GenerateUniformRandomNumber(0,1);
                flower_j = GenerateUniformRandomNumber(0, s->m-1);
                flower_k = GenerateUniformRandomNumber(0, s->m-1);
                
                /* Equation 3 */
                for(j = 0; j < s->n; j++)
                    for(k = 0; k < tensor_id; k++)
                        tmp_t[j][k] = tmp_t[j][k]+epsilon*(s->a[flower_j]->t[j][k]-s->a[flower_k]->t[j][k]);
            }
            CheckTensorLimits(s, tmp_t, tensor_id);
            for(j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);
                
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
                s->a[i]->fit = fitValue;
                for(j = 0; j < s->n; j++){
                    s->a[i]->x[j] = tmp->x[j];
                    for(k = 0; k < tensor_id; k++)
                        s->a[i]->t[j][k] = tmp_t[j][k];
                }
            }
            
            if(fitValue < s->gfit){ /* update the global best */
                s->gfit = fitValue;
                for(j = 0; j < s->n; j++){
                    s->g[j] = tmp->x[j];
                    for(k = 0; k < tensor_id; k++)
                        s->t_g[j][k] = tmp_t[j][k];
                }
            }
            
            DestroyAgent(&tmp, _FPA_);
            DeallocateTensor(&tmp_t, s->n);
       }
       fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    va_end(arg);
}
/****************************/