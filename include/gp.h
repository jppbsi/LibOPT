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

#ifndef GP_H
#define GP_H

#include "opt.h"

/* In GP structure, we have the agents and the nodes. The agents are used according to the other
techniques either, but the nodes are employed to build the tree-like representation. */

void runBGSGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Binary Geometric Semantic Genetic Programming for function minimization */
void runGSGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the standard (real-valued) Geometric Semantic Genetic Programming for function minimization */
void runGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Genetic Programming for function minimization */
void runTGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Tensor-based Genetic Programming for function minimization */

#endif