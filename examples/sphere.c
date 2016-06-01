#include "opt.h"
#include "common.h"
#include "function.h"
#include "pso.h"

int main(){
    
    SearchSpace *s = NULL;
    
    double r = GenerateRandomNumber(-20,20);
    
    s = CreateSearchSpace(10, 2, _PSO_); /* It creates a search space with 10 agents for a 2-D problem. We are going to use PSO to solve it. */
    
    /* It initializes PSO parameters */
    s->w = 1.4;
    s->c1 = 1.4;
    s->c2 = 0.6;
    s->iterations = 10;
    
    /* It initalizes the boundaries of decision variables */
    s->LB[0] = 0; s->LB[1] = 0; 
    s->UB[0] = 1; s->UB[1] = 1;
    /******/
    
    InitializeSearchSpace(s); /* It initalizes the search space */
    runPSO(s, Sphere); /* It minimizes function Sphere */
    
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
    
    return 0;
}
