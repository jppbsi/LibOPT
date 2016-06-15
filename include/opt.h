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
/**************************/

/* GP type nodes */
#define TERMINAL 0
#define FUNCTION 1
#define CONSTANT 2
#define TERMINAL_LENGHT 16
/*****************/

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
