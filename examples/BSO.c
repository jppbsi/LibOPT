#include "common.h"
#include "function.h"
#include "bso.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/bso_model.txt", _BSO_); /* It reads the model file and creates a search space. We are going to use PSO to solve our problem. */
    
    InitializeSearchSpace(s, _BSO_); /* It initalizes the search space */
    
    if (CheckSearchSpace(s, _BSO_)) /* It checks wether the search space is valid or not */
        runBSO(s, Sphere); /* It minimizes function Sphere */
    
    DestroySearchSpace(&s, _BSO_); /* It deallocates the search space */
        
    return 0;
}
