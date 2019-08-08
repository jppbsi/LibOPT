#include "abo.h"

/* It executes the Artificial Butterfly Optimization for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate agents
arg: list of additional arguments */
void runABO(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k, sunspot = 0;
    double fitValue, rand, ratio = 0, step = 0, alpha = 0, D = 0;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runABO.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _ABO_, Evaluate, arg); /* Initial evaluation of the search space */

    qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all butterflies according to their fitness. First position gets the best sunspot. */

    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr, "\nRunning iteration %d/%d ... \n", t, s->iterations);

        ratio = 0.9-(0.9-s->ratio_e)*(t/s->iterations);
        sunspot = (int)s->m*ratio;
        
        /* sunspot flight mode */
        for(i = 0; i < sunspot; i++){

            va_copy(arg, argtmp);

            rand = round(GenerateUniformRandomNumber(-1, 1));
            k = round(GenerateUniformRandomNumber(0, sunspot - 1));

            for(j = 0; j < s->n; j++){
                s->a[i]->x[j] = s->a[i]->x[j] + (s->a[i]->x[j] - s->a[k]->x[j])*rand;
            }

            CheckAgentLimits(s, s->a[i]);

            tmp = CopyAgent(s->a[i], _ABO_, _NOTENSOR_);
                
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _ABO_);
                s->a[i] = CopyAgent(tmp, _ABO_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
            }

            DestroyAgent(&tmp, _ABO_);
        }

        /* canopy flight mode */
        step = 1-(1-s->step_e)*(t/s->iterations);
        for(i = sunspot; i < s->m; i++){
            
            va_copy(arg, argtmp);

            rand = round(GenerateUniformRandomNumber(0, 1));
            k = round(GenerateUniformRandomNumber(0, sunspot - 1));
            for(j = 0; j < s->n; j++){
                s->a[i]->x[j] = s->a[i]->x[j] + ((s->a[i]->x[j] - s->a[k]->x[j])/fabs(s->a[i]->x[j] - s->a[k]->x[j]))*(s->LB[j] - s->UB[j])*step*rand;
            }

            CheckAgentLimits(s, s->a[i]);

            tmp = CopyAgent(s->a[i], _ABO_, _NOTENSOR_);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _ABO_);
                s->a[i] = CopyAgent(tmp, _ABO_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
            }else{
                alpha = 2-(2-0.1)*(t/s->iterations);
                rand = round(GenerateUniformRandomNumber(0, 1));
                k = round(GenerateUniformRandomNumber(0, sunspot - 1));
                for(j = 0; j < s->n; j++){
                    D = fabs(2*rand*(s->a[k]->x[j] - s->a[i]->x[j]));
                    s->a[i]->x[j] = s->a[k]->x[j] - 2*alpha*rand - alpha*D;
                }
            }

            DestroyAgent(&tmp, _ABO_);

        }

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all butterflies according to their fitness. First position gets the best sunspot. */

        fprintf(stderr, "OK (minimum fitness value %lf)", s->a[0]->fit);
    }
    va_end(arg);
}
