/* CS implementation is based on the paper available at https://arxiv.org/pdf/1003.1594.pdf */

#ifndef CS_H
#define CS_H

#include "opt.h"

int NestLossParameter(int size, float probability); /* It computes the number of nests that will be replaced, taking into account a probability [0,1] */
void runCS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Cuckoo Search for function minimization */
void runTensorCS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Cuckoo Search for function minimization */

#endif
