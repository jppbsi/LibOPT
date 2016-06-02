#include "function.h"

/* It computes the equation of a 2-D sphere
Parameters:
a: agent
---
Minimum at f(0,0) = 0
Domain: -infty < x,y < +infty */
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

/* It computes the Rosenbrock's function
Parameters:
a: agent
---
Minimum at f(1,1) = 0
Domain: -infty < x,y < +infty */
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

/* It computes the Dixon-Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x_i = 2^{-/frac{2^i-2}{2^i}}
Domain: -infty < x,y < +infty */
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