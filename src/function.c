#include "function.h"

/* It computes the Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x_i = 0
Domain: -infty < x,y < +infty */
double Ackley(Agent *a, ...){
    int i;
    double alpha = 20, beta = 0.2, gamma = 2*M_PI;
    double sum = 0, sum_1 = 0, sum_2 = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Ackley.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Ackley. It must be greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++){
	sum_1 += pow(a->x[i], 2);
	sum_2 += cos(gamma*a->x[i]);
    }
    
    sum = -alpha*exp(-beta*sqrt((1/a->n)*sum_1)) - exp((1/a->n)*sum_2) + alpha + exp(1);
	
    return sum;
}

/* It computes the sixth Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 1)
Domain: -infty < x,y < +infty */
double Bukin_Sixth(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bukin_Sixth.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bukin_Sixth. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 100 * sqrt(fabs(a->x[1] - 0.01*pow(a->x[0], 2))) + 0.01 * fabs(a->x[0] + 10);
    
    return sum;
}

/* It computes the Cross-in-Tray function
Parameters:
a: agent
---
Minimum at f(x*) = -2.06261 at x = (1.3491, -1.3491), (1.3491, 1.3491), (-1.3491, 1.3491) and (-1.3491, -1.3491)
Domain: -infty < x,y < +infty */
double Cross_Tray(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Cross_Tray.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Cross_Tray. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = -0.0001 * pow((fabs(sin(a->x[0])*sin(a->x[1])*exp(fabs(100 - (sqrt(pow(a->x[0], 2)+pow(a->x[1], 2))/M_PI)))) + 1), 0.1);
    
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

/* It computes the Sphere's function
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