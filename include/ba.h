#ifndef BA_H
#define BA_H

#include "opt.h"
#include "common.h"

void UpdateBatVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (bat) */
void SetBatFrequency(SearchSpace *s, int i); /* It sets the frequency of an agent (bat) */
void EvaluateBats(SearchSpace *s, prtFun Evaluate, va_list arg); /* It evaluates the entire search space */
Agent *GenerateNewBatNearBest(SearchSpace *s); /* It generates an agent (bat) near the best one */
void runBA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Bat Algorithm for function minimization */

#endif