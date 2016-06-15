#include "opt.h"
#include "common.h"
#include "function.h"

int main(){
    SearchSpace *s = NULL;
    
    int min_depth = 1, max_depth = 1, n_terminals = 2, i;
    int m = 10, n = 2;
    
    char **terminal = (char **)malloc(n_terminals*sizeof(char *));
    for(i = 0; i < n_terminals; i++)
        terminal[i] = (char *)malloc(TERMINAL_LENGHT*sizeof(char));
    
    strcpy(terminal[0], "x");
    strcpy(terminal[1], "y");
        
    /* It creates a GP seach space with 10 agents (trees), 2 dimensions,
    trees with minimum depth of min_depth and maximum depth of max_depth, and 2 terminals (x and y) */
    s = CreateSearchSpace(m, n, _GP_, min_depth, max_depth, n_terminals, terminal);
    
    DestroySearchSpace(&s, _GP_);
    
    return 0;
}

