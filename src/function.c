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


#include "function.h"

/* Benchmark functions */
/* It computes the 1st Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -35 <= x_i <= 35 */
double Ackley_First(Agent *a, va_list arg)
{
    int i;
    double alpha = 20, beta = 0.02, gamma = 2 * M_PI;
    double sum = 0, sum_1 = 0, sum_2 = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Ackley_First.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Ackley_First. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        sum_1 += pow(a->x[i], 2);
        sum_2 += cos(gamma * a->x[i]);
    }

    sum = -alpha * exp(-beta * sqrt((1 / a->n) * sum_1)) - exp((1 / a->n) * sum_2) + alpha + exp(1);

    return sum;
}

/* It computes the 2nd Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = -200 at x* = (0, 0)
Domain: -32 <= x_i <= 32 */
double Ackley_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Ackley_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Ackley_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -200 * exp(-0.02 * sqrt(pow(a->x[0], 2) + pow(a->x[1], 2)));

    return sum;
}

/* It computes the 3rd Ackley's function
Parameters:
a: agent
---
Minimum at f(x*) = -219.1418 at x* = (0, -0.4)
Domain: -32 <= x_i <= 32 */
double Ackley_Third(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Ackley_Third.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Ackley_Third. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 200 * exp(-0.02 * sqrt(pow(a->x[0], 2) + pow(a->x[1], 2))) + 5 * exp(cos(3 * a->x[0]) + sin(3 * a->x[1]));

    return sum;
}

/* It computes the Adjiman's function
Parameters:
a: agent
---
Minimum at f(x*) = -2.02181 at x* = (2, 0.10578)
Domain: -1 <= x_0 <= 2 and -1 <= x_1 <= 1 */
double Adjiman(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Adjiman.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Adjiman. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = cos(a->x[0]) * sin(a->x[1]) - a->x[0] / (pow(a->x[1], 2) + 1);

    return sum;
}

/* It computes the 1st Alpine's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -10 <= x_i <= 10 */
double Alpine_First(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Alpine_First.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Alpine_First. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += fabs(a->x[i] * sin(a->x[i]) + 0.1 * a->x[i]);

    return sum;
}

/* It computes the 2nd Alpine's function
Parameters:
a: agent
---
Minimum at f(x*) = 2.808^n at x* = (7.917, va_list arg, 7.917)
Domain: 0 <= x_i <= 10 */
double Alpine_Second(Agent *a, va_list arg)
{
    int i;
    double sum = 1;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Alpine_Second.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Alpine_Second. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum *= sqrt(a->x[i]) * sin(a->x[i]);

    return sum;
}

/* It computes the Bartels' Conn function
Parameters:
a: agent
---
Minimum at f(x*) = 1 at x* = (0, 0)
Domain: -500 <= x_i <= 500 */
double Bartels_Conn(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bartels_Conn.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bartels_Conn. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = fabs(pow(a->x[0], 2) + pow(a->x[1], 2) + a->x[0] * a->x[1]) + fabs(sin(a->x[0])) + fabs(cos(a->x[1]));

    return sum;
}

/* It computes the Beale's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (3, 0.5)
Domain: -4.5 <= x_i <= 4.5 */
double Beale(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Beale.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Beale. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(1.5 - a->x[0] + a->x[0] * a->x[1], 2) + pow(2.25 - a->x[0] + a->x[0] * pow(a->x[1], 2), 2) + pow(2.625 - a->x[0] + a->x[0] * pow(a->x[1], 3), 2);

    return sum;
}

/* It computes the 2-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP2(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Biggs_EXP2.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Biggs_EXP2. It must be equal to two.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 10; i++)
        sum += pow(exp(-0.1 * i * a->x[0]) - 5 * exp(-0.1 * i * a->x[1]) - (exp(-0.1 * i) - 5 * exp(10 * 0.1 * i)), 2);

    return sum;
}

/* It computes the 3-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 5)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP3(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Biggs_EXP3.\n");
        return DBL_MAX;
    }

    if (a->n != 3)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Biggs_EXP3. It must be equal to three.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 10; i++)
        sum += pow(exp(-0.1 * i * a->x[0]) - a->x[2] * exp(-0.1 * i * a->x[1]) - (exp(-0.1 * i) - 5 * exp(10 * 0.1 * i)), 2);

    return sum;
}

/* It computes the 4-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP4(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Biggs_EXP4.\n");
        return DBL_MAX;
    }

    if (a->n != 4)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Biggs_EXP4. It must be equal to four.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 10; i++)
        sum += pow(a->x[2] * exp(-0.1 * i * a->x[0]) - a->x[3] * exp(-0.1 * i * a->x[1]) - (exp(-0.1 * i) - 5 * exp(10 * 0.1 * i)), 2);

    return sum;
}

/* It computes the 5-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5, 4)
Domain: 0 <= x_i <= 20 */
double Biggs_EXP5(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Biggs_EXP5.\n");
        return DBL_MAX;
    }

    if (a->n != 5)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Biggs_EXP5. It must be equal to five.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 11; i++)
        sum += pow(a->x[2] * exp(-0.1 * i * a->x[0]) - a->x[3] * exp(-0.1 * i * a->x[1]) + 3 * exp(-0.1 * i * a->x[4]) - (exp(-0.1 * i) - 5 * exp(10 * 0.1 * i) + 3 * exp(-4 * 0.1 * i)), 2);

    return sum;
}

/* It computes the 6-D Biggs' Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1, 5, 4, 3)
Domain: -20 <= x_i <= 20 */
double Biggs_EXP6(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Biggs_EXP6.\n");
        return DBL_MAX;
    }

    if (a->n != 6)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Biggs_EXP6. It must be equal to six.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 13; i++)
        sum += pow(a->x[2] * exp(-0.1 * i * a->x[0]) - a->x[3] * exp(-0.1 * i * a->x[1]) + a->x[5] * exp(-0.1 * i * a->x[4]) - (exp(-0.1 * i) - 5 * exp(10 * 0.1 * i) + 3 * exp(-4 * 0.1 * i)), 2);

    return sum;
}

/* It computes the Bird's function
Parameters:
a: agent
---
Minimum at f(x*) = -106.764537 at x* = (4,70104, 3.15294) or (-1.58214, -3.13024)
Domain: -2PI <= x_i <= 2PI */
double Bird(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bird.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bird. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = sin(a->x[0]) * exp(pow(1 - cos(a->x[1]), 2)) + cos(a->x[1]) * exp(pow(1 - sin(a->x[0]), 2)) + pow(a->x[0] - a->x[1], 2);

    return sum;
}

/* It computes the 1st Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_First(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bohachevsky_First.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bohachevsky_First. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) + 2 * pow(a->x[1], 2) - 0.3 * cos(3 * M_PI * a->x[0]) - 0.4 * cos(4 * M_PI * a->x[1]) + 0.7;

    return sum;
}

/* It computes the 2nd Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bohachevsky_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bohachevsky_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) + 2 * pow(a->x[1], 2) - (0.3 * cos(3 * M_PI * a->x[0])) * (0.4 * cos(4 * M_PI * a->x[1])) + 0.3;

    return sum;
}

/* It computes the 3rd Bohachevsky's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Bohachevsky_Third(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bohachevsky_Third.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bohachevsky_Third. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) + 2 * pow(a->x[1], 2) - 0.3 * cos(3 * M_PI * a->x[0] + 4 * M_PI * a->x[1]) + 0.3;

    return sum;
}

/* It computes the Booth's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 3)
Domain: -10 <= x_i <= 10 */
double Booth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Booth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Booth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0] + 2 * a->x[1] - 7, 2) + pow(2 * a->x[0] + a->x[1] - 5, 2);

    return sum;
}

/* It computes the Box-Betts Quadratic Sum function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 10, 1)
Domain: 0.9 <= x_0 <= 1.2, 9 <= x_1 <= 11.2 and 0.9 <= x_2 <= 1.2 */
double Box_Betts(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Box_Betts.\n");
        return DBL_MAX;
    }

    if (a->n != 3)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Box_Betts. It must be equal to three.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(exp(-0.1 * (i + 1) * a->x[0]) - exp(-0.1 * (i + 1) * a->x[1]) - exp(fabs(-0.1 * (i + 1) - exp(-(i + 1))) * a->x[2]), 2);

    return sum;
}

/* It computes the Brent's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (10, 10)
Domain: -10 <= x_i <= 10 */
double Brent(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Brent.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Brent. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0] + 10, 2) + pow(a->x[1] + 10, 2) + exp(-pow(a->x[0], 2) - pow(a->x[1], 2));

    return sum;
}

/* It computes the Brown's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -1 <= x_i <= 4 */
double Brown(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Brown.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Brown. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < (a->n - 1); i++)
        sum += pow(pow(a->x[i], 2), (pow(a->x[i + 1], 2) + 1)) + pow(pow(a->x[i + 1], 2), (pow(a->x[i], 2) + 1));

    return sum;
}

/* It computes the 2nd Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 0)
Domain: -15 <= x_0 <= -5 and -3 <= x_1 <= 3 */
double Bukin_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bukin_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bukin_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 100 * (a->x[1] - 0.01 * pow(a->x[0], 2) + 1) + 0.01 * pow(a->x[0] + 10, 2);

    return sum;
}

/* It computes the 4th Bukin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-10, 0)
Domain: -15 <= x_0 <= -5 and -3 <= x_1 <= 3 */
double Bukin_Forth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bukin_Forth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bukin_Forth. It must be equal to two.\n");
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
double Bukin_Sixth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Bukin_Sixth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Bukin_Sixth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 100 * sqrt(fabs(a->x[1] - 0.01 * pow(a->x[0], 2))) + 0.01 * fabs(a->x[0] + 10);

    return sum;
}

/* It computes the Three-Hump Camel function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -5 <= x_i <= 5 */
double Three_HumpCamel(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Three_HumpCamel.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Three_HumpCamel. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 2 * pow(a->x[0], 2) - 1.05 * pow(a->x[0], 4) + pow(a->x[0], 6) / 6 + a->x[0] * a->x[1] + pow(a->x[1], 2);

    return sum;
}

/* It computes the Six-Hump Camel function
Parameters:
a: agent
---
Minimum at f(x*) = -1.0316 at x* = (-0.0898, 0.7126) or (0.0898, -0.7126)
Domain: -5 <= x_i <= 5 */
double Six_HumpCamel(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Six_HumpCamel.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Six_HumpCamel. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (4 - 2.1 * pow(a->x[0], 2) + pow(a->x[0], 4) / 3) * pow(a->x[0], 2) + a->x[0] * a->x[1] + (4 * pow(a->x[1], 2) - 4) * pow(a->x[1], 2);

    return sum;
}

/* It computes the Chen's Bird function
Parameters:
a: agent
---
Minimum at f(x*) = -2000 at x* = (-7/18, -13/18)
Domain: -500 <= x_i <= 500 */
double Chen_Bird(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Chen_Bird.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Chen_Bird. It must be equal to two.\n");
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
double Chen_V(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Chen_V.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Chen_V. It must be equal to two.\n");
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
double Chichinadze(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Chichinadze.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Chichinadze. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) - 12 * a->x[0] + 11 + 10 * cos(M_PI * a->x[0] / 2) + 8 * sin(5 * M_PI * a->x[0] / 2) - pow(1 / 5, 0.5) * exp(-0.5 * pow(a->x[1] - 0.5, 2));

    return sum;
}

/* It computes the Chung Reynolds' function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Chung_Reynolds(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Chung_Reynolds.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Chung_Reynolds. It must be equal or greater than one.\n");
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
double Colville(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Colville.\n");
        return DBL_MAX;
    }

    if (a->n != 4)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Colville. It must be equal to four.\n");
        return DBL_MAX;
    }

    sum = 100 * pow(a->x[0] - pow(a->x[1], 2), 2) + pow(1 - a->x[0], 2) + 90 * pow(a->x[3] - pow(a->x[2], 2), 2) + pow(1 - a->x[2], 2) + 10.1 * (pow(a->x[1] - 1, 2) + pow(a->x[3] - 1, 2)) + 19.8 * (a->x[1] - 1) * (a->x[3] - 1);

    return sum;
}

/* It computes the Cosine's Mixture function
Parameters:
a: agent
---
Minimum at f(x*) = 0.2 at x* = (0, 0) or f(x*) = 0.4 at x* = (0, 0, 0, 0)
Domain: -1 <= x_i <= 1 */
double Cosine(Agent *a, va_list arg)
{
    int i;
    double sum = 0, partial_sum = 0, partial_sum2 = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Cosine.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Cosine. It must be greater than 1.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++) {
        partial_sum += cos(5 * M_PI * a->x[i]);
        partial_sum2 += pow(a->x[i], 2);
    }

    sum = -0.1 * partial_sum - partial_sum2;

    return sum;
}

/* It computes the Cross-in-Tray function
Parameters:
a: agent
---
Minimum at f(x*) = -2.06261 at x* = (1.3494, -1.3494), (1.3494, 1.3494), (-1.3494, 1.3494) or (-1.3494, -1.3494)
Domain: -10 <= x_i < 10 */
double Cross_Tray(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Cross_Tray.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Cross_Tray. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -0.0001 * pow((fabs(sin(a->x[0]) * sin(a->x[1]) * exp(fabs(100 - (sqrt(pow(a->x[0], 2) + pow(a->x[1], 2)) / M_PI)))) + 1), 0.1);

    return sum;
}

/* It computes the Csendes' function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -1 <= x_i <= 1 */
double Csendes(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Csendes.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Csendes. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 6) * (2 + sin(1 / a->x[i]));

    return sum;
}

/* It computes the Cube's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-1, 1)
Domain: -10 <= x_i <= 10 */
double Cube(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Cube.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Cube. It must be equal to two.\n");
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
double Damavandi(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Damavandi.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Damavandi. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (1 - pow(fabs((sin(M_PI * (a->x[0] - 2)) * sin(M_PI * (a->x[1] - 2))) / (pow(M_PI, 2) * (a->x[0] - 2) * (a->x[1] - 2))), 5)) * (2 + pow(a->x[0] - 7, 2) + 2 * pow(a->x[1] - 7, 2));

    return sum;
}

/* It computes the Deckkers-Aarts' function
Parameters:
a: agent
---
Minimum at f(x*) = -24777 at x* = (0, 15) or (0, -15)
Domain: -20 <= x_i <= 20 */
double Deckkers_Aarts(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Deckkers_Aarts.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Deckkers_Aarts. It must be equal to two.\n");
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
double Dixon_Price(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Dixon_Price.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Dixon_Price. It must be greater than one.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0] - 1, 2);

    for (i = 1; i < a->n; i++)
        sum += (i + 1) * pow((2 * pow(a->x[i], 2) - a->x[i - 1]), 2);

    return sum;
}

/* It computes the Easom's function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* = (PI, PI)
Domain: -100 <= x_i <= 100 */
double Easom(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Easom.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Easom. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -cos(a->x[0]) * cos(a->x[1]) * exp(-pow(a->x[0] - M_PI, 2) - pow(a->x[1] - M_PI, 2));

    return sum;
}

/* It computes the El-Attar-Vidyasagar-Dutta's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.470427 at x* = (2.842503, 1.920175)
Domain: -500 <= x_i <= 500 */
double ElAttar_VidyasagarDutta(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @ElAttar_VidyasagarDutta.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @ElAttar_VidyasagarDutta. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(pow(a->x[0], 2) + a->x[1] - 10, 2) + pow(a->x[0] + pow(a->x[1], 2) - 7, 2) + pow(pow(a->x[0], 2) + pow(a->x[1], 3) - 1, 2);

    return sum;
}

/* It computes the Egg Crate function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -5 <= x_i <= 5 */
double Eggcrate(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Eggcrate.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Eggcrate. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) + pow(a->x[1], 2) + 25 * (pow(sin(a->x[0]), 2) + pow(sin(a->x[1]), 2));

    return sum;
}

/* It computes the Egg Holder function
Parameters:
a: agent
---
Minimum at f(x*) = 959.64 at x* = (512, 404.2319)
Domain: -512 <= x_i <= 512 */
double Eggholder(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Eggholder.\n");
        return DBL_MAX;
    }

    if (a->n < 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Eggholder. It must be equal or greater than two.\n");
        return DBL_MAX;
    }

    for (i = 0; i < (a->n) - 1; i++)
        sum += -(a->x[i + 1] + 47) * sin(sqrt(fabs(a->x[i + 1] + a->x[i] / 2 + 47))) - a->x[i] * sin(sqrt(fabs(a->x[i] - (a->x[i + 1] + 47))));

    return sum;
}

/* It computes the Exponential function
Parameters:
a: agent
---
Minimum at f(x*) = 1 at x* = (0, va_list arg, 0)
Domain: -1 <= x_i <= 1 */
double Exponential(Agent *a, va_list arg)
{
    int i;
    double partial_sum = 0, sum;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Exponential.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Exponential. It must be equal or greater than one.\n");
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
Minimum at f(x*) = 0 at x* = (0, 10)
Domain: 0 <= x_i <= 20 */
double EXP_2(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @EXP_2.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @EXP_2. It must be equal to two.\n");
        return DBL_MAX;
    }

    for (i = 0; i < 10; i++)
        sum += pow(exp(-i * a->x[0] / 10) - 5 * exp(-i * a->x[1] / 10) - exp(-i / 10) + 5 * exp(-i), 2);

    return sum;
}

/* It computes the Freudenstein's Roth function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (5, 4)
Domain: -10 <= x_i <= 10 */
double Freudenstein_Roth(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Freudenstein_Roth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Freudenstein_Roth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0] - 13 + ((5 - a->x[1]) * a->x[1] - 2) * a->x[1], 2) + pow(a->x[0] - 29 + ((a->x[1] + 1) * a->x[1] - 14) * a->x[1], 2);

    return sum;
}

/* It computes the Giunta's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.060447 at x* = (0.45834282, 0.45834282)
Domain: -1 <= x_i <= 1 */
double Giunta(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Giunta.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Giunta. It must be equal to two.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += sin(16 / 15 * a->x[i] - 1) + pow(sin(16 / 15 * a->x[i] - 1), 2) + (1 / 50) * sin(4 * (16 / 15 * a->x[i] - 1));

    sum = 0.6 + sum;

    return sum;
}

/* It computes the Goldstein-Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 3 at x* = (0, -1)
Domain: -2 <= x_i <= 2 */
double Goldstein_Price(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Goldstein_Price.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Goldstein_Price. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (1 + pow(a->x[0] + a->x[1] + 1, 2) * (19 - 14 * a->x[0] + 3 * pow(a->x[1], 2) - 14 * a->x[1] + 6 * a->x[0] * a->x[1] + 3 * pow(a->x[1], 2))) * (30 + pow(2 * a->x[0] - 3 * a->x[1], 2) * (18 - 32 * a->x[0] + 12 * pow(a->x[0], 2) + 48 * a->x[1] - 36 * a->x[0] * a->x[1] + 27 * pow(a->x[1], 2)));

    return sum;
}

/* It computes the Griewank's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Griewank(Agent *a, va_list arg)
{
    int i;
    double partial_sum = 1, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Griewank.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Griewank. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        partial_sum *= cos(a->x[i] / sqrt(i + 1)) + 1;
        sum += pow(a->x[i], 2) / 4000;
    }

    sum = sum - partial_sum;

    return sum;
}

/* It computes the Gulf's Research problem
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (50, 25, 1.5)
Domain: 0.1 <= x_0 <= 100, 0 <= x_1 <= 25.6 and 0 <= x_2 <= 5 */
double Gulf_Research(Agent *a, va_list arg)
{
    int i;
    double sum = 0, u;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Gulf_Research.\n");
        return DBL_MAX;
    }

    if (a->n != 3)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Gulf_Research. It must be equal to three.\n");
        return DBL_MAX;
    }

    for (i = 1; i < 100; i++)
    {
        u = 25 + pow((-50 * log(0.01 * i)), 1 / 1.5);
        sum += pow(exp(-pow(u - a->x[1], a->x[2]) / a->x[0]) - 0.01 * i, 2);
    }

    return sum;
}

/* It computes the Helical Valley function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 0, 0)
Domain: -10 <= x_i <= 10 */
double Helical_Valley(Agent *a, va_list arg)
{
    double sum = 0, theta;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Helical_Valley.\n");
        return DBL_MAX;
    }

    if (a->n != 3)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Helical_Valley. It must be equal to three.\n");
        return DBL_MAX;
    }

    if (a->x[0] >= 0)
        theta = (1 / 2 * M_PI) * pow(tan(a->x[0] / a->x[1]), -1);
    else
        theta = (1 / 2 * M_PI) * pow(tan(a->x[0] / a->x[1] + 0.5), -1);

    sum = 100 * (pow(a->x[1] - 10 * theta, 2) + sqrt(pow(a->x[0], 2) + pow(a->x[1], 2)) - 1) + pow(a->x[2], 2);

    return sum;
}

/* It computes the Himmelblau's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (3, 2)
Domain: -5 <= x_i <= 5 */
double Himmelblau(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Himmelblau.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Himmelblau. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(pow(a->x[0], 2) + a->x[1] - 11, 2) + pow(a->x[0] + pow(a->x[1], 2) - 7, 2);

    return sum;
}

/* It computes the Hosaki's function
Parameters:
a: agent
---
Minimum at f(x*) = -2.3458 at x* = (4, 2)
Domain: 0 <= x_1 <= 5 and 0 <= x_2 <= 6 */
double Hosaki(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Hosaki.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Hosaki. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (1 - 8 * a->x[0] + 7 * pow(a->x[0], 2) - (7 / 3 * pow(a->x[0], 3)) + (1 / 4 * pow(a->x[0], 4))) * pow(a->x[1], 2) * exp(-a->x[1]);

    return sum;
}

/* It computes the Jennrick-Sampson's function
Parameters:
a: agent
---
Minimum at f(x*) = 124.3612 at x* = (0.257825, 0.257825)
Domain: -1 <= x_i <= 1 */
double Jennrick_Sampson(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Jennrick_Sampson.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Jennrick_Sampson. It must be equal to two.\n");
        return DBL_MAX;
    }

    for (i = 1; i <= 10; i++)
        sum += pow(2 + 2 * i - (exp(i * a->x[0]) + exp(i * a->x[1])), 2);

    return sum;
}

/* It computes the Keane's function
Parameters:
a: agent
---
Minimum at f(x*) = -0.673668 at x* = (0, 1.39325) or (1.39325, 0)
Domain: 0 <= x_i <= 10 */
double Keane(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Keane.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Keane. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (pow(sin(a->x[0] - a->x[1]), 2) * pow(sin(a->x[0] + a->x[1]), 2)) / sqrt(pow(a->x[0], 2) + pow(a->x[1], 2));

    return sum;
}

/* It computes the Leon's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 1)
Domain: -1.2 <= x_i <= 1.2 */
double Leon(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Leon.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Leon. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 100 * pow(a->x[1] - pow(a->x[0], 2), 2) + pow(1 - a->x[0], 2);

    return sum;
}

/* It computes the Levy's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, va_list arg,  1)
Domain: -10 <= x_i <= 10 */
double Levy(Agent *a, va_list arg)
{
    int i;
    double partial_sum = 0, sum = 0;
    double w, w_1, w_d;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Levy.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Levy. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    w_1 = 1 + ((a->x[0] - 1) / 4);
    w_d = 1 + ((a->x[a->n - 1] - 1) / 4);

    for (i = 0; i < (a->n - 1); i++)
    {
        w = 1 + ((a->x[i] - 1) / 4);
        partial_sum += pow(w - 1, 2) * (1 + 10 * pow(sin(M_PI * w + 1), 2)) + pow(w_d - 1, 2) * (1 + pow(sin(2 * M_PI * w_d), 2));
    }

    sum = pow(sin(M_PI * w_1), 2) + partial_sum;

    return sum;
}

/* It computes the 13th Levy's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 1)
Domain: -10 <= x_i <= 10 */
double Levy_Thirteenth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Levy_Thirteenth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Levy_Thirteenth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(sin(3 * M_PI * a->x[0]), 2) + (pow(a->x[0] - 1, 2) * (1 + pow(sin(3 * M_PI * a->x[1]), 2))) + (pow(a->x[1] - 1, 2) * (1 + pow(sin(2 * M_PI * a->x[1]), 2)));

    return sum;
}

/* It computes the Matyas's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -10 <= x_i <= 10 */
double Matyas(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Matyas.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Matyas. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.26 * (pow(a->x[0], 2) + pow(a->x[1], 2)) - (0.48 * a->x[0] * a->x[1]);

    return sum;
}

/* It computes the McCormick's function
Parameters:
a: agent
---
Minimum at f(x*) = -1.9133 at x* = (-0.547, -1.547)
Domain: -1.5 <= x_0 <= 4 and -3 <= x_1 <= 3 */
double McCormick(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @McCormick.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @McCormick. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = sin(a->x[0] + a->x[1]) + pow(a->x[0] - a->x[1], 2) - (3 / 2) * a->x[0] + (5 / 2) * a->x[1] + 1;

    return sum;
}

/* It computes the Miele Cantrell's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 1, 1, 1)
Domain: -1 <= x_i <= 1 */
double Miele_Cantrell(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Miele_Cantrell.\n");
        return DBL_MAX;
    }

    if (a->n != 4)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Miele_Cantrell. It must be equal to four.\n");
        return DBL_MAX;
    }

    sum = pow(exp(-a->x[0]) - a->x[1], 4) + 100 * pow(a->x[1] - a->x[2], 6) + pow(tan(a->x[2] - a->x[3]), 4) + pow(a->x[0], 8);

    return sum;
}

/* It computes the Parsopoulos' function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (k*PI/2, lambda*PI) with k = +-1, +-3, va_list arg and lambda = 0, +-1, +-2, va_list arg
Domain: -5 <= x_i <= 5 */
double Parsopoulos(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Parsopoulos.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Parsopoulos. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = cos(pow(a->x[0], 2)) + sin(pow(a->x[1], 2));

    return sum;
}

/* It computes the Pen Holder function
Parameters:
a: agent
---
Minimum at f(x*) = -0.96354 at x* = (+-9.646168, +-9.646168)
Domain: -11 <= x_i <= 11 */
double Pen_Holder(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Pen_Holder.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Pen_Holder. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -exp(pow(fabs(cos(a->x[0]) * cos(a->x[1]) * exp(fabs(1 - pow(pow(a->x[0], 2) + pow(a->x[1], 2), 0.5) / M_PI))), -1));

    return sum;
}

/* It computes the Pathological function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Pathological(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Pathological.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Pathological. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < (a->n - 1); i++)
        sum += 0.5 + (pow(sin(sqrt(100 * pow(a->x[i], 2) + pow(a->x[i + 1], 2)) - 0.5), 2)) / (1 + 0.001 * pow(pow(a->x[i], 2) - 2 * a->x[i] * a->x[i + 1] + pow(a->x[i + 1], 2), 2));

    return sum;
}

/* It computes the Paviani's function
Parameters:
a: agent
---
Minimum at f(x*) = -45.778 at x* = (9.350266, va_list arg, 9.350266)
Domain: 2.0001 <= x_i <= 10 */
double Paviani(Agent *a, va_list arg)
{
    int i;
    double prod = 1, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Paviani.\n");
        return DBL_MAX;
    }

    if (a->n != 10)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Paviani. It must be equal to ten.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        prod *= a->x[i];
        sum += pow(log(a->x[i] - 2), 2) + pow(log(10 - a->x[i]), 2);
    }

    sum = sum - pow(prod, 0.2);

    return sum;
}

/* It computes the Periodic function
Parameters:
a: agent
---
Minimum at f(x*) = 0.9 at x* = (0, 0)
Domain: -10 <= x_i <= 10 */
double Periodic(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Periodic.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Periodic. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 1 + pow(sin(a->x[0]), 2) + pow(sin(a->x[1]), 2) - 0.1 * exp(-(pow(a->x[0], 2) + pow(a->x[1], 2)));

    return sum;
}

/* It computes the Powell's Sum function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -1 <= x_i <= 1 */
double Powell_Sum(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Powell_Sum.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Powell_Sum. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(fabs(a->x[i]), (i + 2));

    return sum;
}

/* It computes the 1st Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-5, -5), (-5, 5), (5, -5) or (5, 5)
Domain: -500 <= x_i <= 500 */
double Price_First(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Price_First.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Price_First. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(fabs(a->x[0]) - 5, 2) + pow(fabs(a->x[1]) - 5, 2);

    return sum;
}

/* It computes the 2nd Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.9 at x* = (0, 0)
Domain: -10 <= x_i <= 10 */
double Price_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Price_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Price_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 1 + pow(sin(a->x[0]), 2) + pow(sin(a->x[1]), 2) - 0.1 * exp(-pow(a->x[0], 2) - pow(a->x[1], 2));

    return sum;
}

/* It computes the 3rd Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-5, -5), (-5, 5), (5, -5) or (5, 5)
Domain: -500 <= x_i <= 500 */
double Price_Third(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Price_Third.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Price_Third. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 100 * pow(a->x[1] - pow(a->x[0], 2), 2) + 6 * pow(6.4 * pow(a->x[1] - 0.5, 2) - a->x[0] - 0.6, 2);

    return sum;
}

/* It computes the 4th Price's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0), (2, 4) or (1.464, -2.506)
Domain: -500 <= x_i <= 500 */
double Price_Forth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Price_Forth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Price_Forth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(2 * pow(a->x[0], 3) * a->x[1] - pow(a->x[1], 3), 2) + pow(6 * a->x[0] - pow(a->x[1], 2) + a->x[1], 2);

    return sum;
}

/* It computes the Qing's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (+-sqrt(i), va_list arg, +-sqrt(i))
Domain: -500 <= x_i <= 500 */
double Qing(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Qing.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Qing. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(pow(a->x[i], 2) - (i + 1), 2);

    return sum;
}

/* It computes the Quadratic function
Parameters:
a: agent
---
Minimum at f(x*) = -3873.7243 at x* = (0.19388, 0.48513)
Domain: -10 <= x_i <= 10 */
double Quadratic(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Quadratic.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Quadratic. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -3803.84 - 138.08 * a->x[0] - 232.92 * a->x[1] + 128.08 * pow(a->x[0], 2) + 203.64 * pow(a->x[1], 2) + 182.25 * a->x[0] * a->x[1];

    return sum;
}

/* It computes the Quartic function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -1.28 <= x_i <= 1.28 */
double Quartic(Agent *a, va_list arg)
{
    int i;
    double sum = 0, u;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Quartic.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Quartic. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += (i + 1) * pow(a->x[i], 4);

    do
    {
        u = GenerateUniformRandomNumber(0, 1);
    } while (u == 1);

    sum += u;

    return sum;
}

/* It computes the Quintic function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (-1 or 2, va_list arg, -1 or 2)
Domain: -10 <= x_i <= 10 */
double Quintic(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Quintic.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Quintic. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += fabs(pow(a->x[i], 5) - 3 * pow(a->x[i], 4) + 4 * pow(a->x[i], 3) + 2 * pow(a->x[i], 2) - 10 * a->x[i] - 4);

    return sum;
}

/* It computes the Rastrigin's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -5.12 <= x_i <= 5.12 */
double Rastrigin(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Rastrigin.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Rastrigin. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    sum = 10 * a->n;

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 2) - 10 * cos(2 * M_PI * a->x[i]);

    return sum;
}

/* It computes the Rosenbrock's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, va_list arg, 1)
Domain: -30 <= x_i <= 30 */
double Rosenbrock(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Rosenbrock.\n");
        return DBL_MAX;
    }

    if (a->n < 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Rosenbrock. It must be greater than two.\n");
        return DBL_MAX;
    }

    for (i = 0; i < (a->n - 1); i++)
        sum += 100 * (pow(a->x[i + 1] - pow(a->x[i], 2), 2)) + pow(a->x[i] - 1, 2);

    return sum;
}

/* It computes the Rotated Ellipsoid 1 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -500 <= x_i <= 500 */
double Rotated_Ellipsoid_1(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Rotated_Ellipsoid_1.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Rotated_Ellipsoid_1. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 7 * pow(a->x[0], 2) - 6 * sqrt(3) * a->x[0] * a->x[1] + 13 * pow(a->x[1], 2);

    return sum;
}

/* It computes the Rotated Ellipsoid 2 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -500 <= x_i <= 500 */
double Rotated_Ellipsoid_2(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Rotated_Ellipsoid_2.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Rotated_Ellipsoid_2. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) - a->x[0] * a->x[1] + pow(a->x[1], 2);

    return sum;
}

/* It computes the Rump's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -500 <= x_i <= 500 */
double Rump(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Rump.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Rump. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = (333.75 - pow(a->x[0], 2)) * pow(a->x[1], 6) + pow(a->x[0], 2) * (11 * pow(a->x[0], 2) * pow(a->x[1], 2) - 121 * pow(a->x[1], 4) - 2) + 5.5 * pow(a->x[1], 8) + (a->x[0]) / (2 * a->x[1]);

    return sum;
}

/* It computes the Salomon's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Salomon(Agent *a, va_list arg)
{
    int i;
    double partial_sum = 0, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Salomon.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Salomon. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        partial_sum += pow(a->x[i], 2);

    sum = 1 - cos(2 * M_PI * sqrt(partial_sum)) + 0.1 * sqrt(partial_sum);

    return sum;
}

/* It computes the 1st Schaffer's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Schaffer_First(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schaffer_First.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schaffer_First. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.5 + (pow(sin(pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2)), 2) - 0.5) / (1 + 0.001 * pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2));

    return sum;
}

/* It computes the 2nd Schaffer's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0)
Domain: -100 <= x_i <= 100 */
double Schaffer_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schaffer_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schaffer_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.5 + (pow(sin(pow(pow(a->x[0], 2) - pow(a->x[1], 2), 2)), 2) - 0.5) / (1 + 0.001 * pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2));

    return sum;
}

/* It computes the 3rd Schaffer's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.001230 at x* = (0, +-1.253002) or (+-1.253002, 0)
Domain: -100 <= x_i <= 100 */
double Schaffer_Third(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schaffer_Third.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schaffer_Third. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.5 + (pow(sin(cos(fabs(pow(a->x[0], 2) - pow(a->x[1], 2)))), 2) - 0.5) / (1 + 0.001 * pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2));

    return sum;
}

/* It computes the 4th Schaffer's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.292438 at x* = (0, +-1.253028) or (+-1.253028, 0)
Domain: -100 <= x_i <= 100 */
double Schaffer_Forth(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schaffer_Forth.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schaffer_Forth. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.5 + (pow(cos(sin(pow(a->x[0], 2) - pow(a->x[1], 2))), 2) - 0.5) / (1 + 0.001 * pow(pow(a->x[0], 2) + pow(a->x[1], 2), 2));

    return sum;
}

/* It computes the Schmidt Vetters' function
Parameters:
a: agent
---
Minimum at f(x*) = 3 at x* = (0.78547, 0.78547, 0.78547)
Domain: 0 <= x_i <= 10 */
double Schmidt_Vetters(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schmidt_Vetters.\n");
        return DBL_MAX;
    }

    if (a->n != 3)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schmidt_Vetters. It must be equal to three.\n");
        return DBL_MAX;
    }

    sum = 1 / (1 + pow(a->x[0] - a->x[1], 2)) + sin((M_PI * a->x[1] + a->x[2]) / 2) + exp(pow((a->x[0] + a->x[1]) / a->x[1] - 2, 2));

    return sum;
}

/* It computes the Schumer Steiglitz's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Schumer_Steiglitz(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schumer_Steiglitz.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schumer_Steiglitz. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 4);

    return sum;
}

/* It computes the Schewefel's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -100 <= x_i <= 100 */
double Schewefel(Agent *a, va_list arg)
{
    int i;
    double alpha, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Schewefel.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Schewefel. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 2);

    alpha = sqrt(M_PI);

    sum = pow(sum, alpha);

    return sum;
}

/* It computes the Sphere's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: 0 <= x_i <= 10 */
double Sphere(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Sphere.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Sphere. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 2);

    return sum;
}

/* It computes the Streched V Sine Wave function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -10 <= x_i <= 10 */
double Streched_V_SineWave(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Streched_V_SineWave.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Streched_V_SineWave. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < (a->n - 1); i++)
        sum += pow(pow(a->x[i + 1], 2) + pow(a->x[i], 2), 0.25) * (pow(sin(50 * pow(pow(a->x[i + 1], 2) + pow(a->x[i], 2), 0.1)), 2) + 0.1);

    return sum;
}

/* It computes the Sum of Different Powers function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain:  -1 <= x_i <= 1 */
double Sum_DifferentPowers(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Sum_DifferentPowers.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Sum_DifferentPowers. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(fabs(a->x[i]), (i + 2));

    return sum;
}

/* It computes the Sum Squares function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain:  -10 <= x_i <= 10 */
double Sum_Squares(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Sum_Squares.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Sum_Squares. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += (i + 1) * pow(a->x[i], 2);

    return sum;
}

/* It computes the Styblinski's-Tang function
Parameters:
a: agent
---
Minimum at f(x*) = -78.332 at x* = (-2.903534, va_list arg, -2.903534)
Domain:  -5 <= x_i <= 5 */
double Styblinski_Tang(Agent *a, va_list arg)
{
    int i;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Styblinski_Tang.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Styblinski_Tang. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += pow(a->x[i], 4) - 16 * pow(a->x[i], 2) + 5 * a->x[i];

    sum *= 0.5;

    return sum;
}

/* It computes the 1st Holder's Table function
Parameters:
a: agent
---
Minimum at f(x*) = -26.920336 at x* = (+-9.646168, +-9.646168)
Domain:  -10 <= x_i <= 10 */
double Holder_Table_First(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Holder_Table_First.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Holder_Table_First. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -fabs(cos(a->x[0]) * cos(a->x[1]) * exp(fabs(1 - pow(a->x[0] + a->x[1], 0.5 / M_PI))));

    return sum;
}

/* It computes the 2nd Holder's Table function
Parameters:
a: agent
---
Minimum at f(x*) = -19.20850 at x* = (+-8.055023472141116, +-9.664590028909654)
Domain:  -10 <= x_i <= 10 */
double Holder_Table_Second(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Holder_Table_Second.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Holder_Table_Second. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -fabs(sin(a->x[0]) * cos(a->x[1]) * exp(fabs(1 - pow(a->x[0] + a->x[1], 0.5 / M_PI))));

    return sum;
}

/* It computes the Carrom's Table function
Parameters:
a: agent
---
Minimum at f(x*) = -24.1568155 at x* = (+-9.646157266348881, +-9.646134286497169)
Domain:  -10 <= x_i <= 10 */
double Carrom_Table(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Carrom_Table.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Carrom_Table. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -(1 / 30) * exp(2 * fabs(1 - (sqrt(pow(a->x[0], 2) + pow(a->x[1], 2)) / M_PI)) * pow(cos(a->x[0]), 2) * pow(cos(a->x[1]), 2));

    return sum;
}

/* It computes the Testtube's Holder function
Parameters:
a: agent
---
Minimum at f(x*) = -10.872300 at x* = (+-PI/2, 0)
Domain:  -10 <= x_i <= 10 */
double Testtube_Holder(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Testtube_Holder.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Testtube_Holder. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = -4 * (sin(a->x[0]) * cos(a->x[1]) * exp(fabs(cos(pow(a->x[0], 2) + pow(a->x[1], 2)) / 200)));

    return sum;
}

/* It computes the Trecanni's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0) or (-2, 0)
Domain:  -5 <= x_i <= 5 */
double Trecanni(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Trecanni.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Trecanni. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 4) - 4 * pow(a->x[0], 3) + 4 * a->x[0] + pow(a->x[1], 2);

    return sum;
}

/* It computes the Trefethen's function
Parameters:
a: agent
---
Minimum at f(x*) = -3.30686865 at x* = (-0.024403, 0.210612)
Domain:  -10 <= x_i <= 10 */
double Trefethen(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Trefethen.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Trefethen. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = exp(sin(50 * a->x[0])) + sin(60 * exp(a->x[1])) + sin(70 * sin(a->x[0])) + sin(sin(80 * a->x[1])) - sin(10 * (a->x[0] + a->x[1])) + ((1 / 4) * (pow(a->x[0], 2) + pow(a->x[1], 2)));

    return sum;
}

/* It computes the Trigonometric 1 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain:  0 <= x_i <= PI */
double Trigonometric_1(Agent *a, va_list arg)
{
    int i, j;
    double partial_sum = 0, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Trigonometric_1.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Trigonometric_1. It must be greater than one\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        for (j = 0; j < a->n; j++)
            partial_sum += cos(a->x[j]);
    sum += pow(a->n - partial_sum + (i + 1) * (1 - cos(a->x[i]) - sin(a->x[i])), 2);

    return sum;
}

/* It computes the Trigonometric 2 function
Parameters:
a: agent
---
Minimum at f(x*) = 1 at x* = (0.9, va_list arg, 0.9)
Domain:  -500 <= x_i <= 500 */
double Trigonometric_2(Agent *a, va_list arg)
{
    int i;
    double partial_sum = 0, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Trigonometric_2.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Trigonometric_2. It must be greater than one\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        partial_sum += 8 * pow(sin(7 * pow(a->x[i] - 0.9, 2)), 2) + 6 * pow(sin((14 * pow(a->x[0] - 0.9, 2))), 2) + pow(a->x[i] - 0.9, 2);

    sum = 1 + partial_sum;

    return sum;
}

/* It computes the Venter's Sobiezcczanski-Sobieski function
Parameters:
a: agent
---
Minimum at f(x*) = -400 at x* = (0, 0)
Domain: -50 <= x_i <= 50 */
double Venter_Sobiezcczanski(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Venter_Sobiezcczanski.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Venter_Sobiezcczanski. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow(a->x[0], 2) - 100 * cos(pow(a->x[0], 2)) - 100 * cos(pow(a->x[0], 2) / 30) + pow(a->x[1], 2) - 100 * cos(pow(a->x[1], 2)) - 100 * cos(pow(a->x[1], 2) / 30);

    return sum;
}

/* It computes the Watson's function
Parameters:
a: agent
---
Minimum at f(x*) = 0.002288 at x* = (-0.0158, 1.012, -0.2329, 1.260, -1.513, 0.9928)
Domain: |x_i| <= 10 with a_i = i/29 */
double Watson(Agent *a, va_list arg)
{
    int i, j;
    double partial_sum_1 = 0, partial_sum_2 = 0, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Watson.\n");
        return DBL_MAX;
    }

    if (a->n != 6)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Watson. It must be equal to six.\n");
        return DBL_MAX;
    }

    for (i = 0; i < 30; i++)
    {
        for (j = 0; j < 6; j++)
        {
            if (j < 5)
                partial_sum_1 += ((j - 1) * pow((i / 29), j) * a->x[j + 1]);
            partial_sum_2 += pow((i / 29), j) * a->x[j + 1];
        }
        sum += pow(partial_sum_1 - pow(partial_sum_2, 2) - 1, 2) + pow(a->x[0], 2);
    }

    return sum;
}

/* It computes the Wayburn Seader 1 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (1, 2) or (1.597, 0.806)
Domain: -500 <= x_i <= 500 */
double Wayburn_Seader_1(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Wayburn_Seader_1.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Wayburn_Seader_1. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow((pow(a->x[0], 6) + pow(a->x[1], 4) - 17), 2) + pow(((2 * a->x[0]) + a->x[1] - 4), 4);

    return sum;
}

/* It computes the Wayburn Seader 2 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0.2, 1) or (0.425, 1)
Domain: -500 <= x_i <= 500 */
double Wayburn_Seader_2(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Wayburn_Seader_2.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Wayburn_Seader_2. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = pow((1.613 + (4 * pow((a->x[0] - 0.3125), 2)) - (4 * pow((a->x[1] - 1.625), 2))), 2) + pow((a->x[1] - 1), 2);

    return sum;
}

/* It computes the Wayburn Seader 3 function
Parameters:
a: agent
---
Minimum at f(x*) = 21.35 at x* = (5.611, 6.187)
Domain: -500 <= x_i <= 500 */
double Wayburn_Seader_3(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Wayburn_Seader_3.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Wayburn_Seader_3. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 2 * (pow(a->x[0], 3) / 3) - 8 * pow(a->x[0], 2) + 31 * a->x[0] - (a->x[0] * a->x[1]) + 5 + pow(pow((a->x[0] - 4), 2) + (pow((a->x[1] - 5), 2) - 4), 2);

    return sum;
}

/* It computes the Wavy's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, 0) with k = 10
Domain: -PI <= x_i <= PI */
double Wavy(Agent *a, va_list arg)
{
    int i, k = 10;
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Wavy.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Wavy. It must be equal or greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
        sum += cos(k * a->x[i]) * exp(-pow(a->x[i], 2) / 2);

    sum = 1 - (1 / a->n) * sum;

    return sum;
}

/* It computes the Xin-She Yang's 1 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -5 <= x_i <= 5 */
double XinShe_Yang_1(Agent *a, va_list arg)
{
    int i;
    double e, sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @XinShe_Yang_1.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @XinShe_Yang_1. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        e = GenerateUniformRandomNumber(0, 1);
        sum += e * pow(fabs(a->x[i]), (i + 1));
    }

    return sum;
}

/* It computes the Xin-She Yang's 2 function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -2PI <= x_i <= 2PI */
double XinShe_Yang_2(Agent *a, va_list arg)
{
    double sum = 0, sum1 = 0, sum2 = 0;
    int i;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @XinShe_Yang_2.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @XinShe_Yang_2. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        sum1 += fabs(a->x[i]);
        sum2 += sin(pow(a->x[i], 2));
    }

    sum += (sum1)*exp(-sum2);

    return sum;
}

/* It computes the Xin-She Yang's 3 function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* = (0, va_list arg, 0) with m = 5 and beta = 15
Domain: -20 <= x_i <= 20 */
double XinShe_Yang_3(Agent *a, va_list arg)
{
    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 1;
    int i, m = 5, beta = 15;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @XinShe_Yang_3.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @XinShe_Yang_3. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        sum1 += pow((a->x[i] / beta), 2 * m);
        sum2 += pow(a->x[i], 2);
        sum3 *= pow(cos(a->x[i]), 2);
    }

    sum = exp(-sum1) - (2 * exp(-sum2)) * sum3;

    return sum;
}

/* It computes the Xin-She Yang's 4 function
Parameters:
a: agent
---
Minimum at f(x*) = -1 at x* = (0, va_list arg, 0)
Domain: -10 <= x_i <= 10 */
double XinShe_Yang_4(Agent *a, va_list arg)
{
    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    int i;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @XinShe_Yang_4.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @XinShe_Yang_4. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        sum1 += pow(sin(a->x[i]), 2);
        sum2 += pow(a->x[i], 2);
        sum3 += pow(sin(sqrt(fabs(a->x[i]))), 2);
    }

    sum = (sum1 - exp(-sum2)) * exp(-sum3);

    return sum;
}

/* It computes the Zakharov's function
Parameters:
a: agent
---
Minimum at f(x*) = 0 at x* = (0, va_list arg, 0)
Domain: -5 <= x_i <= 10 */
double Zakharov(Agent *a, va_list arg)
{
    double sum = 0, sum1 = 0, sum2 = 0;
    int i;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Zakharov.\n");
        return DBL_MAX;
    }

    if (a->n < 1)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Zakharov. It must be greater than one.\n");
        return DBL_MAX;
    }

    for (i = 0; i < a->n; i++)
    {
        sum1 += pow(a->x[i], 2);
        sum2 += (i + 1) * a->x[i];
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
double Zettl(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Zettl.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Zettl. It must be equal to two.\n");
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
double Zirilli(Agent *a, va_list arg)
{
    double sum = 0;

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @Zirilli.\n");
        return DBL_MAX;
    }

    if (a->n != 2)
    {
        fprintf(stderr, "\nInvalid number of decision variables @Zirilli. It must be equal to two.\n");
        return DBL_MAX;
    }

    sum = 0.25 * pow(a->x[0], 4) - 0.5 * pow(a->x[0], 2) + 0.1 * a->x[0] + 0.5 * pow(a->x[1], 2);

    return sum;
}
/***********************/

/* Genetic Programming general-purpose functions */
/* It computes the pointwise sum of two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_SUM_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parametsrs @f_SUM_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = x[i] + y[i];

    return out;
}

/* It computes the pointwise subtraction of two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_SUB_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_SUB_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = x[i] - y[i];

    return out;
}

/* It computes the pointwise multiplication of two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_MUL_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_MUL_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = x[i] * y[i];

    return out;
}

/* It computes the pointwise vision of two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_DIV_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_DIV_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = x[i] / (y[i] + 0.00001); /* It avoids division by 0 */

    return out;
}

/* It computes the absolute value of each element from an n-dimensional array
Parameters:
x: array
n: dimension */
double *f_ABS_(double *x, int n)
{
    if (!x)
    {
        fprintf(stderr, "\nInvalid input parameters @f_ABS_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = fabs(x[i]);

    return out;
}

/* It computes the squared root of each element from a two n-dimensional array
Parameters:
x: array
n: dimension */
double *f_SQRT_(double *x, int n)
{
    if (!x)
    {
        fprintf(stderr, "\nInvalid input parameters @f_ABS_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = sqrt(fabs(x[i]));

    return out;
}

/* It computes the exponential (e) of each element from an n-dimensional array
Parameters:
x: array
n: dimension */
double *f_EXP_(double *x, int n)
{
    if (!x)
    {
        fprintf(stderr, "\nInvalid input parameters @f_EXP_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = exp(x[i]);

    return out;
}

/* It computes the natural logarithm (base-e logarithm) of each element from an n-dimensional array
Parameters:
x: array
n: dimension */
double *f_LOG_(double *x, int n)
{
    if (!x)
    {
        fprintf(stderr, "\nInvalid input parameters @f_LOG_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = log(x[i] + 0.00001);

    return out;
}

/* It computes the logical function AND among two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_AND_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_AND_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = (double)((int)x[i] & (int)y[i]);

    return out;
}

/* It computes the logical function OR among two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_OR_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_OR_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = (double)((int)x[i] | (int)y[i]);

    return out;
}

/* It computes the logical function XOR among two n-dimensional arrays
Parameters:
x, y: arrays
n: dimension */
double *f_XOR_(double *x, double *y, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_XOR_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = (double)((int)x[i] ^ (int)y[i]);

    return out;
}

/* It computes the logical function NOT of an n-dimensional array
Parameters:
x: array
n: dimension */
double *f_NOT_(double *x, int n)
{
    if (!x)
    {
        fprintf(stderr, "\nInvalid input parameters @f_NOT_.\n");
        exit(-1);
    }

    int i;
    double *out = NULL;

    out = (double *)malloc(n * sizeof(double));
    for (i = 0; i < n; i++)
        out[i] = (double)~(int)x[i];

    return out;
}
/*****************************/

/* Tensor-based Genetic Programming general-purpose functions */
/* It computes the tensor sum of two mxn-dimensional tensors
Parameters:
x, y:tensors
m,n n: dimensions */
double **f_TSUM_(double **x, double **y, int m, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_TSUM_.\n");
        exit(-1);
    }

    int i, j;
    double **out = NULL;

    out = (double **)malloc(m * sizeof(double));
    for (i = 0; i < m; i++){
	out[i] = (double *)malloc(n * sizeof(double));
	
	for(j = 0; j < n; j++)
	    out[i][j] = x[i][j] + y[i][j];
    }

    return out;
}

/* It computes the tensor subtraction of two mxn-dimensional tensors
Parameters:
x, y:tensors
m,n n: dimensions */
double **f_TSUB_(double **x, double **y, int m, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_TSUB_.\n");
        exit(-1);
    }

    int i, j;
    double **out = NULL;

    out = (double **)malloc(m * sizeof(double));
    for (i = 0; i < m; i++){
	out[i] = (double *)malloc(n * sizeof(double));
	
	for(j = 0; j < n; j++)
	    out[i][j] = x[i][j] - y[i][j];
    }

    return out;
}

/* It computes the tensor multiplication of two mxn-dimensional tensors
Parameters:
x, y:tensors
m,n n: dimensions */
double **f_TMUL_(double **x, double **y, int m, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_TMUL_.\n");
        exit(-1);
    }

    int i, j;
    double **out = NULL;

    out = (double **)malloc(m * sizeof(double));
    for (i = 0; i < m; i++){
	out[i] = (double *)malloc(n * sizeof(double));
	
	for(j = 0; j < n; j++)
	    out[i][j] = x[i][j] * y[i][j];
    }

    return out;
}

/* It computes the tensor division (protected) of two mxn-dimensional tensors
Parameters:
x, y:tensors
m,n n: dimensions */
double **f_TDIV_(double **x, double **y, int m, int n)
{
    if (!x || !y)
    {
        fprintf(stderr, "\nInvalid input parameters @f_TMUL_.\n");
        exit(-1);
    }

    int i, j;
    double **out = NULL;

    out = (double **)malloc(m * sizeof(double));
    for (i = 0; i < m; i++){
	out[i] = (double *)malloc(n * sizeof(double));
	
	for(j = 0; j < n; j++){
            if(!y[i][j]) out[i][j] = 0.0;
            else out[i][j] = x[i][j]/y[i][j];
	}
    }

    return out;
}
/*****************************/

/* Math functions */
/* It computes the logist sigmoid function
Parameters:
x: input */
double Logistic_Sigmoid(double x)
{
    double y;

    y = 1.0 / (1 + exp(-x));

    return y;
}
/*****************************/