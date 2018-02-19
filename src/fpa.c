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


#include "fpa.h"

/* It executes the Flower Pollination Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runFPA(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, flower_j, flower_k;
    double prob, epsilon, *L = NULL, fitValue;
    Agent *tmp = NULL, **tmp_flowers = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runFPA.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _FPA_, Evaluate, arg); /* Initial evaluation of the search space */

    tmp_flowers = (Agent **)calloc(s->m, sizeof(Agent));

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        for (i = 0; i < s->m; i++)
            tmp_flowers[i] = CopyAgent(s->a[i], _FPA_, _NOTENSOR_);

        /* for each flower */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);
            tmp = CopyAgent(s->a[i], _FPA_, _NOTENSOR_);

            prob = GenerateUniformRandomNumber(0, 1);
            if (prob > s->p)
            { /* large-scale pollination */
                L = GenerateLevyDistribution(s->n, s->beta);

                /* Equation 1 */
                for (j = 0; j < s->n; j++)
                    tmp->x[j] = tmp->x[j] + L[j] * (s->g[j] - tmp->x[j]);
                /**************/

                free(L);
            }
            else
            { /* local pollination */
                epsilon = GenerateUniformRandomNumber(0, 1);
                flower_j = GenerateUniformRandomNumber(0, s->m - 1);
                flower_k = GenerateUniformRandomNumber(0, s->m - 1);

                /* Equation 3 */
                for (j = 0; j < s->n; j++)
                    tmp->x[j] = tmp->x[j] + epsilon * (tmp_flowers[flower_j]->x[j] - tmp_flowers[flower_k]->x[j]);
            }
            CheckAgentLimits(s, tmp);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _FPA_);
                s->a[i] = CopyAgent(tmp, _FPA_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
            }

            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }
            DestroyAgent(&tmp, _FPA_);
        }

        for (i = 0; i < s->m; i++)
            DestroyAgent(&tmp_flowers[i], _FPA_);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(tmp_flowers);

    va_end(arg);
}
/****************************/

/* It executes the Tensor-based Flower Pollination Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorFPA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k, flower_j, flower_k;
    double prob, epsilon, **L = NULL, fitValue;
    double **tmp_t = NULL, ***tmp_tensors = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorFPA.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _FPA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    tmp_tensors = (double ***)calloc(s->m, sizeof(double **));

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        for (i = 0; i < s->m; i++)
            tmp_tensors[i] = CopyTensor(s->a[i]->t, s->n, tensor_id);

        /* for each flower */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);
            tmp = CopyAgent(s->a[i], _FPA_, _NOTENSOR_);
            tmp_t = CopyTensor(s->a[i]->t, s->n, tensor_id);

            prob = GenerateUniformRandomNumber(0, 1);
            if (prob > s->p)
            { /* large-scale pollination */
                L = (double **)calloc(s->n, sizeof(double *));
                for (j = 0; j < s->n; j++)
                    L[j] = GenerateLevyDistribution(tensor_id, s->beta);

                /* Equation 1 */
                for (j = 0; j < s->n; j++)
                    for (k = 0; k < tensor_id; k++)
                        tmp_t[j][k] = tmp_t[j][k] + L[j][k] * (s->t_g[j][k] - tmp_t[j][k]);
                /**************/
                for (j = 0; j < s->n; j++)
                    free(L[j]);
                free(L);
            }
            else
            { /* local pollination */
                epsilon = GenerateUniformRandomNumber(0, 1);
                flower_j = GenerateUniformRandomNumber(0, s->m - 1);
                flower_k = GenerateUniformRandomNumber(0, s->m - 1);

                /* Equation 3 */
                for (j = 0; j < s->n; j++)
                    for (k = 0; k < tensor_id; k++)
                        tmp_t[j][k] = tmp_t[j][k] + epsilon * (tmp_tensors[flower_j][j][k] - tmp_tensors[flower_k][j][k]);
            }
            CheckTensorLimits(s, tmp_t, tensor_id);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                DestroyTensor(&s->a[i]->t, s->n);
                DestroyAgent(&(s->a[i]), _FPA_);
                s->a[i] = CopyAgent(tmp, _FPA_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
                s->a[i]->t = CopyTensor(tmp_t, s->n, tensor_id);
            }

            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                DestroyTensor(&s->t_g, s->n);
                s->t_g = CopyTensor(tmp_t, s->n, tensor_id);
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }

            DestroyAgent(&tmp, _FPA_);
            DestroyTensor(&tmp_t, s->n);
        }

        for (i = 0; i < s->m; i++)
            DestroyTensor(&tmp_tensors[i], s->n);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(tmp_tensors);

    va_end(arg);
}
/****************************/