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

#include "bsa.h"

/* It executes the Backtracking Search Optimization Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runBSA(SearchSpace *s, prtFun Evaluate, ...)
{
	/*Initialization*/
    va_list arg, argtmp;
    int t, i, j;
    double fitValue;

	double** Mutation = NULL;
	double** Map = NULL; /*Matrix representing values to be permuted*/
    Mutation = (double **)calloc(s->m, sizeof(double *));
	Map = (double **)calloc(s->m, sizeof(double *));
    for (i = 0; i < s->m; i++)
	{
        Mutation[i] = (double *)calloc(s->n, sizeof(double));
		Map[i] = (double *)calloc(s->n, sizeof(double));
	}
    Agent *tmp = NULL;

	SearchSpace *oldS = CreateSearchSpace(s->m,s->n,_BSA_);
	//oldS->iterations = s->iterations;
	//oldS->mix_rate = s->mix_rate;
	//oldS->F = s->F;
	
	InitializeSearchSpace(oldS, _BSA_);

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runBSA.\n");
        exit(-1);
    }

    if (!oldS)
    {
        fprintf(stderr, "\nSearch space not allocated @runBSA.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _BSA_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
		fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
		va_copy(arg, argtmp);
		/*SELECTION - I*/
		if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
			ReplaceSearchSpaceAgents(s,oldS);
		Permutation(oldS, _BSA_);
		/*GENERATION OF TRIAL POPULATION*/
		/**MUTATION*/
		setMutation(s, oldS, Mutation);
		/**CROOS OVER */			
		SearchSpace *T = NULL;
		T = crossOverStrategyOfBSA(s, oldS, Map, Mutation); /*Trial-population*/
		boundaryControlMechanism(s,T);

		/*SELECTION - II*/
		EvaluateSearchSpace(T, _BSA_, Evaluate, arg);
		for (i = 0; i < s->m; i++)
		{
			if ( T->a[i]->fit <s->a[i]->fit)
			{
		        DestroyAgent(&(s->a[i]), _BSA_);
		        s->a[i] = CopyAgent(T->a[i], _BSA_, _NOTENSOR_);
		        s->a[i]->fit = T->a[i]->fit;
			}

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->best = i;
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                    s->g[j] = s->a[i]->x[j];
            }
		}

		DestroySearchSpace(&T, _BSA_);
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }


    for (i = 0; i < s->m; i++)
	{
        free(Mutation[i]);
		free(Map[i]);
	}
    free(Mutation);
	free(Map);
	DestroySearchSpace(&oldS, _BSA_);
    va_end(arg);
}

void boundaryControlMechanism(SearchSpace *s,SearchSpace *T)
{
	int i,j;
	double a,b,c,d;
	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
		{
			//fprintf(stderr, "a = %lf\n",T->a[i]->x[j]);
			//fprintf(stderr, "b = %lf\n",s->LB[j]);
			//fprintf(stderr, "c = %lf\n",T->a[i]->x[j]);
			//fprintf(stderr, "d = %lf\n",s->UB[j]);
			if (T->a[i]->x[j] < s->LB[j] || T->a[i]->x[j] > s->UB[j])
			{
				T->a[i]->x[j] = ( (s->UB[j] - s->LB[j]) * ((double)rand() / RAND_MAX)) + s->LB[j] ;
			}
		}
	}
}

void setMutation(SearchSpace *s, SearchSpace *oldS, double** Mutation)
{
	int i, j;
	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
			Mutation[i][j] =  s->a[i]->x[j] + (s->F*GenerateUniformRandomNumber(0.0, 1.0)*(oldS->a[i]->x[j] - s->a[i]->x[j]));
	}
}

void initializeMap(SearchSpace *s,  double** Map)
{
	int i,j;
    for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			Map[i][j] = 1;
}

SearchSpace *crossOverStrategyOfBSA(SearchSpace *s, SearchSpace *OldS, double** Map, double** Mutation)
{
	int i,j, u, MaxU;
	initializeMap(s, Map);

	/*number of permutations*/
	if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
	{
		MaxU = (int)ceil(s->mix_rate * s->n * GenerateUniformRandomNumber(0.0, 1.0));
		for (i = 0; i < s->m; i++)			
			for (j = 1; j <= MaxU; j++)
			{
				u = rand() % s->n;
				Map[i][u] = 0;
			}
	}
	else
	{
		int randi;
		for (i = 0; i < s->m; i++)
		{
			randi = rand() % s->n;
			Map[i][randi] = 0;
		}
	}
    SearchSpace *T = NULL;
	T = CreateSearchSpace(s->m,s->n,_BSA_);
	InitializeSearchSpace(T, _BSA_);

	// Generation of a trial population
    for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			T->a[i]->x[j] = Mutation[i][j];

	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
		{
			if (Map[i][j] == 1)
				T->a[i]->x[j] = s->a[i]->x[j];
		}
	}
	return T;
}

