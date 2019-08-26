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

#include "cgp.h"

double computeFunc(double x, double y, int op_id) {
    switch (op_id) {
        case _SUM_:
            return x + y;
        case _SUB_:
            return x - y;
        case _MUL_:
            return x * y;
        case _DIV_:
            return x / (y + 0.00001); /* It avoids division by 0 */

        default:
            fprintf(stderr, "\nInvalid function id @computeFunc. %d\n", op_id);
            exit(1);
    }
}

int get_node_column(int n_rows, int node_index) {
    return (node_index / n_rows);
}

int get_node_row(int n_rows, int node_col, int node_index) {
    return node_index - (node_col * n_rows);
}

int get_node_index(int n_rows, int node_col, int node_row) {
    int a = ((node_col *  n_rows) + node_row);
    if(a < 0) {
        printf("n_rows %d, node_col %d, node_row %d\n", n_rows, node_col, node_row);
        exit(1);
    }
    return a;
}

int get_valid_index_for_output(int n_columns, int n_rows, int n_input_values) {
    /* checking if the output of the program will come from a coding node or an input node */
    double input_proba = (double)n_input_values / ((double)n_input_values + ((double)n_columns * (double)n_rows));

    /* the first half of the probability ruler is indicates the input values are coming from the input array */
    /* originally (according to the paper) this is a 50-50 chance (so using the calculated probability input_proba), but in this implementation we choose to block the possibility of the output gene come from an input node for better results and fast convergence. */
    if(GenerateUniformRandomNumber(0, 1) < 0) {
        return (int)GenerateUniformRandomNumber(0, n_input_values);
    }
    /* the program's output is coming from a coding node */
    else {
        return (int)GenerateUniformRandomNumber(0, n_columns * n_rows) + n_input_values;
    }
}

/* generating a valid node index based on the current node location - this index is the index of the node if */
/* generting a valid index to be used as the input index of a node (this value is index of a node output's) */
int get_valid_input_index(int n_rows, int levels_back, int n_input_values, int node_index) {
    int node_col = get_node_column(n_rows, node_index);
    int node_row = get_node_row(n_rows, node_col, node_index);

    /* if we are in the first column, the only input options are from the input array */
    if(node_col == 0) {
        return (int)GenerateUniformRandomNumber(0, n_input_values);
    }

    /* getting the lower bound of the column number */
    int min_col_val = node_col - levels_back;

    /* the current node could receive its input either from the input array (random values) or from other node */
    if(min_col_val < 0) {
        /* we calculate the probability of the input value come from the input array or from other nodes (keeping the same probability for each type of input taking the numbers of each into consideration) */
        /* where (double)node_col * (double)n_rows) represent the total number of coding genes outputs avaliable for the current node */
        double input_proba = n_input_values / ((double)n_input_values + ((double)node_col * (double)n_rows));
        /* the first half of the probability ruler is indicates the input values are coming from the input array */
        if(GenerateUniformRandomNumber(0, 1) < input_proba) {
            return (int)GenerateUniformRandomNumber(0, n_input_values);
        }
        /* the input value is coming from other coding gene */
        else {
            int new_node_col = (int)GenerateUniformRandomNumber(0, node_col);
            int new_node_row = (int)GenerateUniformRandomNumber(0, n_rows);

            /* adding s->n_input_values to the index because the indexes of the coding genes output start at s->n_input_values, as the first output indexes are from the n_input_values array (random values) */
            return get_node_index(n_rows, new_node_col, new_node_row) + n_input_values;
        }
    }
    /* it's impossible for that node to receive its input from the input array (random values), only from other nodes */
    else {
        int new_node_col = (int)GenerateUniformRandomNumber(min_col_val, node_col);
        int new_node_row = (int)GenerateUniformRandomNumber(0, n_rows);

        /* adding s->n_input_values to the index because the indexes of the coding genes output start at s->n_input_values, as the first output indexes are from the n_input_values array (random values) */
        return get_node_index(n_rows, new_node_col, new_node_row) + n_input_values;
    }
}

void decode_chromossome(Agent *a, int n_columns, int n_rows, int n_input_values, int n) {
    /* array that holds the output of all nodes, including the input nodes */
    double output_nodes_values[n_columns * n_rows + n_input_values];
    /* copying the input nodes to the value output array */
    for(int i = 0; i < n_input_values; i++)
        output_nodes_values[i] = a->input_values[i];

    /* binary array indicating which nodes must be evaluated */
    int to_evaluate[n_columns * n_rows];
    /* and starting it with all entries as Zero / False */
    memset(to_evaluate, 0, n_columns * n_rows * sizeof(int));

    /* getting the nodes directed connected to the output */
    for(int i = 0; i < n; i++) {
        /* the first indexes are from the input values so we are only interested on values equal greater than n_input_values */
        if(a->output_nodes[i] >= n_input_values) {
            to_evaluate[a->output_nodes[i] - n_input_values] = 1; /* that node must be evaluated */
        }
    }
    /* going in the reverse order to check which node is dependent of which */
    for(int i = n_columns * n_rows; i >= 0; i--) {
        /* if that node needs to be evaluated, we marks its inputs as nodes that also need evaluation */
        if(to_evaluate[i] == 1) {
            int c0 = a->genotype[i].connection0 - n_input_values; /* we subtract n_input_values to get the real node index instead of its output index */
            /* if the value is greater or equal to zero, means that the input chosen is a node, not a value coming from the input array, so we mark it as peding evaluation */
            if(c0 >= 0)
                to_evaluate[c0] = 1;

            int c1 = a->genotype[i].connection1 - n_input_values; /* we subtract n_input_values to get the real node index instead of its output index */
            /* if the value is greater or equal to zero, means that the input chosen is a node, not a value coming from the input array, so we mark it as peding evaluation */
            if(c1 >= 0)
                to_evaluate[c1] = 1;
        }
    }
    /* getting the output of each used node */
    for(int i = 0; i < n_columns * n_rows; i++) {
        if(to_evaluate[i] == 1) {
            int f_id = a->genotype[i].func_id;
            int value_c0 = output_nodes_values[a->genotype[i].connection0];
            int value_c1 = output_nodes_values[a->genotype[i].connection1];
            output_nodes_values[i + n_input_values] = computeFunc(value_c0, value_c1, f_id);
        }
    }

    /* putting the output values in the position array to be further evaluated */
    for(int i = 0; i < n; i++) {
        a->x[i] = output_nodes_values[a->output_nodes[i]];
    }

}

void point_mutation(Agent* a, int n_columns, int n_rows, int levels_back, int n_input_values, int n_functions) {
    /* we are calculating the probability of a single gene be a function gene (we multiply by 3 because each node of the genotype has 3 genes/alleles and sum n because there are also the output genes) */
    double total_genes = 3 * (double)n_columns * (double)n_rows + a->n;
    double proba_func_gene = (double)n_columns * (double)n_rows / total_genes;
    /* getting the probability of selecting an connection gene (multiply by 2 because there are 2 connection genes for each function gene)*/
    double proba_connection_gene = 2 * (double)n_columns * (double)n_rows / total_genes;

    double rand_val = GenerateUniformRandomNumber(0, 1);

    /* we are going to select a function gene to be mutated */
    if(rand_val < proba_func_gene) {
        int node_index = (int)GenerateUniformRandomNumber(0, n_columns * n_rows);
        /* generate random function index */
        a->genotype[node_index].func_id = (int)GenerateUniformRandomNumber(0, n_functions);
    }
    /* we are going to select a connection gene to be mutated */
    else if(rand_val < proba_func_gene + proba_connection_gene){
        int node_index = (int)GenerateUniformRandomNumber(0, n_columns * n_rows);
        /* choosing which one of the connection genes is going to be mutated (50%-50% chance) */
        if(GenerateUniformRandomNumber(0, 1) < 0.5)
            a->genotype[node_index].connection0 = get_valid_input_index(n_rows, levels_back, n_input_values, node_index);
        else
            a->genotype[node_index].connection1 = get_valid_input_index(n_rows, levels_back, n_input_values, node_index);
    }
        /* we are going to select an output gene to be mutated */
    else {
        int node_index = (int)GenerateUniformRandomNumber(0, a->n);
        /* getting a new output index */
        a->output_nodes[node_index] = get_valid_index_for_output(n_columns, n_rows, n_input_values);
    }
}

/**
 * It executes the Cartesian Genetic Programming for function minimization
 * @param s Search space
 * @param prtFunction Pointer to the function used to evaluate particles
 * @param ... List of additional arguments
 */
void runCGP(SearchSpace *s, prtFun Evaluate, ...) {
    va_list arg, argtmp;
    double beta, prob;
    int lambda = 4; /* number of offsprings to be generated from an individual */

    va_start(arg, Evaluate);
    va_copy(argtmp, arg);

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @runCGP.\n");
        exit(-1);
    }

    /* generate random valid genotypes (coding genes and output genes) */
    /* for each agent */
    for(int agent_index = 0; agent_index < s->m; agent_index++) {
        /* for each agent node in the genotype */
        for(int node_index = 0; node_index < (s->n_columns * s->n_rows); node_index++) {
            /* generate random function index */
            s->a[agent_index]->genotype[node_index].func_id = (int)GenerateUniformRandomNumber(0, s->n_functions);
            s->a[agent_index]->genotype[node_index].connection0 = get_valid_input_index(s->n_rows, s->levels_back, s->n_input_values, node_index);
            s->a[agent_index]->genotype[node_index].connection1 = get_valid_input_index(s->n_rows, s->levels_back, s->n_input_values, node_index);
        }

        /* for each output node index a*/
        for(int i = 0; i < s->n; i++) {
            s->a[agent_index]->output_nodes[i] = get_valid_index_for_output(s->n_columns, s->n_rows, s->n_input_values);
        }
    }

    for(int agent_index = 0; agent_index < s->m; agent_index++) {
        /* decode the genes and saving the output on s->a[i]->x */
        decode_chromossome(s->a[agent_index], s->n_columns, s->n_rows, s->n_input_values, s->n);
    }

    EvaluateSearchSpace(s, _CGP_, Evaluate, arg); /* Initial evaluation */

    for (int t = 1; t <= s->iterations; t++)
    {
        /* make reproduction by mutation and make selection (1 + lambda) */
        /* for each agent */
        for(int agent_index = 0; agent_index < s->m; agent_index++) {
            /* for each offspring to be generated */
            Agent* best_offspring = NULL;
            for(int offspring_counter = 0; offspring_counter < lambda; offspring_counter++) {
                /* copying the agent and its internal structures */
                Agent* current_offspring = GenerateNewAgent(s, _CGP_);
                memcpy(current_offspring->x, s->a[agent_index]->x, s->n * sizeof(double));
                memcpy(current_offspring->output_nodes, s->a[agent_index]->output_nodes, s->n * sizeof(int));
                memcpy(current_offspring->genotype, s->a[agent_index]->genotype, s->n_columns * s->n_rows * sizeof(CGP_Node));
                memcpy(current_offspring->input_values, s->a[agent_index]->input_values, s->n_input_values * sizeof(double));


                int num_mutations = (int)(s->pMutation * 3 * s->n_columns * s->n_rows + s->n);
                /* mutating that agent num_mutations times */
                for(int i = 0; i < num_mutations; i++)
                    point_mutation(current_offspring, s->n_columns, s->n_rows, s->levels_back, s->n_input_values, s->n_functions);

                /* decoding offspring chromossome */
                decode_chromossome(current_offspring, s->n_columns, s->n_rows, s->n_input_values, s->n);
                /* evaluating offspring */
                va_list argtmp;
                va_copy(argtmp, arg);
                current_offspring->fit = Evaluate(current_offspring, arg);
                va_copy(arg, argtmp);

                /* if is the first iteration... */
                if(best_offspring == NULL) {
                    best_offspring = current_offspring;
                }
                /* if the current offspring has the best fitness yet */
                else if(current_offspring->fit < best_offspring->fit) {
                    /* destroying the old best offspring */
                    DestroyAgent(&(best_offspring), _CGP_);
                    best_offspring = current_offspring;
                }
                else {
                    /* destroying the current offspring */
                    DestroyAgent(&(current_offspring), _CGP_);
                }
            }

            /* if the best offspring has better or equal fitness than its parent, it will become the new parent */
            if(best_offspring->fit <= s->a[agent_index]->fit) {
                /* destroying the parent and making the offspring the new future parent */
                DestroyAgent(&(s->a[agent_index]), _CGP_);
                s->a[agent_index] = best_offspring;
            }
            else {
                /* destroying the offspring */
                DestroyAgent(&(best_offspring), _CGP_);
            }

        }
        /* decode the genes and saving the output on s->a[i]->x*/
        for(int agent_index = 0; agent_index < s->m; agent_index++) {
            /* decode the genes and saving the output on s->a[i]->x */
            decode_chromossome(s->a[agent_index], s->n_columns, s->n_rows, s->n_input_values, s->n);
        }

        EvaluateSearchSpace(s, _CGP_, Evaluate, arg);

        // ShowSearchSpace(s, _CGP_);

        fprintf(stderr, "OK: %.2f%% done. (minimum fitness value %lf) \n", 100 * (double)t / (double)s->iterations, s->gfit);
        //fprintf(stderr, "Vector: ");
        //for (int i = 0; i < s->n; i++) {
        //        fprintf(stderr, "%f ", s->g[i]);
        //}
        //fprintf(stderr, "\n\n");
    }

    va_end(arg);

}
