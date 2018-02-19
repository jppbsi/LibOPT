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

#include "abc.h"

/* It executes the Artificial Bee Colony for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runABC(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int i, j, k, t, chosen_param, neighbour, *trial, max_trial_index, limit;
    double max_fitness, r, fitValue, *prob;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runABC.\n");
        exit(-1);
    }

    limit = s->limit;
    trial = (int *)calloc(s->m, sizeof(int));
    prob = (double *)calloc(s->m, sizeof(double));

    EvaluateSearchSpace(s, _ABC_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        /* Employed Bee step */
        for (i = 0; i < s->m; i++)
        { /* For each food source */
            va_copy(arg, argtmp);

            chosen_param = GenerateUniformRandomNumber(0, s->n - 1); /* Randomly parameter to be used */
            do
            {
                neighbour = GenerateUniformRandomNumber(0, s->m - 1); /* Randomly neighbour to be used, which must be different from i */
            } while (neighbour == i);
            r = GenerateUniformRandomNumber(0, 1);

            tmp = CopyAgent(s->a[i], _ABC_, _NOTENSOR_);
            tmp->x[chosen_param] = s->a[i]->x[chosen_param] + (s->a[i]->x[chosen_param] - s->a[neighbour]->x[chosen_param]) * r; /* We now update our currently solution */
            CheckAgentLimits(s, tmp);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                trial[i] = 0;
                DestroyAgent(&(s->a[i]), _ABC_);
                s->a[i] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
            }
            else
            {
                trial[i]++; /* If the solution could not be improved, we increase the trial counter */
            }
            if (fitValue < s->gfit)
            { /* Update the global best */
                s->gfit = fitValue;
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }
            DestroyAgent(&tmp, _ABC_);
        }

        /* Calculation of new probabilities */
        max_fitness = s->a[0]->fit;
        for (i = 1; i < s->m; i++)
            if (s->a[i]->fit > max_fitness)
                max_fitness = s->a[i]->fit;
        for (i = 0; i < s->m; i++)
            prob[i] = (0.9 * (s->a[i]->fit / (max_fitness + 0.00000001))) + 0.1;

        /* Onlooker Bee step */
        i = 0;
        k = 0;
        while (k < s->m)
        {
            r = GenerateUniformRandomNumber(0, 1);
            if (r < prob[i])
            {
                va_copy(arg, argtmp);
                k++;
                chosen_param = GenerateUniformRandomNumber(0, s->n - 1); /* Randomly parameter to be used */
                do
                {
                    neighbour = GenerateUniformRandomNumber(0, s->m - 1); /* Randomly neighbour to be used, which must be different from i */
                } while (neighbour == i);

                tmp = CopyAgent(s->a[i], _ABC_, _NOTENSOR_);
                tmp->x[chosen_param] = s->a[i]->x[chosen_param] + (s->a[i]->x[chosen_param] - s->a[neighbour]->x[chosen_param]) * r; /* We now update our currently solution */
                CheckAgentLimits(s, tmp);
                fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
                if (fitValue < s->a[i]->fit)
                { /* We accept the new solution */
                    trial[i] = 0;
                    DestroyAgent(&(s->a[i]), _ABC_);
                    s->a[i] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                    s->a[i]->fit = fitValue;
                }
                else
                {
                    trial[i]++; /* If the solution could not be improved, we increase the trial counter */
                }
                if (fitValue < s->gfit)
                { /* Update the global best */
                    s->gfit = fitValue;
                    for (j = 0; j < s->n; j++)
                        s->g[j] = tmp->x[j];
                }
                DestroyAgent(&tmp, _ABC_);
            }
            i++;
            if (i == s->m)
                i = 0;
        }

        /* Scout Bee step */
        max_trial_index = 0;
        for (i = 0; i < s->m; i++)
            if (trial[i] > trial[max_trial_index])
                max_trial_index = i;
        if (trial[max_trial_index] >= limit)
        {
            va_copy(arg, argtmp);
            trial[max_trial_index] = 0;
            tmp = GenerateNewAgent(s, _ABC_);
            CheckAgentLimits(s, tmp);
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for new created agent */
            if (fitValue < s->a[max_trial_index]->fit)
            { /* We accept the new solution */
                DestroyAgent(&(s->a[max_trial_index]), _ABC_);
                s->a[max_trial_index] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                s->a[max_trial_index]->fit = fitValue;
            }
            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }
            DestroyAgent(&tmp, _ABC_);
        }

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(trial);
    free(prob);
    va_end(arg);
}

/* It executes the Tensor-based Artificial Bee Colony for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorABC(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int i, j, k, l, t, chosen_param, neighbour, *trial, max_trial_index, limit;
    double max_fitness, r, fitValue, *prob;
    double **tmp_t = NULL;
    Agent *tmp = NULL;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorABC.\n");
        exit(-1);
    }

    limit = s->limit;
    trial = (int *)calloc(s->m, sizeof(int));
    prob = (double *)calloc(s->m, sizeof(double));

    EvaluateTensorSearchSpace(s, _ABC_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

        /* Employed Bee step */
        for (i = 0; i < s->m; i++)
        { /* For each food source */
            va_copy(arg, argtmp);

            chosen_param = GenerateUniformRandomNumber(0, s->n - 1); /* Randomly parameter to be used */
            do
            {
                neighbour = GenerateUniformRandomNumber(0, s->m - 1); /* Randomly neighbour to be used, which must be different from i */
            } while (neighbour == i);
            r = GenerateUniformRandomNumber(0, 1);

            tmp = CopyAgent(s->a[i], _ABC_, _NOTENSOR_);
            tmp_t = CopyTensor(s->a[i]->t, s->n, tensor_id);
            for (k = 0; k < tensor_id; k++)
                tmp_t[chosen_param][k] = s->a[i]->t[chosen_param][k] + (s->a[i]->t[chosen_param][k] - s->a[neighbour]->t[chosen_param][k]) * r; /* We now update our currently solution */
            CheckTensorLimits(s, tmp_t, tensor_id);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
            if (fitValue < s->a[i]->fit)
            { /* We accept the new solution */
                trial[i] = 0;
                DestroyTensor(&s->a[i]->t, s->n);
                DestroyAgent(&(s->a[i]), _ABC_);
                s->a[i] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                s->a[i]->fit = fitValue;
                s->a[i]->t = CopyTensor(tmp_t, s->n, tensor_id);
            }
            else
            {
                trial[i]++; /* If the solution could not be improved, we increase the trial counter */
            }
            if (fitValue < s->gfit)
            { /* Update the global best */
                s->gfit = fitValue;
                DestroyTensor(&s->t_g, s->n);
                s->t_g = CopyTensor(tmp_t, s->n, tensor_id);
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }
            DestroyAgent(&tmp, _ABC_);
            DestroyTensor(&tmp_t, s->n);
        }

        /* Calculation of new probabilities */
        max_fitness = s->a[0]->fit;
        for (i = 1; i < s->m; i++)
            if (s->a[i]->fit > max_fitness)
                max_fitness = s->a[i]->fit;
        for (i = 0; i < s->m; i++)
            prob[i] = (0.9 * (s->a[i]->fit / (max_fitness + 0.00000001))) + 0.1;

        /* Onlooker Bee step */
        i = 0;
        l = 0;
        while (l < s->m)
        {
            r = GenerateUniformRandomNumber(0, 1);
            if (r < prob[i])
            {
                va_copy(arg, argtmp);
                l++;
                chosen_param = GenerateUniformRandomNumber(0, s->n - 1); /* Randomly parameter to be used */
                do
                {
                    neighbour = GenerateUniformRandomNumber(0, s->m - 1); /* Randomly neighbour to be used, which must be different from i */
                } while (neighbour == i);

                tmp = CopyAgent(s->a[i], _ABC_, _NOTENSOR_);
                tmp_t = CopyTensor(s->a[i]->t, s->n, tensor_id);
                for (k = 0; k < tensor_id; k++)
                    tmp_t[chosen_param][k] = s->a[i]->t[chosen_param][k] + (s->a[i]->t[chosen_param][k] - s->a[neighbour]->t[chosen_param][k]) * r; /* We now update our currently solution */
                CheckTensorLimits(s, tmp_t, tensor_id);
                for (j = 0; j < s->n; j++)
                    tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);

                fitValue = Evaluate(tmp, arg); /* It executes the fitness function for agent tmp */
                if (fitValue < s->a[i]->fit)
                { /* We accept the new solution */
                    trial[i] = 0;
                    DestroyTensor(&s->a[i]->t, s->n);
                    DestroyAgent(&(s->a[i]), _ABC_);
                    s->a[i] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                    s->a[i]->fit = fitValue;
                    s->a[i]->t = CopyTensor(tmp_t, s->n, tensor_id);
                }
                else
                {
                    trial[i]++; /* If the solution could not be improved, we increase the trial counter */
                }
                if (fitValue < s->gfit)
                { /* Update the global best */
                    s->gfit = fitValue;
                    DestroyTensor(&s->t_g, s->n);
                    s->t_g = CopyTensor(tmp_t, s->n, tensor_id);
                    for (j = 0; j < s->n; j++)
                        s->g[j] = tmp->x[j];
                }
                DestroyAgent(&tmp, _ABC_);
                DestroyTensor(&tmp_t, s->n);
            }
            i++;
            if (i == s->m)
                i = 0;
        }

        /* Scout Bee step */
        max_trial_index = 0;
        for (i = 0; i < s->m; i++)
            if (trial[i] > trial[max_trial_index])
                max_trial_index = i;
        if (trial[max_trial_index] >= limit)
        {
            va_copy(arg, argtmp);
            trial[max_trial_index] = 0;
            tmp = GenerateNewAgent(s, _ABC_);
            tmp_t = GenerateNewTensor(s, tensor_id);
            CheckTensorLimits(s, tmp_t, tensor_id);
            for (j = 0; j < s->n; j++)
                tmp->x[j] = TensorSpan(s->LB[j], s->UB[j], tmp_t[j], tensor_id);
            fitValue = Evaluate(tmp, arg); /* It executes the fitness function for new created agent */
            if (fitValue < s->a[max_trial_index]->fit)
            { /* We accept the new solution */
                DestroyTensor(&s->a[max_trial_index]->t, s->n);
                DestroyAgent(&(s->a[max_trial_index]), _ABC_);
                s->a[max_trial_index] = CopyAgent(tmp, _ABC_, _NOTENSOR_);
                s->a[max_trial_index]->fit = fitValue;
                s->a[max_trial_index]->t = CopyTensor(tmp_t, s->n, tensor_id);
            }
            if (fitValue < s->gfit)
            { /* update the global best */
                s->gfit = fitValue;
                DestroyTensor(&s->t_g, s->n);
                s->t_g = CopyTensor(tmp_t, s->n, tensor_id);
                for (j = 0; j < s->n; j++)
                    s->g[j] = tmp->x[j];
            }
            DestroyAgent(&tmp, _ABC_);
            DestroyTensor(&tmp_t, s->n);
        }

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

    free(trial);
    free(prob);
    va_end(arg);
}
/*************************/