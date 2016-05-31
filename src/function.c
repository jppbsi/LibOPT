#include "function.h"

/* It computes the equation of a 2-D sphere
Parameters:
a: agent */
double Sphere(Agent *a, ...){
    double x, y;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Sphere.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Sphere. It must be 2.\n");
        return DBL_MAX;
    }
    
    x = a->x[0];
    y = a->x[1];
	
    return pow(x, 2) + pow(y, 2);
}