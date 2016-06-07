#include "function.h"

/* It computes the 1st Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, ..., 0)
Domain: -35 <= x_i <= 35 */
double Ackley_First(Agent *a, ...){
    int i;
    double alpha = 20, beta = 0.02, gamma = 2*M_PI;
    double sum = 0, sum_1 = 0, sum_2 = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Ackley_First.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Ackley_First. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++){
	sum_1 += pow(a->x[i], 2);
	sum_2 += cos(gamma*a->x[i]);
    }
    
    sum = -alpha*exp(-beta*sqrt((1/a->n)*sum_1)) - exp((1/a->n)*sum_2) + alpha + exp(1);
	
    return sum;
}

/* It computes the 2nd Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = -200 at x* = (0, 0)
Domain: -32 <= x_i <= 32 */
double Ackley_Second(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Ackley_Second.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Ackley_Second. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = -200 * exp(-0.02*sqrt(pow(a->x[0], 2)+pow(a->x[1], 2)));
	
    return sum;
}

/* It computes the 3rd Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = -219.1418 at x* = (0, -0.4)
Domain: -32 <= x_i <= 32 */
double Ackley_Third(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Ackley_Third.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Ackley_Third. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 200 * exp(-0.02*sqrt(pow(a->x[0], 2)+pow(a->x[1], 2))) + 5 * exp(cos(3*a->x[0]) + sin(3*a->x[1]));
	
    return sum;
}

/* It computes the Adjiman's function
Parameters:
a: agent
---
Minimum at f(x*) = -2.02181 at x* = (2, 0.10578)
Domain: -1 <= x_0 <= 2 and -1 <= x_1 <= 1 */
double Adjiman(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Adjiman.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Adjiman. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = cos(a->x[0])*sin(a->x[1]) - a->x[0]/(pow(a->x[1], 2) + 1);
	
    return sum;
}

/* It computes the 1st Alpine's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, ..., 0)
Domain: -10 <= x_i <= 10 */
double Alpine_First(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Alpine_First.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Alpine_First. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum += fabs(a->x[i]*sin(a->x[i]) + 0.1*a->x[i]);
    	
    return sum;
}

/* It computes the 2nd Alpine's function
Parameters:
a: agent
---
Minimum at f(x*) = 2.808^n at x* = (7.917, ..., 7.917)
Domain: -0 <= x_i <= 10 */
double Alpine_Second(Agent *a, ...){
    int i;
    double sum = 1;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Alpine_Second.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Alpine_Second. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum *= sqrt(a->x[i])*sin(a->x[i]);
    	
    return sum;
}

/* It computes the Bartels' Conn function
Parameters:
a: agent
---
Minimum at f(x*) = 1 at x* = (0, 0)
Domain: -500 <= x_i <= 500 */
double Bartels_Conn(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bartels_Conn.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bartels_Conn. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = fabs(pow(a->x[0], 2) + pow(a->x[1], 2) + a->x[0]*a->x[1]) + fabs(sin(a->x[0])) + fabs(cos(a->x[1]));
    	
    return sum;
}

/* It computes the Beale's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (3, 0.5)
Domain: -4.5 <= x_i <= 4.5 */
double Beale(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Beale.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Beale. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(1.5 - a->x[0] + a->x[0]*a->x[1], 2) + pow(2.25 - a->x[0] + a->x[0]*pow(a->x[1],2), 2) + pow(2.625 - a->x[0] + a->x[0]*pow(a->x[1],3), 2);
    	
    return sum;
}

/* It computes the 2-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP2(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Biggs_EXP2.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Biggs_EXP2. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    for (i = 1; i <= 10; i++)
	sum += pow(exp(-0.1*i*a->x[0]) - 5*exp(-0.1*i*a->x[1]) - (exp(-0.1*i) - 5*exp(10*0.1*i)), 2);
    
    return sum;
}

/* It computes the 3-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 5)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP3(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Biggs_EXP3.\n");
        return DBL_MAX;
    }
    
    if(a->n != 3){
        fprintf(stderr,"\nInvalid number of decision variables @Biggs_EXP3. It must be equal to three.\n");
        return DBL_MAX;
    }
    
    for (i = 1; i <= 10; i++)
	sum += pow(exp(-0.1*i*a->x[0]) - a->x[2]*exp(-0.1*i*a->x[1]) - (exp(-0.1*i) - 5*exp(10*0.1*i)), 2);
    
    return sum;
}

/* It computes the 4-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP4(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Biggs_EXP4.\n");
        return DBL_MAX;
    }
    
    if(a->n != 4){
        fprintf(stderr,"\nInvalid number of decision variables @Biggs_EXP4. It must be equal to four.\n");
        return DBL_MAX;
    }
    
    for (i = 1; i <= 10; i++)
	sum += pow(a->x[2]*exp(-0.1*i*a->x[0]) - a->x[3]*exp(-0.1*i*a->x[1]) - (exp(-0.1*i) - 5*exp(10*0.1*i)), 2);
    
    return sum;
}

/* It computes the 5-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5, 4)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP5(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Biggs_EXP5.\n");
        return DBL_MAX;
    }
    
    if(a->n != 5){
        fprintf(stderr,"\nInvalid number of decision variables @Biggs_EXP5. It must be equal to five.\n");
        return DBL_MAX;
    }
    
    for (i = 1; i <= 11; i++)
	sum += pow(a->x[2]*exp(-0.1*i*a->x[0]) - a->x[3]*exp(-0.1*i*a->x[1]) + 3*exp(-0.1*i*a->x[4]) - (exp(-0.1*i) - 5*exp(10*0.1*i) + 3*exp(-4*0.1*i)), 2);
    
    return sum;
}

/* It computes the 6-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5, 4, 3)
Domain: -20 <= x_i <= 20 */
double Biggs_EXP6(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Biggs_EXP6.\n");
        return DBL_MAX;
    }
    
    if(a->n != 6){
        fprintf(stderr,"\nInvalid number of decision variables @Biggs_EXP6. It must be equal to six.\n");
        return DBL_MAX;
    }
    
    for (i = 1; i <= 13; i++)
	sum += pow(a->x[2]*exp(-0.1*i*a->x[0]) - a->x[3]*exp(-0.1*i*a->x[1]) + a->x[5]*exp(-0.1*i*a->x[4]) - (exp(-0.1*i) - 5*exp(10*0.1*i) + 3*exp(-4*0.1*i)), 2);
    
    return sum;
}

/* It computes the Bird's function
Parameters:
a: agent
---
Minimum at f(x*) = -106.764537 at x* = (4,70104, 3.15294), (-1.58214, -3.13024)
Domain: -2PI <= x_i <= 2PI */
double Bird(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bird.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bird. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = sin(a->x[0])*exp(pow(1 - cos(a->x[1]), 2)) + cos(a->x[1])*exp(pow(1 - sin(a->x[0]), 2)) + pow(a->x[0] - a->x[1], 2);
    	
    return sum;
}

/* It computes the 1st Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_First(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bohachevsky_First.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bohachevsky_First. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0], 2) + 2*pow(a->x[1], 2) - 0.3*cos(3*M_PI*a->x[0]) - 0.4*cos(4*M_PI*a->x[1]) + 0.7;
    	
    return sum;
}

/* It computes the 2nd Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_Second(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bohachevsky_Second.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bohachevsky_Second. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0], 2) + 2*pow(a->x[1], 2) - (0.3*cos(3*M_PI*a->x[0])) * (0.4*cos(4*M_PI*a->x[1])) + 0.3;
    	
    return sum;
}

/* It computes the 3rd Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_Third(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bohachevsky_Third.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bohachevsky_Third. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0], 2) + 2*pow(a->x[1], 2) - 0.3*cos(3*M_PI*a->x[0] + 4*M_PI*a->x[1]) + 0.3;
    	
    return sum;
}

/* It computes the Booth's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 3)
Domain: -10 <= x_i <= 10 */
double Booth(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Booth.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Booth. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0] + 2*a->x[1] - 7, 2) + pow(2*a->x[0] + a->x[1] - 5, 2);
    	
    return sum;
}

/* It computes the Box-Betts Quadratic Sum function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1)
Domain: 0.9 <= x_0 <= 1.2, 9 <= x_1 <= 11.2 and 0.9 <= x_2 <= 1.2 */
double Box_Betts(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Box_Betts.\n");
        return DBL_MAX;
    }
    
    if(a->n != 3){
        fprintf(stderr,"\nInvalid number of decision variables @Box_Betts. It must be equal to three.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum += pow(exp(-0.1*(i+1)*a->x[0]) - exp(-0.1*(i+1)*a->x[1]) - exp(fabs(-0.1*(i+1) - exp(-(i+1)))*a->x[2]), 2);
	    	
    return sum;
}

/* It computes the Brent's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -10 <= x_i <= 10 */
double Brent(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Brent.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Brent. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0] + 10, 2) + pow(a->x[1] + 10, 2) + exp(-pow(a->x[0], 2) - pow(a->x[1], 2));
    	
    return sum;
}

/* It computes the Brown's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, ..., 0)
Domain: -1 <= x_i <= 4 */
double Brown(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Brown.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Brown. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < (a->n-1); i++)
	sum += pow(pow(a->x[i], 2), (pow(a->x[i+1], 2) + 1)) + pow(pow(a->x[i+1], 2), (pow(a->x[i], 2) + 1));
    	
    return sum;
}

/* It computes the 2nd Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 0)
Domain: -15 <= x_0 <= -5 and -3 <= x_1 <= 3 */
double Bukin_Second(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bukin_Second.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bukin_Second. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 100 * (a->x[1] - 0.01*pow(a->x[0], 2) + 1) + 0.01 * pow(a->x[0] + 10, 2);
    
    return sum;
}

/* It computes the 4th Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 0)
Domain: -15 <= x_0 <= -5 and -3 <= x_1 <= 3 */
double Bukin_Forth(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Bukin_Forth.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Bukin_Forth. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 100 * pow(a->x[1], 2) + 0.01 * fabs(a->x[0] + 10);
    
    return sum;
}

/* It computes the 6th Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 1)
Domain: -15 <= x_0 <= -5 and -3 <= x_1 <= 3 */
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
Minimum at f(x*) = -2.06261 at x = (1.3494, -1.3494), (1.3494, 1.3494), (-1.3494, 1.3494) and (-1.3494, -1.3494)
Domain: -10 <= x_i < 10 */
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
Domain: -10 <= x_i <= 10 */
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
Minimum at f(x*) = 0 at x* = (1, ..., 1)
Domain: -30 <= x_i <= 30 */
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
Minimum at f(x*) = 0 at x* = (0, ..., 0)
Domain: 0 <= x_i <= 10 */
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