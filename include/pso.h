#ifndef PSO_H
#define PSO_H

#include "common.h"

/* PSO-related functions */
void UpdateParticleVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (particle) */
void UpdateParticlePosition(SearchSpace *S, int i); /* It updates the position of an agent (particle) */
void EvaluateSwarm(SearchSpace *s, prtFun Evaluate, va_list arg); /* It evaluates the entire search space */
void runPSO(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Particle Swarm Optimization for function minimization */
/*************************/

/* AIWPSO-related functions */
void runAIWPSO(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Particle Swarm Optimization with Adpative Inertia Weight for function minimization */
double ComputeSuccess(SearchSpace *s); /* It computes the pecentage of success concerning the whole search space */
/****************************/

#endif