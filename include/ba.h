#ifndef BA_H
#define BA_H

#include "opt.h"
#include "common.h"

void UpdateBatVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (bat) */
void SetBatFrequency(SearchSpace *s, int i); /* It sets the frequency of an agent (bat) */
void runBA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Bat Algorithm for function minimization */

#endif