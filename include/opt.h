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
#define _GP_ 5 /* Genetic Programming */
#define _GA_ 6 /* Genetic Algorithm */
/**************************/

/* GP type nodes */
#define TERMINAL 0
#define FUNCTION 1
#define CONSTANT 2
#define TERMINAL_LENGTH 16
/*****************/

#define N_CONSTANTS 1000 /* number of constants generated at random to populate a GP agent */
#define PROB_MUTATION_FUNCTION 0.9 /* probability of mutation on a function node */

/* GP function-type nodes */
#define _SUM_ 0
#define _SUB_ 1
#define _MUL_ 2
#define _DIV_ 3
#define _EXP_ 4
#define _SQRT_ 5
#define _LOG_ 6
#define _ABS_ 7
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
    
#endif
