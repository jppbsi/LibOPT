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

#include "bso.h"
#include "function.h"

/* BSO-related functions */

/* It clusters the agents and returns a pointer with the best agent's ID per cluster.
Parameters:
s: search space
best_ideas: pointer to the ids of the best ideas per cluster (k-sized array)
ideas_per_cluster: pointer to the ids of the ideas per cluster (k x (Y_i)+1-sized array)
where Y_i stands for the number of ideas in cluster i. Notice we have one more column (the first one)
that stores the number of ideas that belongs to cluster i. */
void k_means(SearchSpace *s, int *best_ideas, int ***ideas_per_cluster)
{
	int *nearest = NULL, *ctr = NULL, i, j, r;
	char *is_chosen = NULL, OK;
	double **center = NULL, old_error, error = DBL_MAX, min_distance, distance;
	double **center_mean = NULL, *best_fitness_cluster = NULL;

	if ((!s) || (!best_ideas) || (!ideas_per_cluster))
	{
		fprintf(stderr, "\nSearch space and/or input arrays not allocated @k_means.\n");
		exit(-1);
	}

	best_fitness_cluster = (double *)malloc(s->k * sizeof(double));
	nearest = (int *)malloc(s->m * sizeof(int));
	ctr = (int *)calloc(s->k, sizeof(int));
	center = (double **)malloc(s->k * sizeof(double *));
	center_mean = (double **)malloc(s->k * sizeof(double *));
	is_chosen = (char *)calloc(s->m, sizeof(char));

	/* initializing k centers with samples choosen at random */
	for (i = 0; i < s->k; i++)
	{
		center[i] = (double *)malloc(s->n * sizeof(double));
		center_mean[i] = (double *)calloc(s->n, sizeof(double));
		OK = j = 0;
		do
		{
			j++;
			r = (int)GenerateUniformRandomNumber(0, s->m);
			if (!is_chosen[r])
			{
				is_chosen[r] = 1;
				OK = 1;
			}
		} while ((!OK) && (j <= s->m));
		if (j > s->m)
		{
			fprintf(stderr, "\nProblems initializing the k centers @k_means. Probably k is too large.\n");
			exit(-1);
		}
		for (j = 0; j < s->n; j++)
			center[i][j] = s->a[r]->x[j];
	}

	/* main algorithm */
	do
	{
		old_error = error;
		error = 0;

		for (i = 0; i < s->k; i++)
		{
			ctr[i] = 0;
			for (j = 0; j < s->n; j++)
				center_mean[i][j] = 0;
		}

		/* for each idea, it finds the nearest center */
		for (i = 0; i < s->m; i++)
		{
			min_distance = DBL_MAX;

			for (j = 0; j < s->k; j++)
			{
				distance = EuclideanDistance(s->a[i]->x, center[j], s->n);
				if (distance < min_distance)
				{
					nearest[i] = j;
					min_distance = distance;
				}
			}

			/* after finding the nearest center, we accumulate
	    the idea's coordinates at this center */
			for (j = 0; j < s->n; j++)
				center_mean[nearest[i]][j] += s->a[i]->x[j];

			ctr[nearest[i]]++;
			error += min_distance;
		}
		error /= s->m;

		/* updating the centers */
		for (i = 0; i < s->k; i++)
		{
			for (j = 0; j < s->n; j++)
			{
				if (ctr[i])
					center[i][j] = center_mean[i][j] / ctr[i];
				else
					center[i][j] = center_mean[i][j];
			}
		}
	} while (fabs(error - old_error) > 1e-5);

	/* identifying the best idea (smallest fitness) per cluster */
	for (i = 0; i < s->k; i++)
	{
		best_fitness_cluster[i] = DBL_MAX;

		/* it allocates an array to store the ids of the ideas of cluster i. The first position stores the number of ideas clustered in cluster i. */
		(*ideas_per_cluster)[i] = (int *)calloc((ctr[i] + 1), sizeof(int));
	}

	for (i = 0; i < s->m; i++)
	{
		(*ideas_per_cluster)[nearest[i]][ctr[nearest[i]]] = i;
		ctr[nearest[i]]--;
		if (s->a[i]->fit < best_fitness_cluster[nearest[i]])
		{
			best_fitness_cluster[nearest[i]] = s->a[i]->fit;
			best_ideas[nearest[i]] = i;
		}
	}
	/*************************************************************/

	for (i = 0; i < s->k; i++)
	{
		free(center[i]);
		free(center_mean[i]);
	}
	free(center);
	free(center_mean);
	free(is_chosen);
	free(nearest);
	free(ctr);
	free(best_fitness_cluster);
}
/****************************/

/* It executes the Brain Storm Optimization for function minimization according to Algorithm 1 (El-Abd, 2017)
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runBSO(SearchSpace *s, prtFun Evaluate, ...)
{
	va_list arg, argtmp;
	int i, j, z, k, t, *best = NULL, c1, c2, **ideas_per_cluster = NULL;
	double p, r;
	Agent *nidea = NULL;

	va_start(arg, Evaluate);
	va_copy(argtmp, arg);

	if (!s)
	{
		fprintf(stderr, "\nSearch space not allocated @runBSO.\n");
		exit(-1);
	}

	ideas_per_cluster = (int **)malloc(s->k * sizeof(int *));
	best = (int *)malloc(s->k * sizeof(int));
	nidea = CreateAgent(s->n, _BSO_, _NOTENSOR_);

	EvaluateSearchSpace(s, _BSO_, Evaluate, arg); /* Initial evaluation */

	for (t = 1; t <= s->iterations; t++)
	{
		fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

		/* clustering ideas */
		k_means(s, best, &ideas_per_cluster);

		/* for each idea */
		for (i = 0; i < s->m; i++)
		{
			va_copy(arg, argtmp);

			p = GenerateUniformRandomNumber(0, 1);
			if (s->p_one_cluster > p)
			{
				c1 = (int)GenerateUniformRandomNumber(0, s->k); /* selecting a cluster probabilistically */
				p = GenerateUniformRandomNumber(0, 1);

				/* creating a new idea based on the cluster selected previously.
		We also consider if cluster c1 has a single idea, i.e., ideas_per_cluster[c1][0] == 0.
		Notice we do not consider the cluster's center into that computation @kmeans function, which means a
		unitary cluster has ideas_per_cluster[c1][0] == 0. */
				if ((s->p_one_center > p) || (ideas_per_cluster[c1][0] == 0))
				{
					for (k = 0; k < s->n; k++)
						nidea->x[k] = s->a[best[c1]]->x[k];
				}
				else
				{ /* creating a new idea based on another idea j selected randomly from cluster c1 */
					j = (int)GenerateUniformRandomNumber(1, ideas_per_cluster[c1][0]);
					j = ideas_per_cluster[c1][j];

					for (k = 0; k < s->n; k++)
						nidea->x[k] = s->a[j]->x[k];
				}
			}
			else
			{

				/* selecting two clusters' centers probabilistically */
				c1 = (int)GenerateUniformRandomNumber(0, s->k);
				c2 = (int)GenerateUniformRandomNumber(0, s->k);

				/* selecting two ideas randomly */
				if (ideas_per_cluster[c1][0] == 0)
					j = best[c1];
				else
				{
					j = (int)GenerateUniformRandomNumber(1, ideas_per_cluster[c1][0]);
					j = ideas_per_cluster[c1][j];
				}

				if (ideas_per_cluster[c2][0] == 0)
					z = best[c2];
				else
				{
					z = (int)GenerateUniformRandomNumber(1, ideas_per_cluster[c2][0]);
					z = ideas_per_cluster[c2][z];
				}

				p = GenerateUniformRandomNumber(0, 1);
				r = GenerateUniformRandomNumber(0, 1);

				/* it creates a new idea based on a random combination of two selected clusters' centers */
				if (s->p_two_centers > p)
				{
					for (k = 0; k < s->n; k++)
						nidea->x[k] = r * s->a[best[c1]]->x[k] + (1 - r) * s->a[best[c2]]->x[k];
				}
				else
				{ /* it creates a new idea based on the ideas selected at random from the clusters previously chosen */
					for (k = 0; k < s->n; k++)
						nidea->x[k] = r * s->a[j]->x[k] + (1 - r) * s->a[z]->x[k];
				}
			}

			/* adding local noise to the new created idea */
			p = (0.5 * s->iterations - t) / k;
			r = GenerateUniformRandomNumber(0, 1) * Logistic_Sigmoid(p);

			for (k = 0; k < s->n; k++)
				nidea->x[k] += r * randGaussian(0, 1);

			/* It evaluates the new created idea */
			CheckAgentLimits(s, nidea);
			p = Evaluate(nidea, arg);
			if (p < s->a[i]->fit)
			{ /* if the new idea is better than the current one */
				for (k = 0; k < s->n; k++)
					s->a[i]->x[k] = nidea->x[k];
				s->a[i]->fit = p;
			}

			if (s->a[i]->fit < s->gfit)
				s->gfit = s->a[i]->fit;
		}

		fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

		for (i = 0; i < s->k; i++)
			free(ideas_per_cluster[i]);
	}

	free(ideas_per_cluster);
	free(best);
	DestroyAgent(&nidea, _BSO_);
	va_end(arg);
}
/*************************/