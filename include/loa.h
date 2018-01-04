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

/* LOA implementation is based on the paper available at https://www.researchgate.net/publication/278795643_Lion_Optimization_Algorithm_LOA_A_Nature-Inspired_Metaheuristic_Algorithm */

#ifndef LOA_H
#define LOA_H

#include "opt.h"

/* LOA-related functions */
void Hunting(SearchSpace *s, int pride, int *selected_females, prtFun Evaluate, va_list arg); /* In each pride, some females look for a prey (hunt). */
void MovingSafePlace(SearchSpace *s, int pride, int *selected_females, prtFun Evaluate, va_list arg); /* In each pride, remained females go toward a safe place */
void Roaming(SearchSpace *s, int pride, prtFun Evaluate, va_list arg); /* In each pride, male lions roams in that pride's territory(best position of each lion in the pride). */
void NomadMovingRandom(SearchSpace *s, int extra_male_nomads, prtFun Evaluate, va_list arg); /* Nomad lions (female and male) move randomly in search space. */
void Mating(SearchSpace *s, int pride, int *n_offsprings, prtFun Evaluate, va_list arg); /* In every pride, a female mate with one or several resident males with a determined probability, producing 2 offsprings(a male and a female). */
void NomadMating(SearchSpace *s, int *n_offsprings, int extra_male_nomads, prtFun Evaluate, va_list arg); /*  A nomad female mate with one nomad male with a determined probability, producing 2 offsprings(a male and a female). */
void Defense(SearchSpace *s, int pride, int n_male_offsprings, int extra_male_nomads); /* In each pride, male lions become mature and fight with other males in their pride. Beaten males abandon their pride and become a nomad. */
void AtackPride(SearchSpace *s, int n_nomad_male_offspring, int extra_male_nomads); /* Every nomad lion try to atack some prides, if the nomad is stronger (best fitness) than lion from the pride, they swap its positions. */
void Migration(SearchSpace *s, int *n_offsprings, int n_nomad_female_offspring, int *extra_nomads, int *n_migrating); /* some randomly selected females will migrate and will become nomads. */
void runLOA (SearchSpace *s,  prtFun Evaluate, ...);  /* It executes the Lion Optimization Algorithm for function minimization */
/*************************/

#endif
