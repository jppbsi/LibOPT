#include "fa.h"

/* It updates the position of an agent (firefly)
Parameters:
s: search space
firefly_id: particle's index */ 
void UpdateFireflyPosition(SearchSpace *s, int firefly_id){
    int i, j;
    double beta, distance, r;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateFireflyPosition.\n");
        exit(-1);
    }

    for(i = 0; i < s->m; i++){
        if(s->a[firefly_id]->fit > s->a[i]->fit){ /* It moves firefly firefly_id towards i */
            distance = EuclideanDistance(s->a[i]->x, s->a[firefly_id]->x, s->n); /* It obtains the euclidean distance by Equation 8 */
	    distance *= distance;
            beta = s->beta_0*exp(-s->gamma*distance); /* It obtains attractiveness by Equation 6 */
	    r = GenerateUniformRandomNumber(0,1);
	    r = 2 * (r - 0.5);
            for(j = 0; j < s->n; j++)
		s->a[firefly_id]->x[j] = s->a[firefly_id]->x[j] + beta * (s->a[i]->x[j] - s->a[firefly_id]->x[j]) + s->alpha * r; /* It updates the firefly position by Equation 9 */
        }
    }
}

/* It updates the position of the best agent (firefly)
Parameters: 
s: search space
best_firefly_id: best particle's index */ 
void UpdateBestFireflyPosition(SearchSpace *s, int best_firefly_id){
    int j;
    double r;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateBestFireflyPosition.\n");
        exit(-1);
    }
    
    r = GenerateUniformRandomNumber(0,1);
    r = 2 * (r - 0.5);
    for(j = 0; j < s->n; j++)
	s->a[best_firefly_id]->x[j] += (s->alpha * r);
}

/* It executes the Firefly Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runFA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, Evaluate, arg); /* Initial evaluation of the search space */
    qsort(s->a, s->m, sizeof(Agent**), CompareForQSort); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */
    
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
	       	
	for (i = 0; i < s->m; i++){
	    UpdateFireflyPosition(s, i); /* It updates all fireflies positions */
	    CheckAgentLimits(s, s->a[i]);
	}
	
	UpdateBestFireflyPosition(s, 0); /* It updates the best firefly position with a random controlled walk in order to avoid local optimum */
	CheckAgentLimits(s, s->a[0]);
	
	EvaluateSearchSpace(s, Evaluate, arg); /* Evaluates the new search space */
	qsort(s->a, s->m, sizeof(Agent**), CompareForQSort); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */
       
	va_copy(arg, argtmp);
       
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    
    va_end(arg);
}

/* It executes the Adaptative Firefly Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runAFA(SearchSpace *s, prtFun Evaluate, ...){
    va_list arg, argtmp;
    int t, i, j;
    double delta;
    Agent *tmp = NULL;
    		
    va_start(arg, Evaluate);
    va_copy(argtmp, arg);
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @runAFA.\n");
        exit(-1);
    }
        
    EvaluateSearchSpace(s, Evaluate, arg); /* Initial evaluation of the search space */
    qsort(s->a, s->m, sizeof(Agent**), CompareForQSort); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */
    
    for(t = 1; t <= s->iterations; t++){
        fprintf(stderr,"\nRunning iteration %d/%d ... ", t, s->iterations);
	
	delta = 1 - (0.0001 / (pow(0.9, (1/s->iterations)))); /* It controls the step size of the randomized parameter alpha */
	s->alpha = 1 - (delta * s->alpha);
       	
	for (i = 0; i < s->m; i++){
	    UpdateFireflyPosition(s, i); /* It updates all fireflies positions */
	    CheckAgentLimits(s, s->a[i]);
	}
	
	UpdateBestFireflyPosition(s, 0); /* It updates the best firefly position with a random controlled walk in order to avoid local optimum */
	CheckAgentLimits(s, s->a[0]);
	
	EvaluateSearchSpace(s, Evaluate, arg); /* Evaluates the new search space */
	qsort(s->a, s->m, sizeof(Agent**), CompareForQSort); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */
	       
	va_copy(arg, argtmp);
       
	fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    
    va_end(arg);
}
/*************************/