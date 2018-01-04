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

/* CS implementation is based on the paper available at https://arxiv.org/pdf/1003.1594.pdf */

#ifndef CS_H
#define CS_H

#include "opt.h"

int NestLossParameter(int size, float probability); /* It computes the number of nests that will be replaced, taking into account a probability [0,1] */
void runCS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Cuckoo Search for function minimization */
void runTensorCS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Cuckoo Search for function minimization */

#endif
