/* ABC implementation is based on the paper available at http://files.matlabsite.com/docs/papers/sp/pso-paper-052.pdf */

#ifndef ABC_H
#define ABC_H

#include "opt.h"

void runABC(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Artificial Bee Colony for function minimization */

#endif
