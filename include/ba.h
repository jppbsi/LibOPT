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

/* BA implementation is based on the paper available at https://arxiv.org/ftp/arxiv/papers/1211/1211.6663.pdf */

#ifndef BA_H
#define BA_H

#include "opt.h"

/* BA related functions */
void UpdateBatVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (bat) */
void SetBatFrequency(SearchSpace *s, int i); /* It sets the frequency of an agent (bat) */
void runBA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Bat Algorithm for function minimization */
/*************************/

/* TensorBA related functions */
void UpdateTensorBatVelocity(SearchSpace *s, int i, int tensor_id); /* It updates the velocity of an tensor (bat) */
void SetTensorBatFrequency(SearchSpace *s, int i); /* It sets the frequency of an tensor (bat) */
double **GenerateNewBatTensor(SearchSpace *s, int tensor_id); /* It generates a new tensor for BA algorithm */
void runTensorBA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Bat Algorithm for function minimization */
/*************************/

#endif