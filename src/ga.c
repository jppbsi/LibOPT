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


#include "ga.h"

/* It executes the Genetic Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate particles
arg: list of additional arguments */
void runGA(SearchSpace *s, prtFun Evaluate, ...)
{
	va_list arg, argtmp;
	int t, i, j, flower_j, flower_k;
	double prob, epsilon, *L = NULL, fitValue;
	Agent *tmp = NULL;

	va_start(arg, Evaluate);
	va_copy(argtmp, arg);

	if (!s)
	{
		fprintf(stderr, "\nSearch space not allocated @runGA.\n");
		exit(-1);
	}

	EvaluateSearchSpace(s, _GA_, Evaluate, arg); /* Initial evaluation of the search space */

	for (t = 1; t <= s->iterations; t++)
	{
		fprintf(stderr, "\nRunning iteration %d/%d ... ", t, s->iterations);

		va_copy(arg, argtmp);

		fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
	}

	va_end(arg);
}