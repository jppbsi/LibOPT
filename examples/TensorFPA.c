#include "common.h"
#include "function.h"
#include "fpa.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/fpa_model.txt", _FPA_); /* It reads the model file and creates a search space. We are going to use FPA to solve our problem. */

    s->t_g = AllocateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
   
    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */
    
    if (CheckSearchSpace(s, _FPA_)) /* It checks whether the search space is valid or not */
        runTensorFPA(s, _QUATERNION_, Rosenbrock); /* It minimizes function Rosenbrock */
        
    DeallocateTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
        DeallocateTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
    
    DestroySearchSpace(&s, _FPA_); /* It deallocates the search space */
        
    return 0;
}
