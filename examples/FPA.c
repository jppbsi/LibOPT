#include "common.h"
#include "function.h"
#include "fpa.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/fpa_model.txt", _FPA_); /* It reads the model file and creates a search space. We are going to use FPA to solve our problem. */
    
    InitializeSearchSpace(s, _FPA_); /* It initalizes the search space */
    
    runFPA(s, Rosenbrock); /* It minimizes function Rosenbrock */
    
    DestroySearchSpace(&s, _FPA_); /* It deallocates the search space */
        
    return 0;
}
