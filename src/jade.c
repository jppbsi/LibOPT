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

#include "jade.h"

/* It executes the Adaptive Differential Evolution with Optional External Archive for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate nests
arg: list of additional arguments */
void runJADE(SearchSpace *s, prtFun Evaluate, ...)
{
    va_list arg, argtmp;
    int t, i, j;
	int n_elements_lists = 0, n_elements_archive = 0;
	double uF = 0.5, uCR = 0.5; /* Mean Mutation Factor and Crossover parameters, respectivelly */
	double Fi, CRi; /* Mutation scale Factor and Crossover controle parameter for each individual */

	double* Sf = NULL; /* scale Factor parameter for each individual */
	double* Scr = NULL; /* Crossover parameter for each individual */
	double* mutation = NULL;
	SearchSpace *crossOver = NULL;
	SearchSpace *A = NULL;

	crossOver = CreateSearchSpace(s->m, s->n, _JADE_);

	for (j=0;j < s->n; j++)
	{
		crossOver->LB[j] = s->LB[j];
		crossOver->UB[j] = s->UB[j];
	}

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);


	/* ----- paper variables ---------
	N P = s->m - population size
	D = s->n - dimension of the problem
	G = s->iterations -  number of generations
	v = mutation - mutation vector
	u = crossOver - crossOver vector
	x = s->a[i] - current agent
	A = A - archive population
	P = s - current population
	*/
	
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runJADE.\n");
        exit(-1);
    }

	if (s->p_greediness < 0.0 || s->p_greediness > 1.0)
	{
		fprintf(stderr, "\np out of bounds @runJADE.\n");
		exit(-1);
	}

	A = CreateSearchSpace(s->m, s->n, _JADE_);

	for (j=0;j < s->n; j++)
	{
		A->LB[j] = s->LB[j];
		A->UB[j] = s->UB[j];
	}
	InitializeSearchSpace(A, _JADE_);

    EvaluateSearchSpace(s, _JADE_, Evaluate, arg); /* Initial evaluation of the search space */

    for (t = 1; t <= s->iterations; t++)
    {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);
        va_copy(arg, argtmp);
		if(n_elements_lists > 0)
		{
			if (Sf) free(Sf);  
			if (Scr) free(Scr);  
		}
		n_elements_lists = 0;

		for (i = 0; i<s->m; i++)
		{
			/* SetCriFi */
			CRi = GenerateGaussianRandomNumber(uCR, 0.1); 
			Fi = GenerateCauchyRandomNumber(uF, 0.1);

			/* MUTATION */
			mutation = MutationJade(i,s, A, Fi, n_elements_archive);

			/* CROSSOVER */
			CrossoverJade(s, crossOver, i, mutation, CRi);

			/* SELECTION */
			EvaluateAgent(crossOver, crossOver->a[i], _JADE_, Evaluate, arg);
			if( s->a[i]->fit > crossOver->a[i]->fit )
			{
				n_elements_lists= n_elements_lists+1;
	
				InsertAgentIntoArchive(A, s, s->a[i], &n_elements_archive);
				DestroyAgent(&(s->a[i]), _JADE_);
				s->a[i] = CopyAgent(crossOver->a[i], _JADE_, _NOTENSOR_);
		        if (s->a[i]->fit < s->gfit) 
		        { /* It updates the global best value and position */
		            s->best = i;
		            s->gfit = s->a[i]->fit;
		            for (j = 0; j < s->n; j++)
		                s->g[j] = s->a[i]->x[j];
		        }
	
				Sf = AddList(Sf, Fi, n_elements_lists);
				Scr = AddList(Scr, CRi, n_elements_lists);
			}

			if(mutation) free(mutation);

		}
		uCR = ((1.0 - s->c) * uCR) + (s->c * ArithmeticMeanList(Scr, n_elements_lists));
		uF = ((1.0 - s->c) * uF) + (s->c * LehmerMeanList(Sf, n_elements_lists));

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
    }

	DestroySearchSpace(&A, _JADE_);
	DestroySearchSpace(&crossOver, _JADE_);
	if (n_elements_lists>0) free(Sf); 
	if (n_elements_lists>0) free(Scr);
    va_end(arg);
}

/* It executes the crossover operation 
Parameters:
s: search space
crossover: search space containing crossover information
mutation: a vector containing mutation information 
CRi: Crossover controler parameter for ith individual */
void CrossoverJade(SearchSpace* s, SearchSpace* crossover, int i, double* mutation, double CRi)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @CrossoverJade.\n");
        exit(-1);
    }

    if (!crossover)
    {
        fprintf(stderr, "\nSearch space Crossover not allocated @CrossoverJade.\n");
        exit(-1);
    }

	int  j_rand, j;

	j_rand = (int)round(GenerateUniformRandomNumber(1.0, (double)s->n));
	for (j = 0; j < s->n; j++)
	{
		if ( j == j_rand || GenerateUniformRandomNumber(0.0, 1.0)< CRi)
		{
			crossover->a[i]->x[j] = mutation[j];
		}
		else
		{
			crossover->a[i]->x[j] = s->a[i]->x[j];
		}
	}
}

/* It generates a mutate vector  
Parameters:
i: index of current individual
s: search space
A: search space containing archived individuals
Fi: Mutation scale Factor  for ith individual
n_elements_archive: number of elements in A */
double* MutationJade(int i, SearchSpace *s, SearchSpace *A, double Fi, int n_elements_archive) 
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @MutationJade.\n");
        exit(-1);
    }

	Agent *bestP = NULL, *r1 = NULL, * r2 = NULL; 
    int r1_index, j;
	double* mutation = NULL;

	mutation = (double *)calloc(s->n, sizeof(double));

	bestP = GetBestPAgent(s); /* Randomly choose bestP as one of the 100 p% best vectors */
	r1 = Getr1Agent(s, i, &r1_index); /* Randomly choose r1 from current population P */
	r2 = Getr2Agent(s, A, i, r1_index, n_elements_archive); /* Randomly choose r2 from current population P union Archive population A */ 

	for(j = 0; j<s->n; j++)
	{
		/* Mutation */
		mutation[j] = s->a[i]->x[j] + (Fi * (bestP->x[j] - s->a[i]->x[j] )) + (Fi * (r1->x[j] - r2->x[j]));

		/* Bounds control */
		if (mutation[j] < s->LB[j])
			mutation[j] = (s->LB[j] + s->a[i]->x[j])/2;
	  	if (mutation[j] > s->UB[j])
		    mutation[j] = (s->UB[j] + s->a[i]->x[j])/2;
	}
	DestroyAgent(&bestP, _JADE_);
	DestroyAgent(&r1, _JADE_);
	DestroyAgent(&r2, _JADE_);

    return mutation;
}

/* It calculates the Lehmer mean of a given list of doubles 
Parameters:
list: list of elements
nElements: number of elements in list */
double LehmerMeanList(double* list, int nElements)
{
	int i;
	double v = 0, p = 0, r = 0;
	if (nElements>0)
	{
		for (i = 0; i<nElements; i++)
		{
			v = v + list[i];
			p = p + pow(list[i],2);
		}
		if (v > 0.0) r = p/v;
	}	
	return r;
}

/* It calculates the Arithmetic mean of a given list of doubles 
Parameters:
list: list of elements
nElements: number of elements in list */
double ArithmeticMeanList(double* list, int nElements)
{
	int i;
	double v = 0,r = 0;
	if (nElements>0)
	{
		for (i=0; i<nElements; i++)
			v = v + list[i];
		r = v/nElements;
	}
	
	return r;
}

/* Insert a double into a predefined list of doubles 
Parameters:
list: list of elements
value: value to be added
nElements: number of elements in list */
double* AddList( double *list, double value, int nElements)
{
	double* l = NULL;
	int i;
	l = (double *)(double *)calloc(nElements, sizeof(double));   
	if(nElements > 1)
	{
		for(i = 0; i < nElements-1; i++)
			l[i] = list[i];
		free(list);
	}
	l[nElements - 1] = value;
	return l;
}

/* Insert an agent replaced in the current population into an archive list 
Parameters:
A: search space containing archived individuals
s: search space
a: agent to be inserted in the list
n_elements_archive: number of elements in A */
void InsertAgentIntoArchive(SearchSpace *A, SearchSpace *s, Agent *a, int* n_elements_archive)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @InsertAgentIntoArchive.\n");
        exit(-1);
    }

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @InsertAgentIntoArchive.\n");
        exit(-1);
    }

    if (!A)
    {
        fprintf(stderr, "\nArchive Search space not allocated @InsertAgentIntoArchive.\n");
        exit(-1);
    }

	if(*n_elements_archive < s->m)
	{
		DestroyAgent(&A->a[*n_elements_archive], _JADE_);
		A->a[*n_elements_archive] = CopyAgent(a, _JADE_, _NOTENSOR_);
		*n_elements_archive = *n_elements_archive + 1;
	}
	else
		SwapArchiveAgent(A, s, a);
}

/* It replaces an agent from a full archive list by a new add one 
Parameters:
A: search space containing archived individuals
s: search space
a: agent to be inserted in the list */
void SwapArchiveAgent(SearchSpace *A, SearchSpace *s, Agent* a)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @SwapArchiveAgent.\n");
        exit(-1);
    }

    if (!A)
    {
        fprintf(stderr, "\nArchive Search space not allocated @SwapArchiveAgent.\n");
        exit(-1);
    }

    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @SwapArchiveAgent.\n");
        exit(-1);
    }

	int index;

	index = (int)round(GenerateUniformRandomNumber(0, A->m - 1));
    DestroyAgent(&(A->a[index]), _JADE_);
	A->a[index] = CopyAgent(a, _JADE_, _NOTENSOR_);
}

/* Randomly choose r2 from current population P union Archive population A */
Agent * Getr2Agent(SearchSpace *s, SearchSpace *A, int i, int r1_index, int n_elements_archive) 
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @Getr2Agent.\n");
        exit(-1);
    }
	if(n_elements_archive > 0)
	{
		if(!A)
		{
		    fprintf(stderr, "\nArchive Search space not allocated @Getr2Agent.\n");
		    exit(-1);
		}
	}

	Agent *a = NULL;
	int r2 = 0, m;
	m = s->m + n_elements_archive - 1;


	if(s->m > 1)
	{
		r2 = i;
		do
		{
			r2 = (int)round(GenerateUniformRandomNumber(0.0, (double)m ));
		}while (r2 == i || r2 == r1_index);
	}

	if(r2 >= s->m)
	{
		r2 = r2 - s->m;
		a = CopyAgent(A->a[r2], _JADE_, _NOTENSOR_);
	}
	else
		a = CopyAgent(s->a[r2], _JADE_, _NOTENSOR_);
 	return a;
}

/* Randomly choose r1 from current population P */
Agent * Getr1Agent(SearchSpace *s, int i, int* r1_index) 
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @Getr1Agent.\n");
        exit(-1);
    }

	Agent *a = NULL;
	*r1_index = 0;	

	if (s->m > 1)
	{
		*r1_index = i;	
		while(*r1_index == i)
			*r1_index = (int)round(GenerateUniformRandomNumber(0, s->m-1));
	}
	a = CopyAgent(s->a[*r1_index], _JADE_, _NOTENSOR_);
    return a;
}

/* Randomly choose bestP as one of the 100 p% best vectors */
Agent * GetBestPAgent(SearchSpace *s) 
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @GetBestPAgent.\n");
        exit(-1);
    }
	Agent *a = NULL;
	SearchSpace *newS = CreateSearchSpace(s->m, s->n, _JADE_);
	int n_best_total, best_n, j, i;

	for (j=0;j<s->n;j++)
	{
		newS->LB[j] = s->LB[j];
		newS->UB[j] = s->UB[j];
	}
	InitializeSearchSpace(newS, _JADE_);
	CopySearchSpaceAgents(s, newS, _JADE_, _NOTENSOR_);
	qsort(newS->a, newS->m, sizeof(Agent **), SortAgent);
	
	n_best_total = floor(s->m * s->p_greediness );
    if (n_best_total >= s->m) n_best_total = s->m - 1;
    best_n = (int)round(GenerateUniformRandomNumber(0, n_best_total));
	a = CopyAgent(newS->a[best_n], _JADE_, _NOTENSOR_);
	DestroySearchSpace(&newS, _JADE_);
    return a;
}
