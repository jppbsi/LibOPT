#ifndef COMMON_H
#define COMMON_H

#include "opt.h"

/* It defines the agent (solution) to be used for all optimization techniques */
typedef struct Agent_{
    /* common definitions */
    int n; /* number of decision variables */
    double *x; /* position */
    double f; /* fitness value */
    
    /* PSO */
    double *v; /* velocity */
    double *xl; /* local best */
}Agent;

/* It defines the search space */
typedef struct SearchSpace_{
    /* common definitions */
    int m; /* number of agents (solutions) */
    int n; /* number of decision variables */
    Agent **a; /* array of pointers to agents */
    double *LB; /* lower boundaries of each decision variable */
    double *UB; /* upper boundaries of each decision variable */
    
    /* PSO */
    double *g; /* global best */
    
}SearchSpace;

/* Agent-related functions */
Agent *CreateAgent(int n, int opt_id); /* It creates an agent */
void DestroyAgent(Agent **a, int opt_id); /* It deallocates an agent */
void CheckAgentLimits(SearchSpace *s, Agent *a); /* It checks whether a given agent has excedeed boundaries */
/**************************/

/* Search Space-related functions */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id); /* It creates a search space */
void DestroySearchSpace(SearchSpace **s, int opt_id); /* It deallocates a search space */
void InitializeSearchSpace(SearchSpace *s); /* It initializes an allocated search space */
/**************************/

/* General-purpose functions */
double GenerateRandomNumber(int low, int high); /* It generates a random number whithin [low,high] */
/**************************/

typedef double (*prtFun)(Agent *, ...); /* Pointer to the function used to evaluate agents */

#endif