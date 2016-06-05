#ifndef RANDOM_H
#define RANDOM_H

#include "opt.h"

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.e-14
#define RNMX (1.0-EPS)

double ran2(int *idum);
int srandinter(int seed); /* It initializes the random number generator */
double randinter(double a, double b); /* It returns a random number uniformly distributed between a and b */
double randGaussian(double mean, double variance); /* It returns a number drawn from a Gaussian distribution */

#endif