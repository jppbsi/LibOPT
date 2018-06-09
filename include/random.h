/*Copyright 2018 LibOpt Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
double randCauchy(double location, double scale); /* It returns a number drawn from a Cauchy distribution */
#endif
