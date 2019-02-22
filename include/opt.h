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
#ifndef _OPT_H_
#define _OPT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Meta-heuristics */
#define _PSO_ 1 /* Particle Swarm Optimization */
#define _BA_ 2 /* Bat Algorithm */
#define _FPA_ 3 /* Flower Pollination Algorithm */
#define _FA_ 4 /* Firefly Algorithm */
#define _CS_ 5 /* Cuckoo Search */
#define _GP_ 6 /* Genetic Programming */
#define _GA_ 7 /* Genetic Algorithm */
#define _BHA_ 8 /* Black Hole Algorithm */
#define _WCA_ 9 /* Water Cycle Algorithm */
#define _MBO_ 10 /* Migrating Bird Optimization */
#define _ABC_ 11 /* Artificial Bee Colony */
#define _HS_ 12 /* Harmony Search */
#define _BSO_ 13 /* Brain Storm Optimization */
#define _LOA_ 14 /* Lion Optimization Algorithm */
#define _DE_ 15 /* Differential Evolution */
#define _BSA_ 16 /* Backtracking Search Optimization Algorithm */
#define _JADE_ 17 /* Adaptive Differential Evolution with Optional External Archive */
#define _COBIDE_ 18 /* Differential evolution based on covariance matrix learning and bimodal distribution parameter */
#define _ABO_ 19 /* Artificial Butterfly Algorithm */
#define _SA_ 20 /* Simulated Annealing Optimization Algorithm */
/**************************/

/* Tensor-based Meta-heuristics */
#define _TGP_ 106 /* Tensor-based Genetic Programming */

/* Tensors */
#define _NOTENSOR_ -1 /* No tensor is used */
#define _QUATERNION_ 4 /* Quaternion Space */
#define _OCTONION_ 8 /* Octonion Space */
/**************************/

/* GP type nodes */
#define TERMINAL 0
#define FUNCTION 1
#define CONSTANT 2
#define NEW_TERMINAL 3
#define TERMINAL_LENGTH 16
/*****************/

/* GP variables */
#define N_CONSTANTS 1000 /* number of constants generated at random to populate a GP agent */
#define PROB_MUTATION_FUNCTION 0.9 /* probability of mutation on a function node */
#define PROB_CROSSOVER_FUNCTION 0.7 /* probability of crossover on a function node */

/* GP function-type nodes */
#define _SUM_ 0
#define _SUB_ 1
#define _MUL_ 2
#define _DIV_ 3
#define _EXP_ 4
#define _SQRT_ 5
#define _LOG_ 6
#define _ABS_ 7
#define _AND_ 8
#define _OR_ 9
#define _XOR_ 10
#define _NOT_ 11
#define _TSUM_ 12
#define _TSUB_ 13
#define _TMUL_ 14
#define _TDIV_ 15
/**************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>

#include "common.h"

#endif
