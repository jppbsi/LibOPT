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


#include "wca.h"

int *FlowIntensity(SearchSpace *s)
{
    int *flow = NULL, i;
    double tmp = 0, sum_fitness;

    flow = (int *)calloc(s->nsr + 1, sizeof(int));

    sum_fitness = 0;

    for (i = 0; i < s->nsr + 1; i++)
    {
        sum_fitness += s->a[i]->fit;
    }

    for (i = 0; i < s->nsr + 1; i++)
    {
        tmp = round(fabs(s->a[i]->fit / sum_fitness) * (s->m - (s->nsr + 1)));
        flow[i] = tmp;
    }

    return flow;
}

void UpdateStreamPosition(SearchSpace *s, int *flow, double c)
{
    int k, i, j, flow_count = 0;
    double tmp, rand;

    /* Streams flow to rivers */
    for (k = 1; k < s->nsr + 1; k++)
    {
        flow_count = flow_count + flow[k];
        for (i = (flow_count - flow[k]); i <= flow_count; i++)
        {
            rand = GenerateUniformRandomNumber(0, 1);
            for (j = 0; j < s->n; j++)
            {
                tmp = s->a[i]->x[j] + rand * c * (s->a[k]->x[j] - s->a[i]->x[j]);
                s->a[i]->x[j] = tmp;
            }
        }
    }

    /* Streams flow to the sea */
    for (i = s->nsr + 1; i <= flow[0]; i++)
    {
        rand = GenerateUniformRandomNumber(0, 1);
        for (j = 0; j < s->n; j++)
        {
            tmp = s->a[i]->x[j] + rand * c * (s->a[s->best]->x[j] - s->a[i]->x[j]);
            s->a[i]->x[j] = tmp;
        }
    }
}

void UpdateRiverPosition(SearchSpace *s, double c)
{
    int i, j;
    double tmp = 0, rand;

    /* Rivers flow to the sea */
    for (i = 1; i < s->nsr + 1; i++)
    {
        rand = GenerateUniformRandomNumber(0, 1);
        for (j = 0; j < s->n; j++)
        {
            tmp = s->a[i]->x[j] + rand * c * (s->a[s->best]->x[j] - s->a[i]->x[j]);
            s->a[i]->x[j] = tmp;
        }
    }
}

void RainingProcess(SearchSpace *s, int *flow)
{
    int i, j;
    double tmp, rand, dist;

    for (i = 1; i < s->nsr + 1; i++)
    {
        rand = GenerateUniformRandomNumber(0, 1);
        dist = EuclideanDistance(s->a[0]->x, s->a[i]->x, s->n); /* It obtains the euclidean distance for further use */
        if ((dist < s->dmax) || (rand < 0.1))
        {
            DestroyAgent(&(s->a[i]), _WCA_);
            s->a[i] = GenerateNewAgent(s, _WCA_);
        }
    }

    for (i = s->nsr + 1; i < flow[0]; i++)
    {
        rand = GenerateUniformRandomNumber(0, 1);
        dist = EuclideanDistance(s->a[0]->x, s->a[i]->x, s->n); /* It obtains the euclidean distance for further use */
        if ((dist < s->dmax) || (rand < 0.1))
        {
            DestroyAgent(&(s->a[i]), _WCA_);
            s->a[i] = GenerateNewAgent(s, _WCA_);
        }
    }
}

/* It executes the Water Cycle Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runWCA(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, *flow = NULL;
    double c = 2; /* c = [1,2]. The author recommends 2 as the best value */
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runWCA.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _WCA_, Evaluate, arg); /* Initial evaluation of the search space */

    qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all raindrops according to their fitness. First position gets the sea. */

    flow = FlowIntensity(s);

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        UpdateStreamPosition(s, flow, c);
        UpdateRiverPosition(s, c);
        for (i = 0; i < s->m; i++)
        {
            CheckAgentLimits(s, s->a[i]);
        }
        EvaluateSearchSpace(s, _WCA_, Evaluate, arg);   /* Initial evaluation of the search space */
        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all raindrops according to their fitness. First position gets the sea. */
        RainingProcess(s, flow);
        s->dmax = s->dmax - (s->dmax / s->iterations);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    free(flow);
    va_end(arg);
}
