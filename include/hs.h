/* HS implementation is based on the paper available at http://journals.sagepub.com/doi/pdf/10.1177/003754970107600201 */

#ifndef HS_H
#define HS_H

#include "opt.h"

#define PSF_RANDOM 0
#define PSF_MEMORY 1
#define PSF_PITCH 2

void runHS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Harmony Search for function minimization */
void runIHS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Improved Harmony Search for function minimization */
void UpdateIndividualHMCR_PAR(SearchSpace *s, char **rehearsal, double *HMCR, double *PAR); /* It updates the individual values of HMCR and PAR concerning PSF-HS */
Agent *GenerateNewPSF(SearchSpace *s, double *HMCR, double *PAR, char *op_type); /* It generates a new PSF agent */
void runPSF_HS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Parameter-setting-free Harmony Search for function minimization */
void runTensorHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Harmony Search for function minimization */
void runTensorIHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Improved Harmony Search for function minimization */
#endif
