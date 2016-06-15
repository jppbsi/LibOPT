#include "opt.h"
#include "common.h"
#include "function.h"

int main(){
    SearchSpace *s = NULL;
    
    s = CreateSearchSpace(10,2, _GP_);
    DestroySearchSpace(&s, _GP_);
    
    return 0;
}

