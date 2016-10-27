/* FPA implementation is based on the paper available at https://arxiv.org/pdf/1312.5673.pdf */

#ifndef FPA_H
#define FPA_H

#include "opt.h"

void runFPA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Flower Pollination Algorithm for function minimization */
void runTensorFPA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Flower Pollination Algorithm for function minimization */

#endif