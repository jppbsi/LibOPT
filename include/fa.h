#ifndef FA_H
#define FA_H

#include "opt.h"
#include "common.h"

void UpdateFireflyPosition(SearchSpace *s, int firefly_id); /* It updates the position of an agent (firefly) */
void UpdateBestFireflyPosition(SearchSpace *s, int best_firefly_id); /* It updates the position of the best agent (firefly) */
void runFA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Firefly Algorithm for function minimization */

#endif