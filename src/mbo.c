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


#include "mbo.h"

/* It updates the neighbours of a single bird
Parameters:
s: search space
b: current bird
k: number of neighbours updated
Evaluate: pointer to the function used to evaluate birds
arg: list of additional arguments */
void UpdateNeighbours(SearchSpace *s, int b, int k, prtFun Evaluate, va_list arg)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateNeighbours.\n");
        exit(-1);
    }
    int i, j;
    double f;
    va_list argtmp;

    va_copy(argtmp, arg);

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < s->n; j++)
            s->a[b]->nb[i]->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);

        f = Evaluate(s->a[b]->nb[i], arg); /* It executes the fitness function for neighbour i */
        s->a[b]->nb[i]->fit = f;           /* It updates the fitness value of actual neighbour i */

        va_copy(arg, argtmp);
    }
    qsort(s->a[b]->nb, s->k, sizeof(Agent **), SortAgent); /* It sorts the neighbours */
}

/* It shares the neighbours to the following bird
Parameters:
s: search space */
void ShareNeighbours(SearchSpace *s)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @ShareNeighbours.\n");
        exit(-1);
    }
    int i, j, k;

    for (i = 0; i < s->X; i++)
    { /* It distribuites the X best neighbours (except the first) to the following birds of leader (1st and 2nd) */
        for (j = 0; j < s->n; j++)
            s->a[1]->nb[(s->k) - (s->X) + i]->x[j] = s->a[2]->nb[(s->k) - (s->X) + i]->x[j] = s->a[0]->nb[i + 1]->x[j];
        s->a[1]->nb[(s->k) - (s->X) + i]->fit = s->a[2]->nb[(s->k) - (s->X) + i]->fit = s->a[0]->nb[i + 1]->fit;
    }
    qsort(s->a[1]->nb, s->k, sizeof(Agent **), SortAgent); /* It sorts the new neighbours */
    qsort(s->a[2]->nb, s->k, sizeof(Agent **), SortAgent);

    if (s->m > 3)
    {
        for (k = 1; k < s->m - 2; k++)
        { /* It distributes the X best neighbours (except the first) to the following birds */
            for (i = 0; i < s->X; i++)
            {
                for (j = 0; j < s->n; j++)
                    s->a[k + 2]->nb[(s->k) - (s->X) + i]->x[j] = s->a[k]->nb[i + 1]->x[j];
                s->a[k + 2]->nb[(s->k) - (s->X) + i]->fit = s->a[k]->nb[i + 1]->fit;
            }
            qsort(s->a[k + 2]->nb, s->k, sizeof(Agent **), SortAgent); /* It sorts the new neighbours */
        }
    }
}

/* It tries to replace each bird for its best neighbour
Parameters:
s: search space */
void ImproveBirds(SearchSpace *s)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @ImproveBirds.\n");
        exit(-1);
    }
    int i, j;

    for (i = 0; i < s->m; i++)
    { /* for each bird */
        if (s->a[i]->nb[0]->fit < s->a[i]->fit)
        { /* It compares the current bird with its best neighbour */
            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] = s->a[i]->nb[0]->x[j];
            s->a[i]->fit = s->a[i]->nb[0]->fit;
        }
    }
}

/* It executes the Migrating Birds Optimization for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate birds
arg: list of additional arguments */
void runMBO(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int i, j, t, k, tour;
    double beta, prob;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runMBO.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _MBO_, Evaluate, arg);   /* Initial evaluation */
    qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Initial bird sort */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each tour */
        for (tour = 0; tour < s->M; tour++)
        {
            UpdateNeighbours(s, 0, s->k, Evaluate, arg); /* It generates the k neighbours of leader */

            for (k = 1; k < s->m; k++)
            { /* It generates the k-X neighbours of each bird */
                UpdateNeighbours(s, k, s->k - s->X, Evaluate, arg);
                va_copy(arg, argtmp);
            }

            ShareNeighbours(s);
            ImproveBirds(s);
        }

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* It replaces the leader with the best bird and sorts the birds flock*/
        //ShowSearchSpace(s, _MBO_);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->a[0]->fit);
    }

    va_end(arg);
}