#ifndef GP_H
#define GP_H

#include "opt.h"
#include "common.h"

#define TERMINAL 0
#define FUNCTION 1
#define CONSTANT 2

/* Tree-related functions */
//Node *CreateNode(char *value, int terminal_id, char flag, char is_const, int const_id); /* It creates a node */
Node *GROW(SearchSpace *s, int dmin, int dmax); /* It creates a random tree based on the GROW algorithm */
/**************************/

#endif