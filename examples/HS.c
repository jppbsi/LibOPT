#include "common.h"
#include "function.h"
#include "hs.h"

int main(){

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/hs_model.txt", _HS_); /* It reads the model file and creates a search space. We are going to use HS to solve our problem. */

    InitializeSearchSpace(s, _HS_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _HS_)) /* It checks wether the search space is valid or not */
        runHS(s, Rosenbrock); /* It minimizes function Rosenbrock */

    DestroySearchSpace(&s, _HS_); /* It deallocates the search space */

    return 0;
}
