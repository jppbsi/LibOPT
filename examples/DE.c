#include "common.h"
#include "function.h"
#include "de.h"

int main() {
    SearchSpace *s = NULL;

    /* It reads the model file and creates a search space. We are going to use LOA to solve our problem. */
    s = ReadSearchSpaceFromFile("examples/model_files/de_model.txt", _DE_);

    InitializeSearchSpace(s, _DE_);   /* It initializes the search space */

    if (CheckSearchSpace(s, _DE_))    /* It checks whether the search space is valid or not */
        runDE(s, Sphere);             /* It minimizes function Sphere */

    DestroySearchSpace(&s, _DE_);     /* It de-allocates the search space */

    return 0;
}
