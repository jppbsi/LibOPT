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


#include "random.h"

/* The source code to generate random numbers was taken from http://www.physics.drexel.edu/courses/Comp_Phys/Physics-306/random.c. */

double ran2(int *idum)
{
    int j;
    int k;
    static int idum2 = 123456789;
    static int iy = 0;
    static int iv[NTAB];
    double temp;

    if (*idum <= 0)
    { // *idum < 0 ==> initialize
        if (-(*idum) < 1)
            *idum = 1;
        else
            *idum = -(*idum);
        idum2 = (*idum);

        for (j = NTAB + 7; j >= 0; j--)
        {
            k = (*idum) / IQ1;
            *idum = IA1 * (*idum - k * IQ1) - k * IR1;
            if (*idum < 0)
                *idum += IM1;
            if (j < NTAB)
                iv[j] = *idum;
        }
        iy = iv[0];
    }
    k = (*idum) / IQ1;
    *idum = IA1 * (*idum - k * IQ1) - k * IR1;
    if (*idum < 0)
        *idum += IM1;

    k = idum2 / IQ2;
    idum2 = IA2 * (idum2 - k * IQ2) - k * IR2;
    if (idum2 < 0)
        idum2 += IM2;

    j = iy / NDIV;
    iy = iv[j] - idum2;
    iv[j] = *idum;
    if (iy < 1)
        iy += IMM1;

    if ((temp = AM * iy) > RNMX)
        return RNMX;
    else
        return temp;
}

#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

static int randx = 0; /* copy of random seed (internal use only) */

/* It initializes the random number generator */
int srandinter(int seed)
{
    if (seed == 0)
        seed = (int)time(NULL); /* initialize from the system
						   clock if seed = 0 */
    randx = -abs(seed);
    return seed; /* return seed in case we need to repeat */
}

/* It returns a random number uniformly distributed within [a,b] */
double randinter(double a, double b)
{
    if (randx == 0)
        srandinter(0);
    return a + (b - a) * ((double)ran2(&randx));
}

/* It returns a number drawn from a Gaussian distribution
Parameters:
mean: mean of the distribution
variance: variance of the distribution */
double randGaussian(double mean, double variance)
{
    double v, x, y, r;

    do
    {
        x = (double)2 * randinter(1, 100) / 99;
        y = (double)2 * randinter(1, 100) / 99;
        r = x * x + y * y;
    } while (r >= 1 || r == 0);

    v = x * sqrt(-2 * log(r) / r) * variance + mean;

    return v;
}

/* It returns a number  number drawn from a Cauchy distribution
Parameters:
location: location of the distribution
scale: scale of the distribution */
double randCauchy(double location, double scale)
{
	double x, F;
    long k = 0;
    while (1) {
		x = (double) randinter(0.0, 1.0);
		F = 1/(M_PI*scale * (1.0 + pow((x-location)/scale, 2)));
		if (F > 1.0) 
		{
			F = 1.0;
			break;
		}
		if (F > 0) break;
		k = k+1;
		if (k > 10) 
		{
			F = 0.001;
			break;
		}
    }
	return F;
}



