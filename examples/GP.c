#include "common.h"
#include "function.h"

int main(){
    SearchSpace *s = NULL;
    
    int min_depth = 1, max_depth = 3, n_terminals = 3, i;
    int n_functions = 3, m = 10, n = 2;
    char **terminal = NULL, **function = NULL;
    double *constant = NULL;
    
    /* loading set of terminals */
    terminal = (char **)malloc(n_terminals*sizeof(char *));
    for(i = 0; i < n_terminals; i++)
        terminal[i] = (char *)malloc(TERMINAL_LENGTH*sizeof(char));
    strcpy(terminal[0], "x");
    strcpy(terminal[1], "y");
    strcpy(terminal[2], "CONST");
    /****************************/
    
    /* loading set of functions */
    function = (char **)malloc(n_functions*sizeof(char *));
    for(i = 0; i < n_functions; i++)
        function[i] = (char *)malloc(TERMINAL_LENGTH*sizeof(char));
    strcpy(function[0], "SUM");
    strcpy(function[1], "SUB");
    strcpy(function[2], "MUL");
    /****************************/
    
    /* loading constants */
    constant = (double *)malloc(N_CONSTANTS*sizeof(double));
    for(i = 0; i < N_CONSTANTS; i++)
        constant[i] = GenerateUniformRandomNumber(0,10);
    /*********************/
        
    /* It creates a GP seach space with 10 agents (trees), 2 dimensions,
    trees with minimum depth of min_depth and maximum depth of max_depth, 2 functions (+ and -), 2 terminals (x and y) and 100 constants chosen
    at random within [0,10]*/
    s = CreateSearchSpace(m, n, _GP_, min_depth, max_depth, n_terminals, N_CONSTANTS, n_functions, terminal, constant, function);
    
    //InitializeSearchSpace(s); /* It initalizes the search space */
    
    for(i = 0; i < s->m; i++)
        PrintTree2File(s, s->T[i], "trees.txt");
    
    DestroySearchSpace(&s, _GP_);
    
    return 0;
}

