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

/* PSO implementation is based on the paper available at http://www.cs.tufts.edu/comp/150GA/homeworks/hw3/_reading6%201995%20particle%20swarming.pdf
AIWPSO implementation is based on the paper available at http://ceit.aut.ac.ir/~ebadzadeh/PSO.htm */

#ifndef PSO_H
#define PSO_H

#include "opt.h"

/* PSO-related functions */
void UpdateParticleVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (particle) */
void UpdateParticlePosition(SearchSpace *s, int i); /* It updates the position of an agent (particle) */
void runPSO(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Particle Swarm Optimization for function minimization */
/*************************/

/* AIWPSO-related functions */
void runAIWPSO(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Particle Swarm Optimization with Adaptive Inertia Weight for function minimization */
double ComputeSuccess(SearchSpace *s); /* It computes the pecentage of success concerning the whole search space */
/****************************/

/* TensorPSO-related functions */
void UpdateTensorParticleVelocity(SearchSpace *s, int i, int tensor_id); /* It updates the velocity of an tensor (particle) */
void UpdateTensorParticlePosition(SearchSpace *s, int i, int tensor_id); /* It updates the position of an tensor (particle) */
void runTensorPSO(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Particle Swarm Optimization for function minimization */
void runTensorAIWPSO(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Particle Swarm Optimization with Adaptive Inertia Weight for function minimization */
/*************************/

#endif
