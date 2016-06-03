#include "ba.h"

/* It updates the velocity of an agent (bat)
Parameters:
S: search space
i: particle's index */
void UpdateBatVelocity(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @UpdateBatVelocity.\n");
        exit(-1);
    }
     
    int j;
    
    for(j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->a[i]->v[j]+(s->a[i]->x[j]-s->g[j])*s->a[i]->f;
}

/* It sets the frequency of an agent (bat)
Parameters:
S: search space
i: particle's index */ 
void SetBatFrequency(SearchSpace *s, int i){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @SetBatFrequency.\n");
        exit(-1);
    }
    
    double beta = GenerateRandomNumber(0,1);
    s->a[i]->f = s->f_min+(s->f_max-s->f_min)*beta;
}