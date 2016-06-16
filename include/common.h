#ifndef COMMON_H
#define COMMON_H

#include "opt.h"
#include "random.h"

/* It defines the node of the tree used to implement GP */
typedef struct _Node{
    char *elem; /* Content of the node */
    int status; /* It defines the status of a given node (TERMINAL|FUNCTION|CONSTANT) */
    int id; /* Identifier of the node (its position in the array of nodes -- it depends on its status) */
    char left_son; /* Flag to identify whether the node is a son placed on the left or on the right */
    struct _Node *right, *left, *parent; /* Pointers to the subtrees on the right, left and parent */
}Node;

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
    double r; /* pulse rate */
    double A; /* loudness */
    
    /* FPA */
    double beta; /* used to compute the step based on Levy Flight */
    double p; /* probability of local pollination */
    
    /* FA */
    double alpha; /* randomized parameter */
    double beta_0; /* attractiveness */
    double gamma; /* light absorption */
    
    /* GP */
    double pReproduction; /* probability of reproduction */
    double pMutation; /* probability of mutation */
    double pSelection; /* probability of selection */
    int min_depth; /* minimum depth of a tree */
    int max_depth; /* maximum depth of a tree */
    int n_terminals; /* number of terminals */
    int n_functions; /* number of functions */
    int n_constants; /* number of constants */
    char **function; /* matrix with the functions' names */
    char **terminal; /* matrix with the terminals' names */
    double *constant; /* array with the random constants */
    Node **T; /* pointer to the agent (tree) */
    
    /* GA */
    double pCrossOver; /* probability of crossover */
    double pMutate; /* probability of mutation */

}SearchSpace;

typedef double (*prtFun)(Agent *, ...); /* Pointer to the function used to evaluate agents */

/* Agent-related functions */
Agent *CreateAgent(int n, int opt_id); /* It creates an agent */
void DestroyAgent(Agent **a, int opt_id); /* It deallocates an agent */
void CheckAgentLimits(SearchSpace *s, Agent *a); /* It checks whether a given agent has excedeed boundaries */
Agent *CopyAgent(Agent *a, int opt_id); /* It copies an agent */
Agent *GenerateNewAgent(SearchSpace *s, int opt_id); /* It generates a new agent according to each technique */
/**************************/

/* Search Space-related functions */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id, ...); /* It creates a search space */
void DestroySearchSpace(SearchSpace **s, int opt_id); /* It deallocates a search space */
void InitializeSearchSpace(SearchSpace *s); /* It initializes an allocated search space */
void ShowSearchSpace(SearchSpace *s); /* It shows a search space */
void EvaluateSearchSpace(SearchSpace *s, prtFun Evaluate, va_list arg); /* It evaluates a search space */
/**************************/

/* General-purpose functions */
double GenerateUniformRandomNumber(double low, double high); /* It generates a random number drawn from a uniform distribution whithin [low,high] */
double GenerateGaussianRandomNumber(double mean, double variance); /* It generates a random number drawn from a Gaussian (normal) distribution */
double *GenerateLevyDistribution(int n, double beta); /* It generates an n-dimensional array drawn from a Levy distribution */
double EuclideanDistance(double *x, double *y, int n); /* It computes the Euclidean distance between two n-dimensional arrays */
int CompareForQSort(const void *a, const void *b); /* It computes the compare function by agent's fitness, which is used on Quick Sort (qsort) */
void WaiveComment(FILE *fp); /* It waives a comment in a model file */
SearchSpace *ReadSearchSpaceFromFile(char *fileName, int opt_id); /* It loads a search space with parameters specified in a file */
int getFUNCTIONid(char *s); /* It returns the identifier of the function used as input */
/**************************/

/* Tree-related functions */
Node *CreateNode(char *value, int node_id, char status); /* It creates a tree node */
Node *GROW(SearchSpace *s, int min_depth, int max_depth); /* It creates a random tree based on the GROW algorithm */
void DestroyTree(Node **T); /* It deallocates a tree */
void PrintTree2File(SearchSpace *s, Node *T, char *fileName); /* It stores a tree in a text file */
void PreFixPrintTree4File(SearchSpace *s, Node *T, FILE *fp); /* It performs a prefix search in tree and saves the nodes in a text file */
/***********************/

#endif