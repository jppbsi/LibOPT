/* DE implementation is based on the paper available at http://jaguar.biologie.hu-berlin.de/~wolfram/pages/seminar_theoretische_biologie_2007/literatur/schaber/Storn1997JGlobOpt11.pdf
as well as wikipedia page at https://en.wikipedia.org/wiki/Differential_evolution#cite_note-storn97differential-2 */

#ifndef DE_H
#define DE_H

#include "opt.h"

/* DE-related functions */
void runDE(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Differential evolution for function minimization */

#endif
