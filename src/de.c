#include "de.h"
#include "function.h"

void MutationAndRecombination(SearchSpace *searchSpace, int target, prtFun function, ...) {
    va_list args;
    Agent *mutant;
    int a, b, c, k;

    va_start(args, function);

    mutant = GenerateNewAgent(searchSpace, _DE_);
    a = b = c = target;

    while (a == target) a = GenerateUniformRandomNumber(0, 1) * searchSpace->m;
    while (b == target || b == a) b = GenerateUniformRandomNumber(0, 1) * searchSpace->m;
    while (c == target || c == b || c == a) c = GenerateUniformRandomNumber(0, 1) * searchSpace->m;

    for (k = 0; k < searchSpace->n; k++) {
        mutant->x[k] = GenerateUniformRandomNumber(0, 1) < searchSpace->cross_probability
                       ? searchSpace->a[target]->x[k]
                       : searchSpace->a[a]->x[k]
                         + searchSpace->mutation_factor
                           * (searchSpace->a[b]->x[k] - searchSpace->a[c]->x[k]);
    }

    mutant->fit = function(mutant, args);

    if(mutant->fit < searchSpace->a[target]->fit) {
        DestroyAgent(&searchSpace->a[target], _DE_);
        searchSpace->a[target] = CopyAgent(mutant, _DE_, _NOTENSOR_);
    }

    DestroyAgent(&mutant, _DE_);
}

/**
 * It executes the Differential Evolution for function minimization
 * @param searchSpace Search space
 * @param prtFunction Pointer to the function used to evaluate particles
 * @param ... List of additional arguments
 */
void runDE(SearchSpace *searchSpace, prtFun function, ...) {
    int t, k;
    va_list args, initialArgs;

    va_start(args, function);
    va_copy(initialArgs, args);

    if (!searchSpace) {
        fprintf(stderr, "\nSearch space not allocated @runDE.\n");
        exit(-1);
    }

    EvaluateSearchSpace(searchSpace, _DE_, function, args); /* Initial evaluation */

    for (t = 1; t <= searchSpace->iterations; t++) {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, searchSpace->iterations);
        va_copy(initialArgs, args);

        /* For each particle */
        for (k = 0; k < searchSpace->m; k++) {
            MutationAndRecombination(searchSpace, k, function, args);

            EvaluateSearchSpace(searchSpace, _DE_, function, args);
        }

        fprintf(stderr, "OK (minimum fitness value %lf)", searchSpace->gfit);
    }

    va_end(args);
}

