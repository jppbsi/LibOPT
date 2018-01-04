/*Copyright 2018 LibOpt Authors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "common.h"
#include "function.h"
#include "ga.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/ga_model.txt", _GA_); /* It reads the model file and creates a search space. We are going to use FA to solve our problem. */

    InitializeSearchSpace(s, _GA_); /* It initalizes the search space */

    if (CheckSearchSpace(s, _GA_)) /* It checks wether the search space is valid or not */
        runGA(s, Brown);           /* It minimizes function Levy */

    DestroySearchSpace(&s, _GA_); /* It deallocates the search space */

    return 0;
}
