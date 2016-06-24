/* FA implementation is based on the paper available at https://arxiv.org/pdf/1308.3898.pdf */

#ifndef FA_H
#define FA_H

#include "opt.h"

void runFA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Firefly Algorithm for function minimization */

#endif