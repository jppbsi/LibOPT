#ifndef COMMON_H
#define COMMON_H

#include "opt.h"

/* It defines the agent (solution) to be used
for all optimization techniques */
typedef struct Agent_{
    int n; /* number of decision variables */
    double *x; /* position */
    double *v; /* velocity */
    double f; /* fitness value */
}Agent;

/* It defines the search space */
typedef struct SearchSpace_{
    int m; /* number of agents (solutions) */
    int n; /* number of decision variables */
    Agent **a; /* array of pointers to agents */
}SearchSpace;

/* Agent-related functions */
Agent *CreateAgent(int n, int opt_id); /* It creates an agent */
void DestroyAgent(Agent **a, int opt_id); /* It deallocates an agent */
/**************************/

/* Search Space-related functions */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id); /* It creates a search space */
void DestroySearchSpace(SearchSpace **s, int opt_id); /* It deallocates a search space */
/**************************/

#endif