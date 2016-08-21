#include "common.h"
#include "function.h"
#include "mbo.h"

int main(){
    
    SearchSpace *s = NULL;
    int i;
    
    s = ReadSearchSpaceFromFile("examples/model_files/mbo_model.txt", _MBO_); /* It reads the model file and creates a search space. We are going to use MBO to solve our problem. */
    InitializeSearchSpace(s, _MBO_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _MBO_)) /* It checks wether the search space is valid or not */
        runMBO(s, Sphere);  /* It minimizes function Sphere */
    
    DestroySearchSpace(&s, _MBO_); /* It deallocates the search space */
    return 0;
}