#include "common.h"

/* Agent-related functions */
/* It creates an agent
Parameters:
n: number of decision variables
opt_id: identifier of the optimization technique */
Agent *CreateAgent(int n, int opt_id){
    if((n < 1) || opt_id < 1){
        fprintf(stderr,"\nInvalid parameters @CreateAgent.\n");
        return NULL;
    }
    
    Agent *a = NULL;
    a = (Agent *)malloc(sizeof(Agent));
    a->v = NULL;
    
    switch (opt_id){
        case _PSO_:
            a->v = (double *)malloc(n*sizeof(double));
            a->xl = (double *)malloc(n*sizeof(double));
            break;
        default:
            free(a);
            fprintf(stderr,"\nInvalid optimization identifier @CreateAgent\n");
            return NULL;
    }
    
    a->x = (double *)malloc(n*sizeof(double));
    
    return a;
}

/* It deallocates an agent
Parameters:
a: address of the agent to be deallocated */
void DestroyAgent(Agent **a, int opt_id){
    Agent *tmp = NULL;
    
    tmp = *a;
    if(!tmp){
        fprintf(stderr,"\nAgent not allocated @DestroyAgent.\n");
        exit(-1);
    }
    
    if(tmp->x) free(tmp->x);
    
    switch (opt_id){
        case _PSO_:
            if(tmp->v) free(tmp->v);
            if(tmp->xl) free(tmp->xl);
            break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroyAgent.\n");
            break;
    }
    
    free(tmp);
}

/* It checks whether a given agent has excedeed boundaries
Parameters:
s: search space
a: agent */
void CheckAgentLimits(SearchSpace *s, Agent *a){
    if((!s) || (!a)){
        fprintf(stderr,"\nInvalid input parameters @CheckLimits.\n");
        exit(-1);
    }
    
    int j;
    for(j = 0; j < a->n; j++){
        if(a->x[j] < s->LB[j]) a->x[j] = s->LB[j];
        else if(a->x[j] > s->UB[j]) a->x[j] = s->UB[j];
    }
}
/**************************/

/* Search Space-related functions */
/* It creates a search space
Parameters:
m: number of agents
n: number of decision variables
opt_id: identifier of the optimization technique */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id){
    SearchSpace *s = NULL;
    
    if((m < 1) || (n < 1) || (opt_id < 1)){
        fprintf(stderr,"\nInvalid parameters @CreateSearchSpace.\n");
        return NULL;
    }
    int i;
    
    s = (SearchSpace *)malloc(sizeof(SearchSpace));
    s->m = m;
    s->n = n;
    
    s->a = (Agent **)malloc(s->m*sizeof(Agent *));
    s->a[0] = CreateAgent(s->n, opt_id);
    if(s->a[0]){ /* Here, we verify whether opt_id is valid or not. In the latter case, function CreateAgent returns NULL. */
        for(i = 1; i < s->m; i++)
            s->a[i] = CreateAgent(s->n, opt_id);
    }else{
        free(s->a);
        free(s);
        return NULL;
    }
    
    switch (opt_id){
        case _PSO_:
            s->g = (double *)malloc(s->n*sizeof(double));
            break;
    }
    
    s->LB = (double *)malloc(s->n*sizeof(double));
    s->UB = (double *)malloc(s->n*sizeof(double));
    
    return s;
}

/* It deallocates a search space
Parameters:
s: address of the search space to be deallocated */
void DestroySearchSpace(SearchSpace **s, int opt_id){
    SearchSpace *tmp = NULL;
    int i;
    
    tmp = *s;
    if(!tmp){
        fprintf(stderr,"\nSearch space not allocated @DestroySearchSpace.\n");
        exit(-1);
    }
    
    for(i = 0; i < tmp->m; i++)
        if(tmp->a[i]) DestroyAgent(&(tmp->a[i]), opt_id);
    free(tmp->a);
    
    if(tmp->LB) free(tmp->LB);
    if(tmp->UB) free(tmp->UB);
    
    switch (opt_id){
        case _PSO_:
            if(tmp->g) free(tmp->g);
            break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroySearchSpace.\n");
            break;       
    }
    
    free(tmp);
}

/* It initializes an allocated search space
Parameters:
s: search space */
void InitializeSearchSpace(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @InitializeSearchSpace.\n");
        exit(-1);
    }
    
    int i, j;
    #pragma omp parallel for
    for(i = 0; i < s->m; i++){
        for(j = 0; j < s->n; j++)
            s->a[i]->x[j] = (double)randinter((float)s->LB[j],(float) s->UB[j]);
    }
}

/* It shows a search space
Parameters:
s: search space */
void ShowSearchSpace(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @ShowSearchSpace.\n");
        exit(-1);
    }
    
    int i, j;
    fprintf(stderr,"\nSearch space with %d agents and %d decision variables\n", s->m, s->n);
    for(i = 0; i < s->m; i++){
        fprintf(stderr,"\nAgent %d-> ", i);
        for(j = 0; j < s->n; j++)
            fprintf(stderr,"x[%d]: %f   ", j, s->a[i]->x[j]);
    }
    fprintf(stderr,"\n-----------------------------------------------------\n");
}

/**************************/


/* General-purpose functions */
/* It generates a random number uniformly distributed between low and high
Parameters:
low: lower bound
high: upper bound
This algorithm has been inspired by: http://www.cprogramming.com/tutorial/random.html */
double GenerateRandomNumber(double low, double high){
    return randinter(low, high);
}
/**************************/

