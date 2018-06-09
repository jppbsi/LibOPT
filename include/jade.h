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

/* JADE implementation is based on the paper available at https://ieeexplore.ieee.org/abstract/document/5208221/?reload=true */

#ifndef JADE_H
#define JADE_H

#include "opt.h"


void runJADE(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Adaptive Differential Evolution with Optional External Archive for function minimization */

/* Lists related functions */
double LehmerMeanList(double* list, int nElements); /* It calculates the Lehmer mean of a given list of doubles */
double ArithmeticMeanList(double* list, int nElements);  /* It calculates the Arithmetic mean of a given list of doubles */
double* AddList( double *list, double value, int nElements); /* Insert a double into a predefined list of doubles */

/* Functions related to the evolutive process */
double* MutationJade(int i, SearchSpace *s, SearchSpace *A, double Fi, int n_elements_archive); /* It generates a mutate vector */
void CrossoverJade(SearchSpace* s, SearchSpace* crossover, int i, double* mutation, double CRi); /* It executes the crossover operation */

/* Archive insert-related functions */
void InsertAgentIntoArchive(SearchSpace *A, SearchSpace *s, Agent *a, int* n_elements_archive); /* Insert an agent replaced in the current population into an archive list */
void SwapArchiveAgent(SearchSpace *A, SearchSpace *s, Agent* a); /* It replaces an agent from a full archive list by a new add one */

/* Agent selection for mutation functions */
Agent * Getr2Agent(SearchSpace *s, SearchSpace *A, int i, int r1_index, int n_elements_archive);  /* Randomly choose r2 from current population P union Archive population A */
Agent * Getr1Agent(SearchSpace *s, int i, int* r1_index); /* Randomly choose r1 from current population P */
Agent * GetBestPAgent(SearchSpace *s); /* Randomly choose bestP as one of the 100 p% best vectors */
#endif
