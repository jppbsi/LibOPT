#include "common.h"
#include "function.h"
#include "ba.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/ba_model.txt", _BA_); /* It reads the model file and creates a search space. We are going to use BA to solve our problem. */

    s->t_g = AllocateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
    {
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        s->a[i]->t_v = AllocateTensor(s->n, _QUATERNION_);
    }

    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */

    if (CheckSearchSpace(s, _BA_))          /* It checks wether the search space is valid or not */
        runTensorBA(s, _QUATERNION_, Levy); /* It minimizes function Levy */

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
    {
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        DestroyTensor(&s->a[i]->t_v, s->n);
    }

    DestroySearchSpace(&s, _BA_); /* It deallocates the search space */

    return 0;
}
