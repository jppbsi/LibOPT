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

/* Initial temperature of the system is a fine tuned parameter. At principle, the number of iterations for SA is not used (initial temperature takes care of this), but if you set the initial temperature as 0 (zero) or any value below zero, we will determine it automatically from the number of iterations. NOTE: Thats, currently is only compatible with the BOLTZMANN_ANNEALING cooling schedule. And is recomended that you you use 2 times the normal number of iterations since SA is a really simple and light weight algorithm. Eg. For a 20.000 iterations problem, is recomended for SA 40.0000 iterations */

#ifndef SA_H
#define SA_H

#include "opt.h"

/* It calculates the new temperature of the system according to the Boltzmann annealing */
double boltzmannAnnealing(double T0, double t);
/* It calculates the initial temperature of the system automatically, based on the max number of iterations and the end temperature */
double initTemp_boltzmannAnnealing(double t_end, double max_iter);

/* It calculates the new temperature of the system according to the Fast Schedule annealing */
double fastScheduleAnnealing(double T, double alpha);

void runSA(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Simulated Annealing for function minimization */

#endif
