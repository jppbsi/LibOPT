#include "common.h"
#include "function.h"
#include "ba.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/ba_model.txt", _BA_); /* It reads the model file and creates a search space. We are going to use BA to solve our problem. */
    
    InitializeSearchSpace(s, _BA_); /* It initalizes the search space */
    
    runBA(s, Levy); /* It minimizes function Levy */
    
    DestroySearchSpace(&s, _BA_); /* It deallocates the search space */
        
    return 0;
}
