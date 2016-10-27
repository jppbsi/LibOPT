#include "common.h"
#include "function.h"
#include "pso.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/pso_model.txt", _PSO_); /* It reads the model file and creates a search space. We are going to use PSO to solve our problem. */
    
    s->t_g = AllocateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++){
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        s->a[i]->t_v = AllocateTensor(s->n, _QUATERNION_);
        s->a[i]->t_xl = AllocateTensor(s->n, _QUATERNION_);
    }
    
    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */
        
    //ShowSearchSpace(s, _PSO_); /* It shows the regular search space, with the tensors being mapped with their span function */
    
    if (CheckSearchSpace(s, _PSO_)) /* It checks wether the search space is valid or not */
        runTensorPSO(s, _QUATERNION_, Sphere); /* It minimizes function Sphere */
    
    DeallocateTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++){
        DeallocateTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        DeallocateTensor(&s->a[i]->t_v, s->n);
        DeallocateTensor(&s->a[i]->t_xl, s->n);
    }
        
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
        
    return 0;
}