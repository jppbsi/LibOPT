#include "common.h"
#include "function.h"
#include "gp.h"

int main(int argc, char **argv){

    if(argc != 2){
        fprintf(stderr,"\nusage TensorGP <model_file>\n");
        exit(-1);
    }
    
    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile(argv[1], _TGP_); /* It reads the model file and creates a search space. We are going to use Quaternion-based GP to solve our problem. */
    InitializeSearchSpace(s, _TGP_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _TGP_)) /* It checks whether the search space is valid or not */
    fprintf(stderr,"\nTeste.");
        runTGP(s, Sphere); /* It minimizes function Sphere */

    /*DeallocateTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
    {
        DeallocateTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
     /*   DeallocateTensor(&s->a[i]->t_v, s->n);
        DeallocateTensor(&s->a[i]->t_xl, s->n);
    }*/

    DestroySearchSpace(&s, _TGP_); /* It deallocates the search space */

    return 0;
}