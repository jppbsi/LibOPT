#include "opt.h"
#include "common.h"
#include "function.h"

int main(){
    
    SearchSpace *s = NULL;
    
    double r = GenerateRandomNumber(-20,20);
    fprintf(stderr,"\nr %lf", r);
    s = CreateSearchSpace(10, 2, _PSO_); /* It creates a search space with 10 agents for a 2-D problem. We are going to use PSO to solve it. */
    
    DestroySearchSpace(&s, _PSO_);
    
    return 0;
}