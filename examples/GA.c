#include "common.h"
#include "function.h"
#include "ga.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/ga_model.txt", _GA_); /* It reads the model file and creates a search space. We are going to use FA to solve our problem. */

    InitializeSearchSpace(s, _GA_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _GA_)) /* It checks wether the search space is valid or not */
        runGA(s, Brown);           /* It minimizes function Levy */

    DestroySearchSpace(&s, _GA_); /* It deallocates the search space */

    return 0;
}
