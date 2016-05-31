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
            break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroyAgent.\n");
            break;
    }
    
    free(tmp);
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
    
    switch (opt_id){
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroySearchSpace.\n");
            break;       
    }
    
    free(tmp);
}
/**************************/
