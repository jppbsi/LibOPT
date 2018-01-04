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


#include "pso.h"

/* PSO-related functions */
/* It updates the velocity of an agent (particle)
Parameters:
s: search space
i: particle's index */
void UpdateParticleVelocity(SearchSpace *s, int i)
{
    double r1, r2;
    int j;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateParticleVelocity.\n");
        exit(-1);
    }

    r1 = GenerateUniformRandomNumber(0, 1);
    r2 = GenerateUniformRandomNumber(0, 1);

    for (j = 0; j < s->n; j++)
        s->a[i]->v[j] = s->w * s->a[i]->v[j] + s->c1 * r1 * (s->a[i]->xl[j] - s->a[i]->x[j]) + s->c2 * r2 * (s->g[j] - s->a[i]->x[j]);
}

/* It updates the position of an agent (particle)
Parameters:
s: search space
i: particle's index */
void UpdateParticlePosition(SearchSpace *s, int i)
{
    int j;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateParticlePosition.\n");
        exit(-1);
    }

    for (j = 0; j < s->n; j++)
        s->a[i]->x[j] = s->a[i]->x[j] + s->a[i]->v[j];
}

/* It executes the Particle Swarm Optimization for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runPSO(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i;
    double beta, prob;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runPSO.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _PSO_, Evaluate, arg); /* Initial evaluation */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each particle */
        for (i = 0; i < s->m; i++)
        {
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }

        EvaluateSearchSpace(s, _PSO_, Evaluate, arg);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/*************************/

/* AIWPSO-related functions */
/* It executes the Particle Swarm Optimization with Adaptive Inertia Weight for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runAIWPSO(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i;
    double beta, prob;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runAIWPSO.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _PSO_, Evaluate, arg); /* Initial evaluation */

    for (i = 0; i < s->m; i++)
        s->a[i]->pfit = s->a[i]->fit;

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each particle */
        for (i = 0; i < s->m; i++)
        {
            UpdateParticleVelocity(s, i);
            UpdateParticlePosition(s, i);
            CheckAgentLimits(s, s->a[i]);
        }

        EvaluateSearchSpace(s, _PSO_, Evaluate, arg);
        prob = ComputeSuccess(s);                       /* Equations 17 and 18 */
        s->w = (s->w_max - s->w_min) * prob + s->w_min; /* Equation 20 */

        va_copy(arg, argtmp);

        for (i = 0; i < s->m; i++)
            s->a[i]->pfit = s->a[i]->fit;

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}

/* It computes the percentage of success concerning the whole search space
Parameters:
s: search space */
double ComputeSuccess(SearchSpace *s)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @ComputeSuccess.\n");
        exit(-1);
    }

    int i;
    double p = 0;

    for (i = 0; i < s->m; i++)
    {
        if (s->a[i]->fit < s->a[i]->pfit)
            p++;
    }

    return p / s->m;
}
/****************************/

/* TensorPSO-related functions */
/* It updates the velocity of an tensor (particle)
Parameters:
s: search space
i: particle's index
tensor_id: identifier of tensor's dimension */
void UpdateTensorParticleVelocity(SearchSpace *s, int i, int tensor_id)
{
    double r1, r2;
    int j, k;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateTensorParticleVelocity.\n");
        exit(-1);
    }

    r1 = GenerateUniformRandomNumber(0, 1);
    r2 = GenerateUniformRandomNumber(0, 1);

    for (j = 0; j < s->n; j++)
    {
        for (k = 0; k < tensor_id; k++)
        {
            s->a[i]->t_v[j][k] = s->w * s->a[i]->t_v[j][k] + s->c1 * r1 * (s->a[i]->t_xl[j][k] - s->a[i]->t[j][k]) + s->c2 * r2 * (s->t_g[j][k] - s->a[i]->t[j][k]);
        }
    }
}

/* It updates the position of an tensor (particle)
Parameters:
s: search space
i: particle's index
tensor_id: identifier of tensor's dimension */
void UpdateTensorParticlePosition(SearchSpace *s, int i, int tensor_id)
{
    int j, k;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @UpdateTensorParticlePosition.\n");
        exit(-1);
    }

    for (j = 0; j < s->n; j++)
        for (k = 0; k < tensor_id; k++)
            s->a[i]->t[j][k] = s->a[i]->t[j][k] + s->a[i]->t_v[j][k];
}

/* It executes the Tensor-based Particle Swarm Optimization for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorPSO(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j;
    double beta, prob;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorPSO.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _PSO_, tensor_id, Evaluate, arg); /* Initial evaluation */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each particle */
        for (i = 0; i < s->m; i++)
        {
            UpdateTensorParticleVelocity(s, i, tensor_id);
            UpdateTensorParticlePosition(s, i, tensor_id);
            CheckTensorLimits(s, s->a[i]->t, tensor_id);
            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
        }

        EvaluateTensorSearchSpace(s, _PSO_, tensor_id, Evaluate, arg);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}

/* It executes the Tensor-based Particle Swarm Optimization with Adaptive Inertia Weight for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorAIWPSO(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j;
    double beta, prob;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorAIWPSO.\n");
        exit(-1);
    }

    EvaluateTensorSearchSpace(s, _PSO_, tensor_id, Evaluate, arg); /* Initial evaluation */

    for (i = 0; i < s->m; i++)
        s->a[i]->pfit = s->a[i]->fit;

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);

        /* for each particle */
        for (i = 0; i < s->m; i++)
        {
            UpdateTensorParticleVelocity(s, i, tensor_id);
            UpdateTensorParticlePosition(s, i, tensor_id);
            CheckTensorLimits(s, s->a[i]->t, tensor_id);
            for (j = 0; j < s->n; j++)
                s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
        }

        EvaluateTensorSearchSpace(s, _PSO_, tensor_id, Evaluate, arg);
        prob = ComputeSuccess(s);                       /* Equations 17 and 18 */
        s->w = (s->w_max - s->w_min) * prob + s->w_min; /* Equation 20 */

        va_copy(arg, argtmp);

        for (i = 0; i < s->m; i++)
            s->a[i]->pfit = s->a[i]->fit;

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    va_end(arg);
}
/****************************/
