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
	SearchSpace *T = NULL;
	SearchSpace *oldS = CreateSearchSpace(s->m, s->n, _BSA_);

	double** Mutation = NULL;
	double** Map = NULL; /* Matrix representing values to be permuted */
    Mutation = (double **)calloc(s->m, sizeof(double *));
	Map = (double **)calloc(s->m, sizeof(double *));
    for (i = 0; i < s->m; i++)
	{
        Mutation[i] = (double *)calloc(s->n, sizeof(double));
		Map[i] = (double *)calloc(s->n, sizeof(double));
	}
	for (j=0;j<s->n;j++)
	{
		oldS->LB[j] = s->LB[j];
		oldS->UB[j] = s->UB[j];
	}
	
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

		/* SELECTION - I */
		if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
			CopySearchSpaceAgents(s, oldS, _BSA_, _NOTENSOR_);
		Permutation(oldS, _BSA_, _NOTENSOR_);

		/* GENERATION OF TRIAL POPULATION */
		/** MUTATION */
		InitializeMutation(s, oldS, Mutation);

		/** CROSS OVER */			
		T = CrossOverStrategyOfBSA(s, Map, Mutation); /* Trial-population */
		BoundaryControlMechanism(s, T);

		/* SELECTION - II */
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

void BoundaryControlMechanism(SearchSpace *s, SearchSpace *T)
{
	int i,j;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @BoundaryControlMechanism.\n");
        exit(-1);
    }

    if (!T)
    {
        fprintf(stderr, "\nSearch space not allocated @BoundaryControlMechanism.\n");
        exit(-1);
    }

	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
		{
			if ((T->a[i]->x[j] < s->LB[j]) || (T->a[i]->x[j] > s->UB[j]))
			{
				T->a[i]->x[j] = ( (s->UB[j] - s->LB[j]) * ((double)rand() / RAND_MAX)) + s->LB[j] ;
			}
		}
	}
}

void InitializeMutation(SearchSpace *s, SearchSpace *oldS, double** Mutation)
{
	int i, j;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @InitializeMutation.\n");
        exit(-1);
    }

    if (!oldS)
    {
        fprintf(stderr, "\nSearch space not allocated @InitializeMutation.\n");
        exit(-1);
    }

	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
			Mutation[i][j] =  s->a[i]->x[j] + (s->F*GenerateUniformRandomNumber(0.0, 1.0)*(oldS->a[i]->x[j] - s->a[i]->x[j]));
	}
}

void InitializeTensorMutation(SearchSpace *s, SearchSpace *oldS, double*** Mutation, int tensor_id)
{
	int i, j, k;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @InitializeMutation.\n");
        exit(-1);
    }

    if (!oldS)
    {
        fprintf(stderr, "\nSearch space not allocated @InitializeMutation.\n");
        exit(-1);
    }

	for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			for (k = 0; k < tensor_id; k++)
				Mutation[i][j][k] =  s->a[i]->t[j][k] + (s->F*GenerateUniformRandomNumber(0.0, 1.0)*(oldS->a[i]->t[j][k] - s->a[i]->t[j][k]));
}

void InitializeMap(SearchSpace *s, double** Map)
{
	int i,j;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @InitializeMap.\n");
        exit(-1);
    }

    for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			Map[i][j] = 1;
}

SearchSpace *CrossOverStrategyOfBSA(SearchSpace *s, double** Map, double** Mutation)
{
	int i,j, u, MaxU, randi;
	SearchSpace *T = NULL;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @CrossOverStrategyOfBSA.\n");
        exit(-1);
    }


	InitializeMap(s, Map);

	/* number of permutations */
	if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
	{
		MaxU = ceil(s->mix_rate * s->n * GenerateUniformRandomNumber(0.0, 1.0));
		for (i = 0; i < s->m; i++)			
			for (j = 1; j <= MaxU; j++)
			{
				u = rand() % s->n;
				Map[i][u] = 0;
			}
	}
	else
	{		
		for (i = 0; i < s->m; i++)
		{
			randi = rand() % s->n;
			Map[i][randi] = 0;
		}
	}
    
	T = CreateSearchSpace(s->m, s->n, _BSA_);
	for (j=0;j<s->n;j++)
	{
		T->LB[j] = s->LB[j];
		T->UB[j] = s->UB[j];
	}
	InitializeSearchSpace(T, _BSA_);


	/* Generation of a trial population */
    for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			T->a[i]->x[j] = Mutation[i][j];

	for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
		{
			if (Map[i][j])
				T->a[i]->x[j] = s->a[i]->x[j];
		}
	}
	return T;
}


SearchSpace *CrossOverTensorStrategyOfBSA(SearchSpace *s, double** Map, double*** Mutation, int tensor_id)
{
	int i,j, k, u, MaxU, MaxTU, randi;
	SearchSpace *T = NULL;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @CrossOverStrategyOfBSA.\n");
        exit(-1);
    }


	InitializeMap(s, Map);

	/* number of permutations */
	if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
	{
		MaxU = ceil(s->mix_rate * s->n * GenerateUniformRandomNumber(0.0, 1.0));
		for (i = 0; i < s->m; i++)	
		{		
			for (j = 1; j <= MaxU; j++)
			{
				u = rand() % s->n;
				Map[i][u] = 0;
			}
		}
	}
	else
	{		
		for (i = 0; i < s->m; i++)
		{
			randi = rand() % s->n;
			Map[i][randi] = 0;
		}
	}
    
	T = CreateSearchSpace(s->m, s->n, _BSA_);

	for (j=0;j < T->n; j++)
	{
		T->LB[j] = s->LB[j];
		T->UB[j] = s->UB[j];
	}	

    T->t_g = CreateTensor(T->n, tensor_id);
    for (i = 0; i < T->m; i++)
        T->a[i]->t = CreateTensor(T->n, tensor_id); /* It allocates a new tensor for each agent */

    InitializeTensorSearchSpace(T, tensor_id); /* It initalizes the search space with tensors */


	/* Generation of a trial population */
    for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			for (k = 0; k < tensor_id; k++)
				T->a[i]->t[j][k] = Mutation[i][j][k];

	for (i = 0; i < s->m; i++)
		for (j = 0; j < s->n; j++)
			if (Map[i][j])
				for (k = 0; k < tensor_id; k++)
					T->a[i]->t[j][k] = s->a[i]->t[j][k];
	return T;
}


/* It executes the Tensor-based Backtracking Search Optimization Algorithm for function minimization
Parameters:
s: search space
tensor_id: identifier of tensor's dimension
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runTensorBSA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...)
{
	/*Initialization*/
    va_list arg, argtmp;
    int t, i, j, k;
	SearchSpace *T = NULL;
	SearchSpace *oldS = CreateSearchSpace(s->m, s->n, _BSA_);

	double*** Mutation = NULL;
	double** Map = NULL; /* Matrix representing values to be permuted */
    Mutation = (double ***)calloc(s->m, sizeof(double **));
	Map = (double **)calloc(s->m, sizeof(double *));
    for (i = 0; i < s->m; i++)
	{
        Mutation[i] = (double **)calloc(s->n, sizeof(double *));
		Map[i] = (double *)calloc(s->n, sizeof(double));
		for (j = 0; j < s->n; j++)
		    Mutation[i][j] = (double *)calloc(tensor_id, sizeof(double ));
	}
	for (j=0;j<s->n;j++)
	{
		oldS->LB[j] = s->LB[j];
		oldS->UB[j] = s->UB[j];
	}	

    oldS->t_g = CreateTensor(oldS->n, tensor_id);
    for (i = 0; i < oldS->m; i++)
        oldS->a[i]->t = CreateTensor(oldS->n, tensor_id); /* It allocates a new tensor for each agent */

    InitializeTensorSearchSpace(oldS, tensor_id); /* It initalizes the search space with tensors */

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runTensorBSA.\n");
        exit(-1);
    }

    if (!oldS)
    {

        fprintf(stderr, "\nSearch space not allocated @runTensorBSA.\n");
        exit(-1);
    }

	for (i = 0; i < s->m; i++)
	{
	    CheckTensorLimits(s, s->a[i]->t, tensor_id);
	    for (j = 0; j < s->n; j++)
	        s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
	}

    EvaluateTensorSearchSpace(s, _BSA_, tensor_id, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
		fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
		va_copy(arg, argtmp);

		/* SELECTION - I */
		if(GenerateUniformRandomNumber(0.0, 1.0)<GenerateUniformRandomNumber(0.0, 1.0))
			CopySearchSpaceAgents(s, oldS, _BSA_, tensor_id);


		TensorPermutation(oldS, _BSA_, tensor_id);
		/* GENERATION OF TRIAL POPULATION */
		/** MUTATION */
		InitializeTensorMutation(s, oldS, Mutation, tensor_id);

		/** CROSS OVER */			
		T = CrossOverTensorStrategyOfBSA(s, Map, Mutation, tensor_id); /* Trial-population */


		for (i = 0; i < T->m; i++)
		{
		    CheckTensorLimits(T, T->a[i]->t, tensor_id);
		    for (j = 0; j < T->n; j++)
		        T->a[i]->x[j] = TensorSpan(T->LB[j], T->UB[j], T->a[i]->t[j], tensor_id);
		}
		BoundaryControlMechanism(s, T);

		/* SELECTION - II */
		EvaluateTensorSearchSpace(T, _BSA_, tensor_id, Evaluate, arg);
		for (i = 0; i < s->m; i++)
		{
			if ( T->a[i]->fit <s->a[i]->fit)
			{
				DestroyTensor(&(s->a[i]->t), s->n);
		        DestroyAgent(&(s->a[i]), _BSA_);
		        s->a[i] = CopyAgent(T->a[i], _BSA_, tensor_id);
				s->a[i]->t = CopyTensor(T->a[i]->t, s->n, tensor_id);
			}

            if (s->a[i]->fit < s->gfit)
            {
                s->best = i;
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
				{
                    s->g[j] = s->a[i]->x[j];
                    for (k = 0; k < tensor_id; k++)
                        s->t_g[j][k] = s->a[i]->t[j][k];
				}
            }
		}



		DestroyTensor(&(T->t_g), T->n);
		for (i = 0; i < T->m; i++)
		    DestroyTensor(&(T->a[i]->t), T->n);  

		DestroySearchSpace(&T, _BSA_);  
        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);

    }


    for (i = 0; i < s->m; i++)
	{
		for (j = 0; j < s->n; j++)
		{
		    free(Mutation[i][j]);
		}
	    free(Mutation[i]);
		free(Map[i]);
	}
    free(Mutation);
	free(Map);
	DestroyTensor(&oldS->t_g, oldS->n);
	for (i = 0; i < oldS->m; i++)
	    DestroyTensor(&oldS->a[i]->t, oldS->n); /* It deallocates the tensor for each agent */

	DestroySearchSpace(&oldS, _BSA_); /* It deallocates the search space */
    va_end(arg);
}

