#include "common.h"
#include "function.h"
#include "loa.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/loa_model.txt", _LOA_); /* It reads the model file and creates a search space. We are going to use LOA to solve our problem. */
    InitializeSearchSpace(s, _LOA_);                                          /* It initalizes the search space */

    if (CheckSearchSpace(s, _LOA_)) /* It checks wether the search space is valid or not */
        runLOA(s, Sphere);          /* It minimizes function Sphere */

    DestroySearchSpace(&s, _LOA_); /* It deallocates the search space */

    return 0;
}
