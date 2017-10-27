#include "common.h"
#include "function.h"
#include "hs.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/hs_model.txt", _HS_); /* It reads the model file and creates a search space. We are going to use HS to solve our problem. */

    s->t_g = AllocateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */

    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initializes the search space with tensors */

    if (CheckSearchSpace(s, _HS_))                /* It checks whether the search space is valid or not */
        runTensorHS(s, _QUATERNION_, Rosenbrock); /* It minimizes function Rosenbrock */

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */

    DestroySearchSpace(&s, _HS_); /* It deallocates the search space */

    return 0;
}
