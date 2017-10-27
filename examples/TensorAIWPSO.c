#include "common.h"
#include "function.h"
#include "pso.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/pso_model.txt", _PSO_); /* It reads the model file and creates a search space. We are going to use AIWPSO to solve our problem. */

    s->t_g = CreateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
    {
        s->a[i]->t = CreateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        s->a[i]->t_v = CreateTensor(s->n, _QUATERNION_);
        s->a[i]->t_xl = CreateTensor(s->n, _QUATERNION_);
    }

    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */

    if (CheckSearchSpace(s, _PSO_))               /* It checks whether the search space is valid or not */
        runTensorAIWPSO(s, _QUATERNION_, Sphere); /* It minimizes function Sphere */

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
    {
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        DestroyTensor(&s->a[i]->t_v, s->n);
        DestroyTensor(&s->a[i]->t_xl, s->n);
    }

    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */

    return 0;
}
