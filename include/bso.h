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


/* BSO implementation is based on the paper available at www.sciencedirect.com/science/article/pii/S2210650216301766 */

#ifndef BSO_H
#define BSO_H

#include "opt.h"

/* BSO-related functions */
void k_means(SearchSpace *s, int *best_ideas, int ***ideas_per_cluster); /* It clusters the agents and returns a pointer with the best agent's ID per cluster */
void runBSO(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Brain Storm Optimization for function minimization */
/*************************/

#endif
