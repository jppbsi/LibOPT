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

#include "ba.h"

/* It updates the velocity of an agent (bat)
Parameters:
S: search space
i: particle's index */
void UpdateBatVelocity(SearchSpace *s, int i)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateBatVelocity.\n");
        exit(-1);
    }

    int j;

    for (j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->a[i]->v[j] + (s->a[i]->x[j] - s->g[j]) * s->a[i]->f;
}

/* It sets the frequency of an agent (bat)
Parameters:
S: search space
i: particle's index */
void SetBatFrequency(SearchSpace *s, int i)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @SetBatFrequency.\n");
        exit(-1);
    }

    double beta = GenerateUniformRandomNumber(0, 1);
    s->a[i]->f = s->f_min + (s->f_min - s->f_max) * beta;
}

/* It executes the Bat Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runBA(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j;
    double alpha = 0.9, beta, prob, fitValue;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runBA.\n");
        exit(-1);
    }

    for (i = 0; i < s->m; i++)
    {
        s->a[i]->f = GenerateUniformRandomNumber(s->f_min, s->f_max);
        s->a[i]->r = GenerateUniformRandomNumber(0, s->r);
        s->a[i]->A = GenerateUniformRandomNumber(0, s->A);
    }

    EvaluateSearchSpace(s, _BA_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        /* for each bat */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);

            SetBatFrequency(s, i);   /* Equation 1 */
            UpdateBatVelocity(s, i); /* Equation 2 */

            /* Equation 3
            Here, we generate a temporary agent (bat) */
            tmp = CopyAgent(s->a[i], _BA_, _NOTENSOR_);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = tmp->x[j] + tmp->v[j];
            /**************/

            prob = GenerateUniformRandomNumber(0, 1);
            if (prob > s->a[i]->r)
            {
                DestroyAgent(&tmp, _BA_);
                tmp = GenerateNewAgent(s, _BA_);
            }
            CheckAgentLimits(s, tmp);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            prob = GenerateUniformRandomNumber(0, 1);
            if ((fitValue < s->a[i]->fit) && (prob < s->a[i]->A))
            { /* We accept the new solution */
                DestroyAgent(&(s->a[i]), _BA_);
                s->a[i] = CopyAgent(tmp, _BA_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
                s->a[i]->r = s->r * (1 - exp(-alpha * t));
                s->a[i]->A = s->A * alpha;
            }

            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }

            DestroyAgent(&tmp, _BA_);
        }

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/

/* It updates the velocity of an tensor (bat)
Parameters:
S: search space
i: particle's index
tensor_id: identifier of tensor's dimension */
void UpdateTensorBatVelocity(SearchSpace *s, int i, int tensor_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateTensorBatVelocity.\n");
        exit(-1);
    }

    int j, k;

    for (j = 0; j < s->n; j++)
        for (k = 0; k < tensor_id; k++)
            s->a[i]->t_v[j][k] = s->a[i]->t_v[j][k] + (s->a[i]->t[j][k] - s->t_g[j][k]) * s->a[i]->f;
}

/* It sets the frequency of an tensor (bat)
Parameters:
S: search space
i: particle's index */
void SetTensorBatFrequency(SearchSpace *s, int i)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @SetTensorBatFrequency.\n");
        exit(-1);
    }

    double beta = GenerateUniformRandomNumber(0, 1);
    s->a[i]->f = s->f_min + (s->f_max - s->f_min) * beta;
}

/* It generates a new tensor for BA algorithm
Parameters:
s: search space
tensor_id: identifier of tensor's dimension */
double **GenerateNewBatTensor(SearchSpace *s, int tensor_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @GenerateNewBatTensor.\n");
        exit(-1);
    }

    double **t = NULL;
    int j, k;

    t = CreateTensor(s->n, tensor_id);
    for (j = 0; j < s->n; j++)
        for (k = 0; k < tensor_id; k++)
            t[j][k] = s->t_g[j][k] + 0.001 * GenerateUniformRandomNumber(-1, 1);

    return t;
}

/* It executes the Tensor-based Bat Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorBA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j, k;
    double alpha = 0.9, beta, prob, fitValue;
    double **tmp_t = NULL, **tmp_t_v = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorBA.\n");
        exit(-1);
    }

    for (i = 0; i < s->m; i++)
    {
        s->a[i]->f = GenerateUniformRandomNumber(s->f_min, s->f_max);
        s->a[i]->r = GenerateUniformRandomNumber(0, s->r);
        s->a[i]->A = GenerateUniformRandomNumber(0, s->A);
    }

    EvaluateTensorSearchSpace(s, _BA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        /* for each bat */
        for (i = 0; i < s->m; i++)
        {
            va_copy(arg, argtmp);

            SetTensorBatFrequency(s, i);              /* Equation 1 */
            UpdateTensorBatVelocity(s, i, tensor_id); /* Equation 2 */

            /* Equation 3
            Here, we generate a temporary agent (bat) */
            tmp = CopyAgent(s->a[i], _BA_, _NOTENSOR_);
            tmp_t = CopyTensor(s->a[i]->t, s->n, tensor_id);
            tmp_t_v = CopyTensor(s->a[i]->t_v, s->n, tensor_id);
            for (j = 0; j < s->n; j++)
                for (k = 0; k < tensor_id; k++)
                    tmp_t[j][k] = tmp_t[j][k] + tmp_t_v[j][k];
            /**************/

            prob = GenerateUniformRandomNumber(0, 1);
            if (prob > s->a[i]->r)
            {
                DestroyTensor(&tmp_t, s->n);
                DestroyAgent(&tmp, _BA_);
                tmp = GenerateNewAgent(s, _BA_);
                tmp_t = GenerateNewBatTensor(s, tensor_id);
            }
            CheckTensorLimits(s, tmp_t, tensor_id);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent i */
            prob = GenerateUniformRandomNumber(0, 1);
            if ((fitValue < s->a[i]->fit) && (prob < s->a[i]->A))
            { /* We accept the new solution */
                DestroyTensor(&s->a[i]->t, s->n);
                DestroyTensor(&s->a[i]->t_v, s->n);
                DestroyAgent(&(s->a[i]), _BA_);
                s->a[i] = CopyAgent(tmp, _BA_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
                s->a[i]->t = CopyTensor(tmp_t, s->n, tensor_id);
                s->a[i]->t_v = CopyTensor(tmp_t_v, s->n, tensor_id);
                s->a[i]->r = s->r * (1 - exp(-alpha * t));
                s->a[i]->A = s->A * alpha;
            }

            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                DestroyTensor(&s->t_g, s->n);
                s->t_g = CopyTensor(tmp_t, s->n, tensor_id);
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }

            DestroyAgent(&tmp, _BA_);
            DestroyTensor(&tmp_t, s->n);
            DestroyTensor(&tmp_t_v, s->n);
        }

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/