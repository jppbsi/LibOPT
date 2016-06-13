/* FPA implementation is based on the paper available at https://arxiv.org/pdf/1312.5673.pdf */

#ifndef FPA_H
#define FPA_H

#include "opt.h"
#include "common.h"

void runFPA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Flower Pollination Algorithm for function minimization */

#endif