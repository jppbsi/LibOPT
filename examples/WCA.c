#include "common.h"
#include "function.h"
#include "wca.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/wca_model.txt", _WCA_); /* It reads the model file and creates a search space. We are going to use WCA to solve our problem. */

    InitializeSearchSpace(s, _WCA_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _WCA_)) /* It checks wether the search space is valid or not */
        runWCA(s, Rosenbrock);      /* It minimizes function Rosenbrock */

    DestroySearchSpace(&s, _WCA_); /* It deallocates the search space */

    return 0;
}
