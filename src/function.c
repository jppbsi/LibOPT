#include "function.h"

/* It computes the equation of a N-D sphere
Parameters:
a: agent */
double Sphere(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Sphere.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Sphere. It must be greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum += pow(a->x[i], 2); 
    	
    return sum;
}

/* It computes the equation of the Rosenbrock function
Parameters:
a: agent */
double Rosenbrock(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Rosenbrock.\n");
        return DBL_MAX;
    }
    
    if(a->n < 2){
        fprintf(stderr,"\nInvalid number of decision variables @Rosenbrock. It must be greater than two.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < (a->n - 1); i++)
	sum += 100 * (pow(a->x[i+1] - pow(a->x[i], 2), 2)) + pow(a->x[i] - 1, 2);
	
    return sum;
}

/* It computes the equation of the Dixon-Price function
Parameters:
a: agent */
double Dixon_Price(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Dixon_Price.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Dixon_Price. It must be greater than one.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0] - 1, 2);
    
    for (i = 1; i < a->n; i++)
	sum += (i+1) * pow((2 * pow(a->x[i], 2) - a->x[i-1]), 2);
	
    return sum;
}