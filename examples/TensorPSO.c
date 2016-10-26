#include "common.h"
#include "function.h"
#include "pso.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/pso_model.txt", _PSO_); /* It reads the model file and creates a search space. We are going to use PSO to solve our problem. */
    
    for (i = 0; i < s->m; i++)
        s->a[i]->t = AllocateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
    
    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */
    
    ShowTensorSearchSpace(s, _QUATERNION_); /* It shows a search space with tensors */
    
    ShowSearchSpace(s, _PSO_); /* It shows the regular search space, with the tensors being mapped with their norm function */
    
    for (i = 0; i < s->m; i++)
        DeallocateTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
        
    return 0;
}
