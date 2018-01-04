/*Copyright 2018 LibOpt Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

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
void UpdateIndividualTensorHMCR_PAR(SearchSpace *s, int tensor_id, char ***rehearsal, double **HMCR, double **PAR); /* It updates the individual values of HMCR and PAR concerning Tensor-based PSF-HS */
Agent *GenerateNewPSF(SearchSpace *s, double *HMCR, double *PAR, char *op_type); /* It generates a new PSF agent */
double **GenerateNewPSFTensor(SearchSpace *s, int tensor_id, double **HMCR, double **PAR, char **op_type); /* It generates a new PSF tensor */
void runPSF_HS(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Parameter-setting-free Harmony Search for function minimization */
void runTensorHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Harmony Search for function minimization */
void runTensorIHS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Tensor-based Improved Harmony Search for function minimization */
void runTensorPSF_HS(SearchSpace *s, int tensor_id, prtFun Evaluate, ...); /* It executes the Parameter-setting-free Tensor-based Improved Harmony Search for function minimization */
#endif
