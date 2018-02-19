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

#include "bha.h"

/* It executes the Black Hole Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate agents
arg: list of additional arguments */
void runBHA(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j;
    double fitValue, sum, rand, dist, radius;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runBHA.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _BHA_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        sum = 0;

        /* Changing the position of each star according to Equation 3 */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);

            rand = GenerateUniformRandomNumber(0, 1);

            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] += rand * (s->g[j] - s->a[i]->x[j]);

            CheckAgentLimits(s, s->a[i]);
            s->a[i]->fit = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            tmp = CopyAgent(s->a[i], _BHA_, _NOTENSOR_);
            if (s->a[i]->fit < s->gfit)
            {
                fitValue = s->gfit;
                s->gfit = s->a[i]->fit;
                s->a[i]->fit = fitValue;
                for (j = 0; j < s->n; j++)
                {
                    tmp->x[j] = s->g[j];
                    s->g[j] = s->a[i]->x[j];
                    s->a[i]->x[j] = tmp->x[j];
                }
            }
            DestroyAgent(&tmp, _BHA_);
            sum = sum + s->a[i]->fit;
        }

        va_copy(arg, argtmp);

        /* Event Horizon and evaluating the solutions */
        radius = s->gfit / sum;
        for (i = 0; i < s->m; i++)
        {
            dist = EuclideanDistance(s->g, s->a[i]->x, s->n); /* It obtains the euclidean distance */
            if (dist < radius)
            {
                DestroyAgent(&(s->a[i]), _BHA_);
                s->a[i] = GenerateNewAgent(s, _BHA_);
            }
        }

        EvaluateSearchSpace(s, _BHA_, Evaluate, arg);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    va_end(arg);
}

/* It executes the Tensor-based Black Hole Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate agents
arg: list of additional arguments */
void runTensorBHA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k;
    double fitValue, sum, rand, dist, radius;
    double **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorBHA.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _BHA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        sum = 0;

        /* Changing the position of each star according to Equation 3 */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);

            rand = GenerateUniformRandomNumber(0, 1);

            for (j = 0; j < s->n; j++)
                for (k = 0; k < tensor_id; k++)
                    s->a[i]->t[j][k] += rand * (s->t_g[j][k] - s->a[i]->t[j][k]);

            CheckTensorLimits(s, s->a[i]->t, tensor_id);
            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
            s->a[i]->fit = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            tmp = CopyAgent(s->a[i], _BHA_, _NOTENSOR_);
            tmp_t = CopyTensor(s->a[i]->t, s->n, tensor_id);
            if (s->a[i]->fit < s->gfit)
            {
                fitValue = s->gfit;
                s->gfit = s->a[i]->fit;
                s->a[i]->fit = fitValue;
                for (j = 0; j < s->n; j++)
                {
                    s->g[j] = s->a[i]->x[j];
                    for (k = 0; k < tensor_id; k++)
                    {
                        tmp_t[j][k] = s->t_g[j][k];
                        s->t_g[j][k] = s->a[i]->t[j][k];
                        s->a[i]->t[j][k] = tmp_t[j][k];
                    }
                }
            }
            DestroyAgent(&tmp, _BHA_);
            DestroyTensor(&tmp_t, s->n);
            sum = sum + s->a[i]->fit;
        }

        va_copy(arg, argtmp);

        /* Event Horizon and evaluating the solutions */
        radius = s->gfit / sum;
        for (i = 0; i < s->m; i++)
        {
            dist = TensorEuclideanDistance(s->t_g, s->a[i]->t, s->n, tensor_id); /* It obtains the euclidean distance */
            if (dist < radius)
            {
                DestroyTensor(&s->a[i]->t, s->n);
                DestroyAgent(&(s->a[i]), _BHA_);
                s->a[i] = GenerateNewAgent(s, _BHA_);
                s->a[i]->t = GenerateNewTensor(s, tensor_id);
            }
        }

        EvaluateTensorSearchSpace(s, _BHA_, tensor_id, Evaluate, arg);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }
    va_end(arg);
}