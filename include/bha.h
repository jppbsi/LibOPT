/* BHA implementation is based on the paper available at http://www.sciencedirect.com/science/article/pii/S0020025512005762 */

#ifndef BHA_H
#define BHA_H

#include "opt.h"

void runBHA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Black Hole Algorithm for function minimization */

#endif
