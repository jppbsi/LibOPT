#include "ga.h"

/* It executes the Genetic Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate chromosomes
arg: list of additional arguments */

void runGA(SearchSpace *s, prtFun Evaluate, ...)
{
	va_list arg, argtmp;
	int i, j, k, t;
	int *selection = NULL;
	int crossover_index, mutation_index;
	double **tmp;

	va_start(arg, Evaluate);
	va_copy(argtmp, arg);

	if (!s)
	{
		fprintf(stderr, "\nSearch space not allocated @runGA.\n");
		exit(-1);
	}

	EvaluateSearchSpace(s, _GA_, Evaluate, arg); /* Initial evaluation of the search space */
	
	tmp = (double **)calloc(s->m, sizeof(double *));
	for(i = 0; i < s->m; i++)
		tmp[i] = (double *)calloc(s->n, sizeof(double));

	for (t = 1; t <= s->iterations; t++)
	{
		fprintf(stderr, "\nRunning generation %d/%d ... ", t, s->iterations);

		/* It performs the selection */
		selection = RouletteSelectionGA(s, s->m);

		/* It performs the crossover */
		for(i = 0; i < s->m / 2; i += 2)
		{
			crossover_index = (int) GenerateUniformRandomNumber(0, s->n);

			for(k = 0; k < s->n; k++)
			{
				if(k < crossover_index)
				{
					tmp[i][k] = s->a[selection[i]]->x[k];
					tmp[i+1][k] = s->a[selection[i+1]]->x[k];
				}
				else
				{
					tmp[i][k] = s->a[selection[i+1]]->x[k];
					tmp[i+1][k] = s->a[selection[i]]->x[k];
				}

			}
		}

		if(s->m % 2 != 0)
		{
			crossover_index = (int) GenerateUniformRandomNumber(0, s->n);

			for(k = 0; k < s->n; k++) 
			{
				if(k < crossover_index)
				{
					tmp[s->m - 1][k] = s->a[selection[s->m - 1]]->x[k];
				}
				else
				{
					tmp[s->m - 1][k] = s->a[selection[0]]->x[k];
				}
			}
		}

		/* It performs the mutation */
		for(i = 0; i < s->m; i++)
		{
			if(GenerateUniformRandomNumber(0, 1) <= s->pMutation)
			{
				mutation_index = (int) GenerateUniformRandomNumber(0, s->n);
				tmp[i][mutation_index] = GenerateUniformRandomNumber(s->LB[mutation_index], s->UB[mutation_index]);
			}

		}

		/* It changes the generation */
		for(i = 0; i < s->m; i++)
		{
			for(j = 0; j < s->n; j++)
			{
				s->a[i]->x[j] = tmp[i][j];
			}
		}

		EvaluateSearchSpace(s, _GA_, Evaluate, arg);

		free(selection);
	}

	fprintf(stderr, "\nOK (minimum fitness value %lf)\n", s->gfit);

	for(i = 0; i < s->m; i++)
		free(tmp[i]);

	free(tmp);


	va_end(arg);
}