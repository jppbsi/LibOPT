/* HS implementation is based on the paper available at http://journals.sagepub.com/doi/pdf/10.1177/003754970107600201 */

#ifndef HS_H
#define HS_H

#include "opt.h"

void runHS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Harmony Search for function minimization */
void runTensorHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Harmony Search for function minimization */

#endif
