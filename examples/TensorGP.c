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

    fprintf(stderr,"\nReading search space ... ");
    s = ReadSearchSpaceFromFile(argv[1], _TGP_); /* It reads the model file and creates a search space. We are going to use Quaternion-based GP to solve our problem. */
    fprintf(stderr,"\nOK");
    
    fprintf(stderr,"\nInitializing search space ... ");
    InitializeSearchSpace(s, _TGP_); /* It initalizes the search space */
    fprintf(stderr,"\nOK");

    if (CheckSearchSpace(s, _TGP_)) /* It checks whether the search space is valid or not */
    fprintf(stderr,"\nTeste.");
        runTGP(s, Sphere); /* It minimizes function Sphere */

    DestroySearchSpace(&s, _TGP_); /* It deallocates the search space */

    return 0;
}