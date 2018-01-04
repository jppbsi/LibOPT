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


/* ABC implementation is based on the paper available at http://files.matlabsite.com/docs/papers/sp/pso-paper-052.pdf */

#ifndef ABC_H
#define ABC_H

#include "opt.h"

void runABC(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Artificial Bee Colony for function minimization */
void runTensorABC(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Artificial Bee Colony for function minimization */

#endif
