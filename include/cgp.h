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

/* CGP implementation is based on the paper available at https://docs.wixstatic.com/ugd/5ef763_8cd1d7d566e84ac79a037cf4205ec527.pdf */

#ifndef CGP_H
#define CGP_H

#include "opt.h"
#include "function.h"

void runCGP(SearchSpace *s, prtFun Evaluate, ...); /* It executes the Cartesian Genetic Programming for function minimization */

double computeFunc(double x, double y, int op_id) ;

int get_node_column(int n_rows, int node_index);

int get_node_row(int n_rows, int node_col, int node_index);

int get_node_index(int n_rows, int node_col, int node_row);

int get_valid_index_for_output(int n_columns, int n_rows, int n_input_values);

int get_valid_input_index(int n_rows, int levels_back, int n_input_values, int node_index) ;

void decode_chromossome(Agent *a, int n_columns, int n_rows, int n_input_values, int n);

void point_mutation(Agent* a, int n_columns, int n_rows, int levels_back, int n_input_values, int n_functions);

#endif /* CGP_H */
