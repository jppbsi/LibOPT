#include "hs.h"

/* It executes the Harmony Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runHS(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double fitValue;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runHS.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _HS_, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

    	va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      tmp = GenerateNewAgent(s, _HS_);
      CheckAgentLimits(s, tmp);
      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}

/* It executes the Tensor-based Harmony Search for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runTensorHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j, l;
    double fitValue, r, signal, **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runTensorHS.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _HS_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for(t = 1; t <= s->iterations; t++){
      fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);

    	va_copy(arg, argtmp);

      qsort(s->a, s->m, sizeof(Agent**), SortAgent); /* Sorts all harmonies according to their fitness. First position gets the best harmony. */

      tmp = CreateAgent(s->n, _HS_);

      tmp_t = GenerateNewTensor(s, tensor_id);

      for(j = 0; j < s->n; j++){
          r = GenerateUniformRandomNumber(0, 1);
          if(s->HMCR >= r){
              i = GenerateUniformRandomNumber(0, s->m-1);
              r = GenerateUniformRandomNumber(0, 1);
              if(s->PAR >= r){
                  signal = GenerateUniformRandomNumber(0, 1);
                  r = GenerateUniformRandomNumber(0, 1);
                  if(signal >= 0.5)
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]+r*s->bw;
                  else
                      for(l = 0; l < tensor_id; l++)
                          tmp_t[j][l] = s->a[i]->t[j][l]-r*s->bw;
              }
          }else{
            for(l = 0; l < tensor_id; l++){
                r = (s->UB[j] - s->LB[j]) * GenerateUniformRandomNumber(0, 1) + s->LB[j];
                tmp_t[j][l] = r;
            }
          }
      }

      CheckTensorLimits(s, tmp_t, tensor_id);
      for(j = 0; j < s->n; j++)
          tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

      fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */

      if((fitValue < s->a[s->m-1]->fit)){ /* We accept the new solution */
        DeallocateTensor(&s->a[s->m-1]->t, s->n);
        DestroyAgent(&(s->a[s->m-1]), _HS_);
        s->a[s->m-1] = CopyAgent(tmp, _HS_);
        s->a[s->m-1]->fit = fitValue;
        s->a[s->m-1]->t = CopyTensor(tmp_t, s->n, tensor_id);
      }

      if(fitValue < s->gfit){ /* update the global best */
        s->gfit = fitValue;
        for(j = 0; j < s->n; j++)
          s->g[j] = tmp->x[j];
      }

      DestroyAgent(&tmp, _HS_);
      DeallocateTensor(&tmp_t, s->n);

      fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }

    va_end(arg);
}
