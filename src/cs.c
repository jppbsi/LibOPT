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

#include "cs.h"

/* It computes the number of nests that will be replaced, taking into account a probability [0,1] */
int NestLossParameter(int size, float probability)
{
    int loss;

    loss = round(size * (1 - probability));

    return loss;
}

/* It executes the Cuckoo Search for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runCS(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k, nest_i, nest_j, loss;
    double rand, *L = NULL, fitValue;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runCS.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _CS_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        va_copy(arg, argtmp);

        nest_i = round(GenerateUniformRandomNumber(0, s->m - 1));
        tmp = CopyAgent(s->a[nest_i], _CS_, _NOTENSOR_);

        /* Equation 1 */
        L = GenerateLevyDistribution(s->n, s->beta);
        for (k = 0; k < s->n; k++)
            tmp->x[k] += s->alpha * L[k];
        free(L);
        /**************/

        CheckAgentLimits(s, tmp);

        nest_j = round(GenerateUniformRandomNumber(0, s->m - 1));

        fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
        if (fitValue < s->a[nest_j]->fit)
        { /* We accept the new solution */
            DestroyAgent(&(s->a[nest_j]), _CS_);
            s->a[nest_j] = CopyAgent(tmp, _CS_, _NOTENSOR_);
            s->a[nest_j]->fit = fitValue;
        }

        DestroyAgent(&tmp, _CS_);

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */

        loss = NestLossParameter(s->m, s->p);

        for (i = s->m - 1; i >= loss; i--)
        {
            va_copy(arg, argtmp);

            tmp = GenerateNewAgent(s, _CS_);
            /* Random walk */
            rand = GenerateUniformRandomNumber(0, 1);
            nest_i = round(GenerateUniformRandomNumber(0, s->m - 1));
            nest_j = round(GenerateUniformRandomNumber(0, s->m - 1));
            for (k = 0; k < s->n; k++)
                tmp->x[k] += rand * (s->a[nest_i]->x[k] - s->a[nest_j]->x[k]);
            /**************/

            CheckAgentLimits(s, tmp);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _CS_);
                s->a[i] = CopyAgent(tmp, _CS_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
            }
            DestroyAgent(&tmp, _CS_);
        }

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */

        fprintf(stderr, "OK (minimum fitness value %lf)", s->a[0]->fit);
    }

    va_end(arg);
}

/* It executes the Tensor-based Cuckoo Search for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runTensorCS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k, nest_i, nest_j, loss;
    double rand, **L = NULL, fitValue;
    double **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorCS.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _CS_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        va_copy(arg, argtmp);

        nest_i = round(GenerateUniformRandomNumber(0, s->m - 1));
        tmp = CopyAgent(s->a[nest_i], _CS_, _NOTENSOR_);
        tmp_t = CopyTensor(s->a[nest_i]->t, s->n, tensor_id);

        /* Equation 1 */
        L = (double **)calloc(s->n, sizeof(double *));
        for (j = 0; j < s->n; j++)
            L[j] = GenerateLevyDistribution(tensor_id, s->beta);
        for (j = 0; j < s->n; j++)
            for (k = 0; k < tensor_id; k++)
                tmp_t[j][k] += s->alpha * L[j][k];
        for (j = 0; j < s->n; j++)
            free(L[j]);
        free(L);
        /**************/

        CheckTensorLimits(s, tmp_t, tensor_id);
        for (j = 0; j < s->n; j++)
            tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

        nest_j = round(GenerateUniformRandomNumber(0, s->m - 1));

        fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
        if (fitValue < s->a[nest_j]->fit)
        { /* We accept the new solution */
            DestroyTensor(&s->a[nest_j]->t, s->n);
            DestroyAgent(&(s->a[nest_j]), _CS_);
            s->a[nest_j] = CopyAgent(tmp, _CS_, _NOTENSOR_);
            s->a[nest_j]->fit = fitValue;
            s->a[nest_j]->t = CopyTensor(tmp_t, s->n, tensor_id);
        }

        DestroyAgent(&tmp, _CS_);
        DestroyTensor(&tmp_t, s->n);

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */

        loss = NestLossParameter(s->m, s->p);

        for (i = s->m - 1; i >= loss; i--)
        {
            va_copy(arg, argtmp);

            tmp = GenerateNewAgent(s, _CS_);
            tmp_t = GenerateNewTensor(s, tensor_id);

            /* Random walk */
            rand = GenerateUniformRandomNumber(0, 1);
            nest_i = round(GenerateUniformRandomNumber(0, s->m - 1));
            nest_j = round(GenerateUniformRandomNumber(0, s->m - 1));
            for (j = 0; j < s->n; j++)
                for (k = 0; k < tensor_id; k++)
                    tmp_t[j][k] += rand * (s->a[nest_i]->t[j][k] - s->a[nest_j]->t[j][k]);
            /**************/
            CheckTensorLimits(s, tmp_t, tensor_id);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                DestroyTensor(&s->a[i]->t, s->n);
                DestroyAgent(&(s->a[i]), _CS_);
                s->a[i] = CopyAgent(tmp, _CS_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
                s->a[i]->t = CopyTensor(tmp_t, s->n, tensor_id);
            }
            DestroyAgent(&tmp, _CS_);
            DestroyTensor(&tmp_t, s->n);
        }

        qsort(s->a, s->m, sizeof(Agent **), SortAgent); /* Sorts all nests according to their fitness. First position gets the best nest. */

        fprintf(stderr, "OK (minimum fitness value %lf)", s->a[0]->fit);
    }

    va_end(arg);
}
