#include "common.h"
#include "function.h"
#include "abc.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/abc_model.txt", _ABC_); /* It reads the model file and creates a search space. We are going to use ABC to solve our problem. */

    s->t_g = CreateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
        s->a[i]->t = CreateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */

    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */

    if (CheckSearchSpace(s, _ABC_))            /* It checks wether the search space is valid or not */
        runTensorABC(s, _QUATERNION_, Sphere); /* It minimizes function Sphere */

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */

    DestroySearchSpace(&s, _ABC_); /* It deallocates the search space */

    return 0;
}
