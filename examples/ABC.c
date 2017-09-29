#include "common.h"
#include "function.h"
#include "abc.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/abc_model.txt", _ABC_); /* It reads the model file and creates a search space. We are going to use ABC to solve our problem. */

    InitializeSearchSpace(s, _ABC_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _ABC_)) /* It checks wether the search space is valid or not */
        runABC(s, Sphere);          /* It minimizes function Sphere */

    DestroySearchSpace(&s, _ABC_); /* It deallocates the search space */

    return 0;
}
