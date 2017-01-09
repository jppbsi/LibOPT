#ifndef GP_H
#define GP_H

#include "opt.h"

/* In GP structure, we have the agents and the nodes. The agents are used according to the other
techniques either, but the nodes are employed to build the tree-like representation. */

void runBGSGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Binary Geometric Semantic Genetic Programming for function minimization */
void runGSGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the standard (real-valued) Geometric Semantic Genetic Programming for function minimization */
void runGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Genetic Programming for function minimization */

#endif