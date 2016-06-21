#include "common.h"
#include "function.h"
#include "fa.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/fa_model.txt", _FA_); /* It reads the model file and creates a search space. We are going to use FA to solve our problem. */
    
    InitializeSearchSpace(s, _FA_); /* It initalizes the search space */
            
    if (CheckSearchSpace(s, _FA_)) /* It checks wether the search space is valid or not */
        runFA(s, Levy); /* It minimizes function Levy */
    
    DestroySearchSpace(&s, _FA_); /* It deallocates the search space */
        
    return 0;
}
