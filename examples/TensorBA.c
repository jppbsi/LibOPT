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
#include "ba.h"

int main()
{

    SearchSpace *s = NULL;
    int i;

    s = ReadSearchSpaceFromFile("examples/model_files/ba_model.txt", _BA_); /* It reads the model file and creates a search space. We are going to use BA to solve our problem. */

    s->t_g = CreateTensor(s->n, _QUATERNION_);
    for (i = 0; i < s->m; i++)
    {
        s->a[i]->t = CreateTensor(s->n, _QUATERNION_); /* It allocates a new tensor for each agent */
        s->a[i]->t_v = CreateTensor(s->n, _QUATERNION_);
    }

    InitializeTensorSearchSpace(s, _QUATERNION_); /* It initalizes the search space with tensors */

    if (CheckSearchSpace(s, _BA_))          /* It checks wether the search space is valid or not */
        runTensorBA(s, _QUATERNION_, Levy); /* It minimizes function Levy */

    DestroyTensor(&s->t_g, s->n);
    for (i = 0; i < s->m; i++)
    {
        DestroyTensor(&s->a[i]->t, s->n); /* It deallocates the tensor for each agent */
        DestroyTensor(&s->a[i]->t_v, s->n);
    }

    DestroySearchSpace(&s, _BA_); /* It deallocates the search space */

    return 0;
}
