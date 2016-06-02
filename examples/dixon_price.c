#include "opt.h"
#include "common.h"
#include "function.h"
#include "pso.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/pso_model.txt", _PSO_); /* It reads a model file and creates a search space considering all the inputed parameters. */    
    InitializeSearchSpace(s); /* It initalizes the search space */
    
    runPSO(s, Dixon_Price); /* It minimizes the Dixon's-Price function */
        
    DestroySearchSpace(&s, _PSO_); /* It deallocates the search space */
    
    return 0;
}
