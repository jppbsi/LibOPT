/* BHA implementation is based on the paper available at http://www.sciencedirect.com/science/article/pii/S0020025512005762 */

#ifndef BHA_H
#define BHA_H

#include "opt.h"

void runBHA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Black Hole Algorithm for function minimization */
void runTensorBHA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Black Hole Algorithm for function minimization */

#endif
