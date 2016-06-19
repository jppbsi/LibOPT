#include "common.h"
#include "function.h"
#include "cs.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/cs_model.txt", _CS_); /* It reads the model file and creates a search space. We are going to use CS to solve our problem. */
    
    InitializeSearchSpace(s, _CS_); /* It initalizes the search space */
            
    runCS(s, Rosenbrock); /* It minimizes function Rosenbrock */
    
    DestroySearchSpace(&s, _CS_); /* It deallocates the search space */
        
    return 0;
}
