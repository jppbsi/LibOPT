/* MBO implementation is based on the paper available at https://www.researchgate.net/publication/247931540_Migrating_Birds_Optimization_A_New_Metaheuristic_Approach_and_Its_Application_to_the_Quadratic_Assignment_Problem */

#ifndef MBO_H
#define MBO_H

#include "opt.h"

/* MBO-related functions */
void UpdateNeighbours(SearchSpace *s, int b, int k, prtFun Evaluate, va_list arg); /* It updates the neighbours of a single bird */
void ShareNeighbours(SearchSpace *s); /* It shares the neighbours to the following bird */
void ImproveBirds(SearchSpace *s); /* It tries to replace each bird for its best neighbour */
void runMBO(SearchSpace *s, prtFun EvaluateFun, ...); /* It executes the Migrating Birds Optimization for function minimization */
/*************************/

#endif