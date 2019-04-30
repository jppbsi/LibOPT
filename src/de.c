#include "de.h"
#include "function.h"

void MutationAndRecombination(SearchSpace *searchSpace, int target, prtFun function, va_list arg) {
    Agent *mutant;
    int a, b, c, k;

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
    CheckAgentLimits(searchSpace, mutant);

    mutant->fit = function(mutant, arg);

    if(mutant->fit < searchSpace->a[target]->fit) {
        DestroyAgent(&searchSpace->a[target], _DE_);
        searchSpace->a[target] = CopyAgent(mutant, _DE_, _NOTENSOR_);
    }

    DestroyAgent(&mutant, _DE_);
}

/**
 * It executes the Differential Evolution for function minimization
 * @param s Search space
 * @param prtFunction Pointer to the function used to evaluate particles
 * @param ... List of additional arguments
 */
void runDE(SearchSpace *s, prtFun Evaluate, ...) {
    int t, k;
    va_list arg, argtmp;

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s) {
        fprintf(stderr, "\nSearch space not allocated @runDE.\n");
        exit(-1);
    }

    if (s->m<=3) {
        fprintf(stderr, "\nNumber of agents should be greater than 3 @runDE.\n");
        exit(-1);
    }

    EvaluateSearchSpace(s, _DE_, Evaluate, arg); /* Initial evaluation */

    for (t = 1; t <= s->iterations; t++) {
        fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);


        /* For each particle */
        for (k = 0; k < s->m; k++) {
			va_copy(arg, argtmp);
           	MutationAndRecombination(s, k, Evaluate, arg);
        }
		va_copy(arg, argtmp);
        EvaluateSearchSpace(s, _DE_, Evaluate, arg);

        fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
		fprintf(stdout, "\n%d %lf",t, s->gfit);
    }

    va_end(arg);
}
