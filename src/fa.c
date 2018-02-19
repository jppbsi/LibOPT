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


#include "fa.h"

/* It executes the Firefly Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFA(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int i, j, k, t;
    double beta, delta = 0.97, distance;
    double r;
    Agent **tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runFA.\n");
        exit(-1);
    }

    tmp = (Agent **)malloc(s->m * sizeof(Agent *));

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        EvaluateSearchSpace(s, _FA_, Evaluate, arg); /* Initial evaluation of the search space */
        for (i = 0; i < s->m; i++)
            tmp[i] = CopyAgent(s->a[i], _FA_, _NOTENSOR_);
        qsort(tmp, s->m, sizeof(Agent **), SortAgent); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */

        for (i = 0; i < s->m; i++)
        {
            for (j = 0; j < s->m; j++)
            {
                distance = EuclideanDistance(s->a[i]->x, tmp[j]->x, s->n); /* It obtains the euclidean distance for further use */
                distance *= distance;
                if (s->a[i]->fit > tmp[j]->fit)
                {
                    beta = s->beta_0 * exp(-s->gamma * distance); /* It obtains attractiveness by Equation 1 */
                    for (k = 0; k < s->n; k++)
                    {
                        r = GenerateUniformRandomNumber(0, 1);
                        s->a[i]->x[k] = s->a[i]->x[k] + beta * (tmp[j]->x[k] - s->a[i]->x[k]) + s->alpha * (r - 0.5); /* It updates the firefly position by Equation 2 */
                    }
                }
            }
        }

        for (i = 0; i < s->m; i++)
        {
            CheckAgentLimits(s, s->a[i]);
            DestroyAgent(&tmp[i], _FA_);
        }

        va_copy(arg, argtmp);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(tmp);
    va_end(arg);
}

/* It executes the Tensor-based Firefly Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorFA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int i, j, k, l, t;
    double beta, delta = 0.97, distance;
    double r;
    double ***tmp_t = NULL;
    Agent **tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorFA.\n");
        exit(-1);
    }

    tmp = (Agent **)malloc(s->m * sizeof(Agent *));
    tmp_t = (double ***)malloc(s->m * sizeof(double **));

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        EvaluateTensorSearchSpace(s, _FA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */
        for (i = 0; i < s->m; i++)
        {
            tmp[i] = CopyAgent(s->a[i], _FA_, _NOTENSOR_);
            tmp_t[i] = CopyTensor(s->a[i]->t, s->n, tensor_id);
        }
        qsort(tmp, s->m, sizeof(Agent **), SortAgent); /* Sorts all fireflies according to their fitness. First position gets the best firefly. */

        for (i = 0; i < s->m; i++)
        {
            for (j = 0; j < s->m; j++)
            {
                distance = TensorEuclideanDistance(s->a[i]->t, tmp_t[j], s->n, tensor_id); /* It obtains the euclidean distance for further use */
                distance *= distance;
                if (s->a[i]->fit > tmp[j]->fit)
                {
                    beta = s->beta_0 * exp(-s->gamma * distance); /* It obtains attractiveness by Equation 1 */
                    for (k = 0; k < s->n; k++)
                    {
                        for (l = 0; l < tensor_id; l++)
                        {
                            r = GenerateUniformRandomNumber(0, 1);
                            s->a[i]->t[k][l] = s->a[i]->t[k][l] + beta * (tmp_t[j][k][l] - s->a[i]->t[k][l]) + s->alpha * (r - 0.5); /* It updates the firefly position by Equation 2 */
                        }
                    }
                }
            }
        }

        for (i = 0; i < s->m; i++)
        {
            CheckTensorLimits(s, s->a[i]->t, tensor_id);
            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
            DestroyAgent(&tmp[i], _FA_);
            DestroyTensor(&tmp_t[i], s->n);
        }

        va_copy(arg, argtmp);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(tmp);
    free(tmp_t);
    va_end(arg);
}
/*************************/