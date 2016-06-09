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
Minimum at f(x*) = 0 at x* = (10, 10)
Domain: -10 <= x_i <= 10 */
double Brent(Agent *a, ...){
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

/* It computes the Three-Hump Camel function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -5 <= x_i <= 5 */
double Three_HumpCamel(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Three_HumpCamel.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Three_HumpCamel. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 2 * pow(a->x[0], 2) - 1.05 * pow(a->x[0], 4) + pow(a->x[0], 6) / 6 + a->x[0] * a->x[1] + pow(a->x[1], 2);
    
    return sum;
}

/* It computes the Six-Hump Camel function
Parameters:
a: agent
---
Minimum at f(x*) = -1.0316 at x* = (-0.0898, 0.7126) and (0.0898, -0.7126)
Domain: -5 <= x_i <= 5 */
double Six_HumpCamel(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Six_HumpCamel.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Six_HumpCamel. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = (4 - 2.1 * pow(a->x[0], 2) + pow(a->x[0], 4)/3) * pow(a->x[0], 2) + a->x[0] * a->x[1] + (4 * pow(a->x[1], 2) - 4) * pow(a->x[1], 2);
    
    return sum;
}

/* It computes the Chen's Bird function
Parameters:
a: agent
---
Minimum at f(x*) = -2000 at x* = (-7/18, -13/18)
Domain: -500 <= x_i <= 500 */
double Chen_Bird(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Chen_Bird.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Chen_Bird. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = -0.001 / (pow(0.001, 2) + pow(a->x[0] - 0.4 * a->x[1] - 0.1, 2)) - 0.001 / (pow(0.001, 2) + pow(2 * a->x[0] + a->x[1] - 1.5, 2));
    
    return sum;
}

/* It computes the Chen's V function
Parameters:
a: agent
---
Minimum at f(x*) = -2000 at x* = (-0.38889, 0.72222)
Domain: -500 <= x_i <= 500 */
double Chen_V(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Chen_V.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Chen_V. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = -0.001 / (pow(0.001, 2) + pow(pow(a->x[0], 2) + pow(a->x[1], 2) - 1, 2)) - 0.001 / (pow(0.001, 2) + pow(pow(a->x[0], 2) + pow(a->x[1], 2) - 0.5, 2)) - 0.001 / (pow(0.001, 2) + pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2));
    
    return sum;
}

/* It computes the Chichinadze's function
Parameters:
a: agent
---
Minimum at f(x*) = -43.3159 at x* = (5.90133, 0.5)
Domain: -30 <= x_i <= 30 */
double Chichinadze(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Chichinadze.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Chichinadze. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0], 2) - 12 * a->x[0] + 11 + 10 * cos(M_PI*a->x[0]/2) + 8 * sin(5*M_PI*a->x[0]/2) - pow(1/5, 0.5) * exp(-0.5 * pow(a->x[1] - 0.5, 2));
    
    return sum;
}

/* It computes the Chung Reynolds' function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, ..., 0)
Domain: -100 <= x_i <= 100 */
double Chung_Reynolds(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Chung_Reynolds.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Chung_Reynolds. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum += pow(a->x[i], 2);
    
    sum *= sum;
    
    return sum;
}

/* It computes the Colville's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 1, 1, 1)
Domain: -10 <= x_i <= 10 */
double Colville(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Colville.\n");
        return DBL_MAX;
    }
    
    if(a->n != 4){
        fprintf(stderr,"\nInvalid number of decision variables @Colville. It must be equal to four.\n");
        return DBL_MAX;
    }
    
    sum = 100 * pow(a->x[0] - pow(a->x[1], 2), 2) + pow(1 - a->x[0], 2) + 90 * pow(a->x[3] - pow(a->x[2], 2), 2) + pow(1 - a->x[2], 2) + 10.1 * (pow(a->x[1] - 1, 2) + pow(a->x[3] - 1, 2)) + 19.8 * (a->x[1] - 1) * (a->x[3] - 1);
    
    return sum;
}

/* It computes the Cross-in-Tray function
Parameters:
a: agent
---
Minimum at f(x*) = -2.06261 at x = (1.3494, -1.3494), (1.3494, 1.3494), (-1.3494, 1.3494) and (-1.3494, -1.3494)
Domain: -10 <= x_i < 10 */
double Cross_Tray(Agent *a, ...){
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

/* It computes the Csendes' function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, ..., 0
Domain: -1 <= x_i <= 1 */
double Csendes(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Csendes.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Csendes. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	sum += pow(a->x[i], 6) * (2 + sin(1/a->x[i]));
    
    return sum;
}

/* It computes the Cube's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-1, 1)
Domain: -10 <= x_i <= 10 */
double Cube(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Cube.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Cube. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = 100 * pow(a->x[1] - pow(a->x[0], 3), 2) + pow(1 - a->x[0], 2);
    
    return sum;
}

/* It computes the Damavandi's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (2, 2)
Domain: 0 <= x_i <= 14 */
double Damavandi(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Damavandi.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Damavandi. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = (1 - pow(fabs((sin(M_PI*(a->x[0] - 2)) * sin(M_PI*(a->x[1] - 2))) / (pow(M_PI, 2) * (a->x[0] - 2) * (a->x[1] - 2))), 5)) * (2 + pow(a->x[0] - 7, 2) + 2 * pow(a->x[1] - 7, 2));
    
    return sum;
}

/* It computes the Deckkers-Aarts' function
Parameters:
a: agent
---
Minimum at f(x*) = -24777 at x* = (0, 15) and (0, -15)
Domain: -20 <= x_i <= 20 */
double Deckkers_Aarts(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Deckkers_Aarts.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Deckkers_Aarts. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(10, 5) * pow(a->x[0], 2) + pow(a->x[1], 2) - pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2) + pow(10, -5) * pow(pow(a->x[0], 2) + pow(a->x[1], 2), 4);
    
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

/* It computes the Easom's function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* (PI, PI)
Domain: -100 <= x_i <= 100 */
double Easom(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Easom.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Easom. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = -cos(a->x[0])*cos(a->x[1])*exp(-pow(a->x[0] - M_PI, 2) - pow(a->x[1] - M_PI, 2));
	
    return sum;
}

/* It computes the El-Attar-Vidyasagar-Dutta's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.470427 at x* (2.842503, 1.920175)
Domain: -500 <= x_i <= 500 */
double ElAttar_VidyasagarDutta(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @ElAttar_VidyasagarDutta.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @ElAttar_VidyasagarDutta. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(pow(a->x[0], 2) + a->x[1] - 10, 2) + pow(a->x[0] + pow(a->x[1], 2) - 7, 2) + pow(pow(a->x[0], 2) + pow(a->x[1], 3) - 1, 2);
	
    return sum;
}

/* It computes the Egg Crate function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* (0, 0)
Domain: -5 <= x_i <= 5 */
double Eggcrate(Agent *a, ...){
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Eggcrate.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Eggcrate. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0], 2) + pow(a->x[1], 2) + 25 * (pow(sin(a->x[0]), 2) + pow(sin(a->x[1]), 2));
	
    return sum;
}

/* It computes the Egg Holder function
Parameters:
a: agent
---
Minimum at f(x*) = 959.64 at x* (512, 404.2319)
Domain: -512 <= x_i <= 512 */
double Eggholder(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Eggholder.\n");
        return DBL_MAX;
    }
    
    if(a->n < 2){
        fprintf(stderr,"\nInvalid number of decision variables @Eggholder. It must be equal or greater than two.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < (a->n) - 1; i++)
	sum += -(a->x[i+1] + 47) * sin(sqrt(fabs(a->x[i+1] + a->x[i]/2 + 47))) - a->x[i] * sin(sqrt(fabs(a->x[i] - (a->x[i+1] + 47))));
    	
    return sum;
}

/* It computes the Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 1 at x* (0, ..., 0)
Domain: -1 <= x_i <= 1 */
double Exponential(Agent *a, ...){
    int i;
    double partial_sum = 0, sum;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Exponential.\n");
        return DBL_MAX;
    }
    
    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Exponential. It must be equal or greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++)
	partial_sum += pow(a->x[i], 2);
	
    sum = -exp(-0.5 * partial_sum);
    	
    return sum;
}

/* It computes the 2-D Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* (0, 10)
Domain: 0 <= x_i <= 20 */
double EXP_2(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @EXP_2.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @EXP_2. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < 10; i++)
	sum += pow(exp(-i*a->x[0]/10) - 5 * exp(-i*a->x[1]/10) - exp(-i/10) + 5 * exp(-i), 2);
    	
    return sum;
}

/* It computes the Freudenstein's Roth function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* (5, 4)
Domain: -10 <= x_i <= 10 */
double Freudenstein_Roth(Agent *a, ...){
    int i;
    double sum = 0;
    
    if(!a){
        fprintf(stderr,"\nAgent not allocated @Freudenstein_Roth.\n");
        return DBL_MAX;
    }
    
    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Freudenstein_Roth. It must be equal to two.\n");
        return DBL_MAX;
    }
    
    sum = pow(a->x[0] - 13 + ((5 - a->x[1]) * a->x[1] - 2) * a->x[1], 2) + pow(a->x[0] - 29 + ((a->x[1] + 1) * a->x[1] - 14) * a->x[1], 2);
    	
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

/* It computes the Xin-She Yang's 1 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, .., 0)
Domain: -5 <= x_i <= 5 */
double XinShe_Yang_1(Agent *a, ...){
    int e, i;
    double sum = 0;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @XinShe_Yang_1.\n");
        return DBL_MAX;
    }

    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @XinShe_Yang_1. It must be greater than one.\n");
        return DBL_MAX;
    }
    
    for (i = 0; i < a->n; i++){
	e = GenerateUniformRandomNumber(0, 1);
	sum += e * pow(fabs(a->x[i]), (i+1));
    }

    return sum;
}

/* It computes the Xin-She Yang's 2 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, .., 0)
Domain: -2PI <= x_i <= 2PI */
double XinShe_Yang_2(Agent *a, ...){
    double sum = 0, sum1 = 0, sum2 = 0;
    int i;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @XinShe_Yang_2.\n");
        return DBL_MAX;
    }

    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @XinShe_Yang_2. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++){
        sum1 += fabs(a->x[i]);
        sum2 += sin(pow(a->x[i],2));
    }

    sum += (sum1) * exp(-sum2);

    return sum;
}

/* It computes the Xin-She Yang's 3 function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* = (0, .., 0) with m = 5 and beta = 15
Domain: -20 <= x_i <= 20 */
double XinShe_Yang_3(Agent *a, ...){
    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 1;
    int i, m = 5, beta = 15;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @XinShe_Yang_3.\n");
        return DBL_MAX;
    }

    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @XinShe_Yang_3. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++){
        sum1 += pow((a->x[i]/beta),2*m);
        sum2 += pow(a->x[i],2);
        sum3 *= pow(cos(a->x[i]),2);
    }

    sum = exp(-sum1) - (2*exp(-sum2)) * sum3;

    return sum;
}

/* It computes the Xin-She Yang's 4 function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* = (0, .., 0)
Domain: -10 <= x_i <= 10 */
double XinShe_Yang_4(Agent *a, ...){
    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    int i;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @XinShe_Yang_4.\n");
        return DBL_MAX;
    }

    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @XinShe_Yang_4. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++){
        sum1 += pow(sin(a->x[i]),2);
        sum2 += pow(a->x[i],2);
        sum3 += pow(sin(sqrt(fabs(a->x[i]))),2);
    }

    sum = (sum1 - exp(-sum2)) * exp(-sum3);

    return sum;
}

/* It computes the Zakharov's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, .., 0)
Domain: -5 <= x_i <= 10 */
double Zakharov(Agent *a, ...){
    double sum = 0, sum1 = 0, sum2 = 0;
    int i;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @Zakharov.\n");
        return DBL_MAX;
    }

    if(a->n < 1){
        fprintf(stderr,"\nInvalid number of decision variables @Zakharov. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++){
        sum1 += pow(a->x[i], 2);
        sum2 += (i+1) * a->x[i];
    }
    
    sum = sum1 + pow(0.5 * sum2, 2) + pow(0.5 * sum2, 4);
    
    return sum;
}

/* It computes the Zettl's function
Parameters:
a: agent
---
Minimum at f(x*) = -0.003791 at x* = (-0.0299, 0)
Domain: -5 <= x_i <= 10 */
double Zettl(Agent *a, ...){
    double sum = 0;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @Zettl.\n");
        return DBL_MAX;
    }

    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Zettl. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(pow(a->x[0], 2) + pow(a->x[1], 2) - 2 * a->x[0], 2) + 0.25 * a->x[0];

    return sum;
}

/* It computes the Zirilli's function
Parameters:
a: agent
---
Minimum at f(x*) = -0.3523 at x* = (-1.0465, 0)
Domain: -10 <= x_i <= 10 */
double Zirilli(Agent *a, ...){
    double sum = 0;

    if(!a){
        fprintf(stderr,"\nAgent not allocated @Zirilli.\n");
        return DBL_MAX;
    }

    if(a->n != 2){
        fprintf(stderr,"\nInvalid number of decision variables @Zirilli. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.25 * pow(a->x[0], 4) - 0.5 * pow(a->x[0], 2) + 0.1 * a->x[0] + 0.5 * pow(a->x[1], 2);

    return sum;
}