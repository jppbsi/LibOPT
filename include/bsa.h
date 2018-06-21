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

/* Backtracking Search Optimization Algorithm implementation is based on the paper available at https://www.sciencedirect.com/science/article/abs/pii/S0096300313001380 */

#ifndef BSA_H
#define BSA_H

#include "opt.h"

void runBSA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Harmony Search for function minimization */
void InitializeMutation(SearchSpace *s, SearchSpace *OldS, double** Mutation);  /* It initializes the mutation matrix */
SearchSpace *CrossOverStrategyOfBSA(SearchSpace *s, double** Map, double** Mutation); /* It executes the the BSA cross over strategy */
void BoundaryControlMechanism(SearchSpace *s,SearchSpace *T);  /* It controls the boundaries of the new Trial-population */
void InitializeMap(SearchSpace *s,  double** Map);  /* It initializes the map containing the position of features to be permuted */


/*  Tensor-Based Functions */
void runTensorBSA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the tensor-based Backtracking Search Optimization Algorithm for function minimization */
SearchSpace *CrossOverTensorStrategyOfBSA(SearchSpace *s, double** Map, double*** Mutation, int tensor_id); /* It executes the the tensor-based BSA cross over strategy */
void InitializeTensorMutation(SearchSpace *s, SearchSpace *oldS, double*** Mutation, int tensor_id); /* It initializes the tensor-based mutation matrix */


#endif
