/* BA implementation is based on the paper available at https://arxiv.org/ftp/arxiv/papers/1211/1211.6663.pdf */

#ifndef BA_H
#define BA_H

#include "opt.h"

/* BA related functions */
void UpdateBatVelocity(SearchSpace *s, int i); /* It updates the velocity of an agent (bat) */
void SetBatFrequency(SearchSpace *s, int i); /* It sets the frequency of an agent (bat) */
void runBA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Bat Algorithm for function minimization */
/*************************/

/* TensorBA related functions */
void UpdateTensorBatVelocity(SearchSpace *s, int i, int tensor_id); /* It updates the velocity of an tensor (bat) */
void runTensorBA(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Bat Algorithm for function minimization */
/*************************/

#endif