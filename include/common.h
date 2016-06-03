#ifndef COMMON_H
#define COMMON_H

#include "opt.h"
#include "random.h"

/* It defines the agent (solution) to be used for all optimization techniques */
typedef struct Agent_{
    /* common definitions */
    int n; /* number of decision variables */
    double *x; /* position */
    double fit; /* fitness value */
    
    /* PSO */
    double *v; /* velocity */
    double *xl; /* local best */
    
    /* AIWPSO */
    double pfit; /* fitness value of the previous iteration */
    
    /* BA */
    double f; /* frequency */    
}Agent;

/* It defines the search space */
typedef struct SearchSpace_{
    /* common definitions */
    int m; /* number of agents (solutions) */
    int n; /* number of decision variables */
    int iterations; /* number of iterations for convergence */
    Agent **a; /* array of pointers to agents */
    double *LB; /* lower boundaries of each decision variable */
    double *UB; /* upper boundaries of each decision variable */
    double *g; /* global best agent */
    
    /* PSO */
    double w; /* inertia weight */
    double w_min; /* lower bound for w - used for adaptive inertia weight */
    double w_max; /* upper bound for w - used for adaptive inertia weight */
    double c1; /* c1 parameter */
    double c2; /* c2 parameter */
    double gfit; /* global best fitness */
    
    /* BA */
    double f_min; /* minimum frequency */
    double f_max; /* maximum frequency */


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
void ShowSearchSpace(SearchSpace *s); /* It shows a search space */
/**************************/

/* General-purpose functions */
double GenerateRandomNumber(double low, double high); /* It generates a random number whithin [low,high] */
void WaiveComment(FILE *fp); /* It waives a comment in a model file */
SearchSpace *ReadSearchSpaceFromFile(char *fileName, int opt_id); /* It loads a search space with parameters specified in a file */

/**************************/

typedef double (*prtFun)(Agent *, ...); /* Pointer to the function used to evaluate agents */

#endif