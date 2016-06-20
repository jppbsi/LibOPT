#include "common.h"
#include "function.h"
#include "bha.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/bha_model.txt", _BHA_); /* It reads the model file and creates a search space. We are going to use BHA to solve our problem. */
    
    InitializeSearchSpace(s, _BHA_); /* It initalizes the search space */
    
    runBHA(s, Rosenbrock); /* It minimizes function Rosenbrock */
    
    DestroySearchSpace(&s, _BHA_); /* It deallocates the search space */
        
    return 0;
}
