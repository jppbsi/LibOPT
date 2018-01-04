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

#include "common.h"
#include "function.h"
#include "gp.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "\nusage GP <model_file>\n");
        exit(-1);
    }

    SearchSpace *s = NULL;

    int min_depth = 1, max_depth = 3, n_terminals = 2, i, j;
    int n_functions = 3, m = 10, n = 2;
    char **terminal = NULL, **function = NULL;
    double **constant = NULL;

    /* This toy example shows how to use GP using a model file and using features added in the source-code */
    fprintf(stderr, "\nToy example using built-in features ***\n");

    /* Built-in features ******************************************************/
    /* loading set of terminals */
    terminal = (char **)malloc(n_terminals * sizeof(char *));
    for (i = 0; i < n_terminals; i++)
        terminal[i] = (char *)malloc(TERMINAL_LENGTH * sizeof(char));
    strcpy(terminal[0], "(x,y)");
    strcpy(terminal[1], "CONST");
    /****************************/

    /* loading set of functions */
    function = (char **)malloc(n_functions * sizeof(char *));
    for (i = 0; i < n_functions; i++)
        function[i] = (char *)malloc(TERMINAL_LENGTH * sizeof(char));
    strcpy(function[0], "SUM");
    strcpy(function[1], "SUB");
    strcpy(function[2], "MUL");
    /****************************/

    /* loading constants */
    constant = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        constant[i] = (double *)malloc(N_CONSTANTS * sizeof(double));
        for (j = 0; j < N_CONSTANTS; j++)
            constant[i][j] = GenerateUniformRandomNumber(-5.0, 5.0);
    }
    /*********************/

    /* It creates a GP seach space with 10 agents (trees), 2 dimensions,
    trees with minimum depth of min_depth and maximum depth of max_depth, 2 functions (+ and -), 2 terminals (x,y and CONST) and 100 constants chosen
    at random within [0,10]*/
    s = CreateSearchSpace(m, n, _GP_, min_depth, max_depth, n_terminals, N_CONSTANTS, n_functions, terminal, constant, function);
    s->iterations = 10;
    s->is_integer_opt = 1; /* integer(binary)-valued optimization problem */

    /* Initializing lower and upper bounds */
    for (i = 0; i < s->n; i++)
    {
        s->LB[i] = -5.0;
        s->UB[i] = 5.0;
    }

    InitializeSearchSpace(s, _GP_); /* It initalizes the search space */

    s->pReproduction = 0.3;                                /* Setting up the probability of reproduction */
    s->pMutation = 0.4;                                    /* Setting up the probability of mutation */
    s->pCrossover = 1 - (s->pReproduction + s->pMutation); /* Setting up the probability of crossover */

    if (CheckSearchSpace(s, _GP_))
        runGP(s, Sphere); /* It minimizes function Sphere */
    else
        fprintf(stderr, "\nPlease, check your GP configuration prior running it.\n");

    PrintTree2File(s, s->T[s->best], "best_tree.txt"); /* It saves the best tree */

    DestroySearchSpace(&s, _GP_);
    /**************************************************************************/

    /* Using model file *******************************************************/
    fprintf(stderr, "\nToy example using model file ***\n");
    s = NULL;
    s = ReadSearchSpaceFromFile(argv[1], _GP_);
    InitializeSearchSpace(s, _GP_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _GP_))
        runGP(s, Sphere); /* It minimizes function Sphere */
    else
        fprintf(stderr, "\nPlease, check your GP configuration prior running it.\n");

    PrintTree2File(s, s->T[s->best], "best_tree.txt"); /* It saves the best tree */

    DestroySearchSpace(&s, _GP_);
    /**************************************************************************/

    return 0;
}
