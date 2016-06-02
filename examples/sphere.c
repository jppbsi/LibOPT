#include "opt.h"
#include "common.h"
#include "function.h"
#include "pso.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
        
    s = CreateSearchSpace(10, 2, _PSO_); /* It creates a search space with 10 agents for a 2-D problem. We are going to use PSO to solve it. */
    
    /* It initializes PSO parameters */
    s->w = 1.4;
    s->c1 = 1.4;
    s->c2 = 0.6;
    s->iterations = 10;
    
    /* It initalizes the boundaries of decision variables within the range [-5.12,5.12] */
    for (i = 0; i < s->n; i++){
        s->LB[i] = -5.12;
        s->UB[i] = 5.12;
    }
    /******/
    
    InitializeSearchSpace(s); /* It initalizes the search space */
    runPSO(s, Sphere); /* It minimizes function Sphere */
    
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
    
    return 0;
}
