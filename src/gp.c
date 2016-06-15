#include "gp.h"

/* Tree-related functions */
/* It creates a random tree based on the GROW algorithm described in "Two Fast Tree-Creation Algorithms for Genetic Programming", S. Lukw, IEEE Transactions on Evolutionary Computation, 2000.
Parameters:
s: search space
dmin: minimum depth
dmax: maximum depth */
Node *GROW(SearchSpace *s, int dmin, int dmax){
    int it, aux, const_id;
    Node *tmp = NULL, *node = NULL;
    
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @EvaluateSwarm.\n");
        return NULL;
    }
    
    if(dmin == dmax){
        aux = GenerateUniformRandomNumber(1, s->n_terminals-1);
	if(!strcmp(s->terminal[aux], "CONST")){
	    const_id = GenerateUniformRandomNumber(0, s->n_constants-1);
	    return CreateNode(s->terminal[aux], aux, 1, 1, const_id);
	}
        return CreateNode(s->terminal[aux], aux, 1, 0, -1);
    }
    /*else{
        aux = rand()%(gp->n_functions+gp->n_terminals);
        if(aux >= gp->n_functions){ // if tmp is a terminal
            aux = aux-gp->n_functions;
	    if(!strcmp(gp->terminal[aux], "CONST")){
		srand(time(NULL));
		T = gsl_rng_default;
		r = gsl_rng_alloc(T);
		gsl_rng_set(r, random_seed());
	    
		const_id = gsl_rng_uniform_int(r, gp->constant->size);
		gsl_rng_free(r);
		tmp = CreateNode(gp->terminal[aux], aux, 1, 1, const_id);
	    }
            else tmp = CreateNode(gp->terminal[aux], aux, 1, 0, -1);
            return tmp;
        }
        else{
            node = CreateNode(gp->function[aux], aux, 0, 0, -1);
            for(it = 0; it < N_ARGS_FUNCTION[getFUNCTIONid(gp->function[aux])]; it++){
                tmp = GROW(gp, d+1,dmax);
                if(!it)
                    node->esq = tmp;
                else{
                    node->dir = tmp;
                    tmp->son_esq = 0;
                }
                tmp->parent = node;
            }
            return node;
        }
    }*/
}

/* It creates a node
Parameters:
value: content of the node
node_id: identifier of the node id, which can be its position in the array of terminals or functions
flag:
is_const: flag to indicate the node to be created is a constant or not
const_id: identifier of the constant (i.e. its position in the array of constants) */
/*Node *CreateNode(char *content, int node_id, char is_terminal, char is_const, int const_id){
    Node *tmp = NULL;
    tmp = (Node *)malloc(sizeof(Node));
    
    if(!value){
        fprintf(stderr,"\nInvalid input @CreateNode.\n");
        exit(-1);
    }

    tmp->terminal_id = terminal_id; tmp->is_const = is_const; tmp->const_id = const_id;
    tmp->esq = tmp->dir = tmp->parent = NULL; tmp->is_terminal = flag;
    tmp->son_esq = 1; /* by default, every node is a left node */
    /*tmp->elem = (char *)malloc((strlen(value)+1)*sizeof(char));
    strcpy(tmp->elem, value);
    
    return tmp;
}*/
/**************************/