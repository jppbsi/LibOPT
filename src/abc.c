#include "abc.h"

/* It executes the Artificial Bee Colony for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runABC(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int i, j, k, t, chosen_param, neighbour, *trial, max_trial_index, max_fitness, limit;
    double r, fitValue, *prob;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runABC.\n");
        exit(-1);
    }
    
    limit = s->limit;
    trial = (int *)calloc(s->m, sizeof(int));
    
    EvaluateSearchSpace(s, _ABC_, Evaluate, arg); /* Initial evaluation of the search space */
      
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
	
	/* Employed Bee step */
	for (i = 0; i < s->m; i++){ /* For each food source */
	    va_copy(arg, argtmp);
	    
	    chosen_param = GenerateUniformRandomNumber(0, s->n-1); /* Randomly parameter to be used */
	    do {
		neighbour = GenerateUniformRandomNumber(0, s->m-1); /* Randomly neighbour to be used, which must be different from i */
	    } while (neighbour == i);
	    r = GenerateUniformRandomNumber(0, 1);
	    
	    tmp = CopyAgent(s->a[i], _ABC_);
	    tmp->x[chosen_param] = s->a[i]->x[chosen_param] + (s->a[i]->x[chosen_param] - s->a[neighbour]->x[chosen_param]) * r; /* We now update our currently solution */
	    CheckAgentLimits(s, tmp);
	    
	    fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
            if(fitValue < s->a[i]->fit){ /* We accept the new solution */
		trial[i] = 0;
		DestroyAgent(&(s->a[i]), _ABC_);
                s->a[i] = CopyAgent(tmp, _ABC_);
                s->a[i]->fit = fitValue;
            }
	    else {
		trial[i]++; /* If the solution could not be improved, we increase the trial counter */
	    }
            if(fitValue < s->gfit){ /* Update the global best */
		s->gfit = fitValue;
		for(j = 0; j < s->n; j++)
		    s->g[j] = tmp->x[j];
	    }
            DestroyAgent(&tmp, _ABC_);
	}
	/*
	prob = (double *)calloc(s->m, sizeof(double));
	
	/* Calculation of new probabilities */
	max_fitness = s->a[0]->fit;
	for (i = 1; i < s->m; i++)
	    if (s->a[i]->fit > max_fitness)
		max_fitness = s->a[i]->fit;
	for (i = 0; i < s->m; i++)
	    prob[i] = (0.9 * (s->a[i]->fit / max_fitness)) + 0.1;	
	    
	/* Onlooker Bee step */
	i = 1;
	k = 0;
	while (k < s->m){
	    r = GenerateUniformRandomNumber(0, 1);
	    if(r < prob[i]){
		va_copy(arg, argtmp);
		k++;
		chosen_param = GenerateUniformRandomNumber(0, s->n-1); /* Randomly parameter to be used */
		do {
		    neighbour = GenerateUniformRandomNumber(0, s->m-1); /* Randomly neighbour to be used, which must be different from i */
		} while (neighbour == i);
		
		tmp = CopyAgent(s->a[i], _ABC_);
		tmp->x[chosen_param] = s->a[i]->x[chosen_param] + (s->a[i]->x[chosen_param] - s->a[neighbour]->x[chosen_param]) * r; /* We now update our currently solution */
		CheckAgentLimits(s, tmp);
		
		fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
		if(fitValue < s->a[i]->fit){ /* We accept the new solution */
		    trial[i] = 0;
		    DestroyAgent(&(s->a[i]), _ABC_);
		    s->a[i] = CopyAgent(tmp, _ABC_);
		    s->a[i]->fit = fitValue;
		}
		else {
		    trial[i]++; /* If the solution could not be improved, we increase the trial counter */
		}
		if(fitValue < s->gfit){ /* Update the global best */
		    s->gfit = fitValue;
		    for(j = 0; j < s->n; j++)
			s->g[j] = tmp->x[j];
		}
		DestroyAgent(&tmp, _ABC_);
	    }
	    i++;
	    if (i == s->m)
		i = 0;
	}
	
	/* Scout Bee step */
	max_trial_index = 0;
	for (i = 0; i < s->m; i++)
	    if (trial[i] > trial[max_trial_index])
		max_trial_index = i;
	if(trial[max_trial_index] >= limit){
	    va_copy(arg, argtmp);
	    trial[max_trial_index] = 0;
	    tmp = GenerateNewAgent(s, _ABC_);
	    CheckAgentLimits(s, tmp);
	    fitValue = Evaluate(tmp, arg); /* It executes the fitness function for new created agent */
	    if(fitValue < s->a[max_trial_index]->fit){ /* We accept the new solution */
		DestroyAgent(&(s->a[max_trial_index]), _ABC_);
                s->a[max_trial_index] = CopyAgent(tmp, _ABC_);
                s->a[max_trial_index]->fit = fitValue;
            }
            if(fitValue < s->gfit){ /* update the global best */
		s->gfit = fitValue;
		for(j = 0; j < s->n; j++)
		    s->g[j] = tmp->x[j];
	    }
            DestroyAgent(&tmp, _ABC_);
	}

	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    
    free(trial);
    free(prob);
    va_end(arg);
}
/*************************/