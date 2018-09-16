/*Copyright 2018 LibOpt Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef COMMON_H
#define COMMON_H

#include "random.h"

/* General-Purpose variables */
#define LINE_SIZE 128 /* It limits the number of characters in a line when reading from model files */
/*****************************/

/* It defines the node of the tree used to implement GP */
typedef struct _Node{
    char *elem; /* Content of the node */
    int status; /* It defines the status of a given node (TERMINAL|FUNCTION|CONSTANT|DATA) */
    int id; /* Identifier of the node (its position in the array of nodes -- it depends on its status) */
    char left_son; /* Flag to identify whether the node is a son placed on the left or on the right */
    struct _Node *right, *left, *parent; /* Pointers to the subtrees on the right, left and parent */
    double *val; /* used for Geometric Semantic GP */
}Node;

/* It defines a general-purpose structure */
typedef struct _Data{
    int id;
    double val;
}Data;

/* It defines the agent (solution) to be used for all optimization techniques */
typedef struct Agent_{
    /* common definitions */
    int n; /* number of decision variables */
    double *x; /* position */
    double fit; /* fitness value */
    double **t; /* tensor */

    /* PSO */
    double *v; /* velocity */
    double *xl; /* local best */

    /* AIWPSO, LOA */
    double pfit; /* fitness value of the previous iteration */

    /* TensorPSO */
    double **t_v; /* tensor velocity */
    double **t_xl; /* tensor local best */

    /* BA */
    double f; /* frequency */
    double r; /* pulse rate */
    double A; /* loudness */

    /* MBO */
    struct Agent_ **nb; /* array of pointers to neighbours */

    /* LOA */
    double *prev_x; /* position (associated with pfit) */
    double best_fit; /* best fitness value so far of the agent (associated with xl) */

    /* SA */
    double *LB; /* lower boundaries of each decision variable of that agent */
    double *UB; /* upper boundaries of each decision variable of that agent */

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
    double **t_g; /* global best tensor */
    int best; /* index of the best agent */
    double gfit; /* global best fitness */
    int is_integer_opt; /* integer-valued optimization problem? */
    int tensor_dim; /* dimension of the tensor */

    /* PSO */
    double w; /* inertia weight */
    double w_min; /* lower bound for w - used for adaptive inertia weight */
    double w_max; /* upper bound for w - used for adaptive inertia weight */
    double c1; /* c1 parameter */
    double c2; /* c2 parameter */

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

    /* GP and GA */
    double pReproduction; /* probability of reproduction */
    double pMutation; /* probability of mutation */
    double pCrossover; /* probability of crossover */

    /* WCA */
    int nsr; /* number of rivers */
    double dmax; /* raining process maximum distance */

    /* GP */
    int min_depth; /* minimum depth of a tree */
    int max_depth; /* maximum depth of a tree */
    int n_terminals; /* number of terminals */
    int n_functions; /* number of functions */
    int n_constants; /* number of constants */
    char **function; /* matrix with the functions' names */
    char **terminal; /* matrix with the terminals' names */
    double **constant; /* matrix with the random constants */
    Node **T; /* pointer to the tree */
    double *tree_fit; /* fitness of each tree (in GP, the number of agents is different from the number of trees) */

    /* TGP */
    double ***t_constant; /* matrix with the tensor-based random constants */
    
    /* MBO */
    int X; /* number of neighbour solutions to be shared with the next solution */
    int M; /* number of tours, i.e., the number of iterations for the leader */
    int leftSide; /* flag to know which bird will be changed */

    /* ABC */
    int limit; /* number of trial limits for each food source */

    /* HS */
    double HMCR; /* harmony memory considering rate */
    double PAR; /* pitch adjusting rate */
    double bw; /* bandwidth */

    /* IHS */
    double PAR_min, PAR_max; /* minimum and maximum pitch adjusting rate */
    double bw_min, bw_max; /* minimum and maximum bandwidth */
    
    /* BSO */
    double p_one_cluster; /* probability of selecting a cluster center */
    double p_one_center; /* probability of randomly selecting an idea from a probabilistic selected cluster */
    double p_two_centers; /* probability of of creating a random combination of two probabilistic selected clusters */

    /* MBO/BSO */
    int k; /* number of neighbours solutions to be considered for MBO or number of clusters for BSO */

    /* LOA */
    double sex_rate; /* percentage of female lions in each pride */
    double nomad_percent; /* percentage of nomad lions in the population */
    double roaming_percent; /* percentage of pride territory that will be visited by a male lion */
    double mating_prob; /* probability of a female mate with male */
    double imigration_rate; /* rate of females in a pride that will become nomads */
    int n_prides; /* number of prides */
    struct Pride{
        int n_females; /* number of females in a pride */
        int n_males; /* number of males in a pride */
        Agent **females; /* array of pointers to female lions from a pride */
        Agent **males; /* array of pointers to male lions from a pride */
    }*pride_id; /* array of prides */
    int n_female_nomads; /* number of nomad females */
    int n_male_nomads; /* number of nomad males */
    Agent **female_nomads; /* array of pointers to female nomad lions */
    Agent **male_nomads; /* array of pointers to male nomad lions */
    
    /* BSA */
    double mix_rate; /* controls the number of elements of individuals that will mutate in a trial  */
    int F; /* controls the amplitude of the search-direction matrix (oldS - s) */

    /* JADE */
    double c; /* rate of parameter adaptation */
    double p_greediness; /* determines the greediness of the mutation strategy */

    /* CoBiDE */
    double pb; /* probability to execute DE according to the covariance matrix learning */
    double ps; /* proportion of the individuals chosen from the current population to calculate the covariance matrix */

    /* ABO */
    double ratio_e; /*  */
    double step_e; /* */

    /* SA */
    int cooling_schedule_id; /* identification number of the cooling schedule used on SA */
    double init_temperature; /* Initial temperature of the system. If it is 0 (zero) or any value below, we will determine it automatically from the number of iterations. */
    double end_temperature; /* temperature that means the convergence of the algorithm (Generally = 1) */
    double func_param; /* extra parameter for the cooling schedule functions */

}SearchSpace;

typedef double (*prtFun)(Agent *, va_list arg); /* Pointer to the function used to evaluate agents */

/* Agent-related functions */
Agent *CreateAgent(int n, int opt_id, int tensor_dim); /* It creates an agent */
void DestroyAgent(Agent **a, int opt_id); /* It deallocates an agent */
void CheckAgentLimits(SearchSpace *s, Agent *a); /* It checks whether a given agent has excedeed boundaries */
Agent *CopyAgent(Agent *a, int opt_id, int tensor_dim); /* It copies an agent */
void EvaluateAgent(SearchSpace *s, Agent *a, int opt_id, prtFun Evaluate, va_list arg); /* It evaluate an agent according to each technique */
Agent *GenerateNewAgent(SearchSpace *s, int opt_id); /* It generates a new agent according to each technique */
void CopySearchSpaceAgents(SearchSpace *s, SearchSpace *oldS, int opt_id, int tensor_id); /* It copies the agents from s to oldS */
void Permutation(SearchSpace *s, int opt_id, int tensor_dim); /* It performs a SearchSpace permutation */
/**************************/

/* Search Space-related functions */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id, ...); /* It creates a search space */
void DestroySearchSpace(SearchSpace **s, int opt_id); /* It deallocates a search space */
void InitializeSearchSpace(SearchSpace *s, int opt_id); /* It initializes an allocated search space */
void ShowSearchSpace(SearchSpace *s, int opt_id); /* It shows a search space */
void EvaluateSearchSpace(SearchSpace *s, int opt_id, prtFun Evaluate, va_list arg); /* It evaluates a search space */
char CheckSearchSpace(SearchSpace *s, int opt_id); /* It checks whether a search space has been properly set or not */




/**************************/

/* General-purpose functions */
double GenerateUniformRandomNumber(double low, double high); /* It generates a random number drawn from a uniform distribution whithin [low,high] */
double GenerateGaussianRandomNumber(double mean, double variance); /* It generates a random number drawn from a Gaussian (normal) distribution */
double GenerateCauchyRandomNumber(double location, double scale); /* It generates a random number drawn from a Cauchy distribution */
double *GenerateLevyDistribution(int n, double beta); /* It generates an n-dimensional array drawn from a Levy distribution */
double EuclideanDistance(double *x, double *y, int n); /* It computes the Euclidean distance between two n-dimensional arrays */
double *GetPerpendicularVector(double *x, int n); /* It generates a perpendicular vector to a given vector */
void NormalizeVector(double *x, int n); /* It normalizes a given vector */
int SortAgent(const void *a, const void *b); /* It is used to sort by agent's fitness (asceding order of fitness) */
int SortDataByVal(const void *a, const void *b); /* It is used to sort an array of Data by asceding order of the variable val */
void WaiveComment(FILE *fp); /* It waives a comment in a model file */
SearchSpace *ReadSearchSpaceFromFile(char *fileName, int opt_id); /* It loads a search space with parameters specified in a file */
int getFUNCTIONid(char *s); /* It returns the identifier of the function used as input */
int *RouletteSelection(SearchSpace *s, int k); /* It selects k elements based on the roulette selection method */
int *RouletteSelectionGA(SearchSpace *s, int k); /* It selects k elements based on the roulette selection method */
/**************************/

/* Tree-related functions */
Node *CreateNode(char *value, int node_id, char status, ...); /* It creates a tree node */
Node *GROW(SearchSpace *s, int min_depth, int max_depth); /* It creates a random tree based on the GROW algorithm */
void DestroyTree(Node **T); /* It deallocates a tree */
void PrintTree2File(SearchSpace *s, Node *T, char *fileName); /* It stores a tree in a text file */
void PreFixPrintTree4File(SearchSpace *s, Node *T, FILE *fp); /* It performs a prefix search in tree and saves the nodes in a text file */
double *RunTree(SearchSpace *s, Node *T); /* It runs a given tree and outputs its solution array */
Node *CopyTree(Node *T); /* It copies a given tree */
void PreFixTravel4Copy(Node *T, Node *Parent); /* It performs a prefix travel on a tree */
int getSizeTree(Node *T); /* It returns the size of a tree (number of nodes) */
Node *Mutation(SearchSpace *s, Node *T, float p); /* It performs the mutation of a tree T */
Node **Crossover(Node *Father, Node *Mother, float p); /* It performs the crossover between father and mother trees */
Node *PreFixPositioningTree(Node *T, int pos, char *left_son, int status, int *ctr); /* It returns the parent of the pos-th node using a prefix travel */
Node *SGXB(SearchSpace *s, Node *T1_tmp, Node *T2_tmp); /* It performs the Geometric Semantic Genetic Programming crossover operator for boolean functions */
Node *SGMB(SearchSpace *s, Node *T_tmp); /* It performs the Geometric Semantic Genetic Programming mutation operator for boolean functions */
Node *SGXE(SearchSpace *s, Node *T1_tmp, Node *T2_tmp); /* It performs the Geometric Semantic Genetic Programming crossover operator for real-valued functions */
Node *SGME(SearchSpace *s, Node *T1_tmp, Node *T2_tmp); /* It performs the Geometric Semantic Genetic Programming mutation operator for real-valued functions */
/***********************/

/* Tensor-related functions */
double **CreateTensor(int n, int tensor_dim); /* It allocates a new tensor */
void DestroyTensor(double ***t, int n); /* It deallocates a tensor */
void InitializeTensorSearchSpace(SearchSpace *s, int tensor_id); /* It initializes an allocated search space with tensors */
void ShowTensorSearchSpace(SearchSpace *s, int tensor_id); /* It shows a search space with tensors */
void CheckTensorLimits(SearchSpace *s, double **t, int tensor_dim); /* It checks whether a given tensor has excedeed boundaries */
double **CopyTensor(double **t, int n, int tensor_id); /* It copies a given tensor */
double **GenerateNewTensor(SearchSpace *s, int tensor_id); /* It generates a new tensor */
double TensorNorm(double *t, int tensor_dim); /* It computes the norm of a given tensor */
double TensorSpan(double L, double U, double *t, int tensor_dim); /* It maps the tensor value to a real one bounded by [L,U] */
double TensorEuclideanDistance(double **t, double **s, int n, int tensor_id); /* It calculates the Euclidean Distance between tensors */
void EvaluateTensorSearchSpace(SearchSpace *s, int opt_id, int tensor_id, prtFun Evaluate, va_list arg); /* It evaluates a tensor-based search space */
double **RunTTree(SearchSpace *s, Node *T); /* It runs a given tensor-based tree and outputs its solution array */
void TensorPermutation(SearchSpace *s, int opt_id, int tensor_dim);  /* It performs a tensor-based SearchSpace permutation */
/***********************/

/* Simulated Annealing related functions */
/* Simulated Annealing (SA) Cooling Schedules */
enum SA_COOLING_SCHEDULES {
  BOLTZMANN_ANNEALING, /* basic SA cooling strategy */
  FAST_SCHEDULE_ANNEALING, /* Fast Schedule annealing */

  /* Add other cooling Schedule functions before TOTAL_COOLING_SCHEDULES item. */
  TOTAL_COOLING_SCHEDULES /* Number of cooling Schedules */
};

/* It returns the identifier of the function used as the SA Cooling Schedule */
int getCoolingScheduleId(char *s);
/***********************/

#endif
