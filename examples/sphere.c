#include "opt.h"
#include "common.h"
#include "function.h"

int main(){
    
    SearchSpace *s = NULL;
    
    double r = GenerateRandomNumber(-20,20);
    
    s = CreateSearchSpace(10, 2, _PSO_); /* It creates a search space with 10 agents for a 2-D problem. We are going to use PSO to solve it. */
    
    /* It initalizes the boundaries of decision variables */
    s->LB[0] = -10; s->LB[1] = -10; 
    s->UB[0] = 10; s->UB[1] = 10;
    /******/
    
    InitializeSearchSpace(s); /* It initalizes the search space */
    ShowSearchSpace(s); /* It shows the search space */
    
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
    
    return 0;
}