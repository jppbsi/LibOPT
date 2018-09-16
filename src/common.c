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

/* number of arguments (descendants) required by each terminal function in GP in the following order:
SUM, SUB, MUL, DIV, EXP, SQRT, LOG, ABS, AND, OR, XOR, NOT, TSUM, TSUB, TMUL and TDIV */
const int N_ARGS_FUNCTION[] = {2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 2};

/* Agent-related functions */
/* It creates an agent
Parameters:
n: number of decision variables
opt_id: identifier of the optimization technique
tensor_dim: dimensionality of the tensor (you should use _NOTENSOR_ if it is not used) */
Agent *CreateAgent(int n, int opt_id, int tensor_dim){
    if ((n < 1) || opt_id < 1){
        fprintf(stderr, "\nInvalid parameters @CreateAgent.\n");
        return NULL;
    }

    Agent *a = NULL;
    a = (Agent *)malloc(sizeof(Agent));
    a->v = NULL;
    a->xl = NULL;
    a->fit = DBL_MAX;
    a->t = NULL;
    a->t_v = NULL;
    a->t_xl = NULL;
    a->prev_x = NULL;
    a->f = NAN;
    a->r = NAN;
    a->A = NAN;
    a->nb = NULL;
    a->pfit = DBL_MAX;
    a->best_fit = DBL_MAX;
    a->n = n;

    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
        case _CS_:
        case _GP_:
        case _GA_:
        case _BHA_:
        case _WCA_:
        case _MBO_:
        case _ABC_:
        case _BSO_:
        case _JADE_:
        case _COBIDE_:
        case _BSA_:
        case _ABO_:
        case _HS_:
            a->x = (double *)calloc(n, sizeof(double));
            if ((opt_id != _GP_) && (opt_id != _TGP_) & (opt_id != _BSO_))
                a->v = (double *)calloc(n, sizeof(double));
            if (opt_id == _PSO_)
                a->xl = (double *)calloc(n, sizeof(double));
            break;
        case _LOA_:
            a->x = (double *)calloc(n, sizeof(double));
            a->xl = (double *)calloc(n, sizeof(double));
            a->prev_x = (double *)calloc(n, sizeof(double));
            break;
        case _TGP_:
            if(tensor_dim == _NOTENSOR_){
                fprintf(stderr, "\nInvalid tensor dimension @CreateAgent\n.");
                return NULL;
            }
            a->t = CreateTensor(n, tensor_dim);
            a->x = (double *)calloc(n, sizeof(double));
            break;
        case _SA_:
            a->x = (double *)calloc(n, sizeof(double));
            break;

        default:
            free(a);
            fprintf(stderr, "\nInvalid optimization identifier @CreateAgent\n.");
            return NULL;
            break;
    }

    return a;
}

/* It deallocates an agent
Parameters:
a: address of the agent to be deallocated
opt_id: identifier of the optimization technique */
void DestroyAgent(Agent **a, int opt_id){
    Agent *tmp = NULL;

    tmp = *a;
    if (!tmp){
        fprintf(stderr, "\nAgent not allocated @DestroyAgent.\n");
        exit(-1);
    }

    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
        case _CS_:
        case _GP_:
        case _GA_:
        case _BHA_:
        case _WCA_:
        case _MBO_:
        case _ABC_:
        case _BSO_:
        case _JADE_:
        case _COBIDE_:
        case _BSA_:
        case _ABO_:
        case _HS_:
            if (tmp->x) free(tmp->x);
            if (tmp->v) free(tmp->v);
            if (opt_id == _PSO_)
                if (tmp->xl)
                    free(tmp->xl);
            break;
        case _LOA_:
            if (tmp->x) free(tmp->x);
            if (tmp->v) free(tmp->v);
            if (tmp->xl) free(tmp->xl);
            if (tmp->prev_x) free(tmp->prev_x);
            break;
        case _TGP_:
            if (tmp->x) free(tmp->x);
            if (tmp->t) DestroyTensor(&(tmp->t), tmp->n);
            break;
        case _SA_:
          if(tmp->x)
            free(tmp->x);
          /* attention: these variables were allocated at CreateSearchSpace, not at CreateAgent. */
          if(tmp->LB)
            free(tmp->LB);
          if(tmp->UB)
            free(tmp->UB);
          break;

        default:
            fprintf(stderr, "\nInvalid optimization identifier @DestroyAgent.\n");
            break;
    }

    free(tmp);
}

/* It checks whether a given agent has excedeed boundaries
Parameters:
s: search space
a: agent */
void CheckAgentLimits(SearchSpace *s, Agent *a)
{
    if ((!s) || (!a))
    {
        fprintf(stderr, "\nInvalid input parameters @CheckAgentLimits.\n");
        exit(-1);
    }

    int j;

    for (j = 0; j < a->n; j++)
    {
        if (a->x[j] < s->LB[j])
            a->x[j] = s->LB[j];
        else if (a->x[j] > s->UB[j])
            a->x[j] = s->UB[j];
    }
}

/* It copies an agent
Parameters:
a: agent
opt_id: identifier of the optimization technique
tensor_dim: dimensionality of the tensor (it takes the value -1 if it is not used) */
Agent *CopyAgent(Agent *a, int opt_id, int tensor_dim)
{
	int i;
    if (!a)
    {
        fprintf(stderr, "\nAgent not allocated @CopyAgent.\n");
        exit(-1);
    }

    Agent *cpy = NULL;
    cpy = CreateAgent(a->n, opt_id, tensor_dim);

    switch (opt_id)
    {
    case _PSO_:
    case _BA_:
    case _FPA_:
    case _FA_:
    case _CS_:
    case _GA_:
    case _BHA_:
    case _WCA_:
    case _ABC_:
    case _JADE_:
    case _COBIDE_:
    case _BSA_:
    case _ABO_:
    case _HS_:
    case _SA_:
        memcpy(cpy->x, a->x, a->n * sizeof(double));
        memcpy(cpy->v, a->v, a->n * sizeof(double));
        if (opt_id == _PSO_)
            memcpy(cpy->xl, a->xl, a->n * sizeof(double));
        if (opt_id == _FA_ || opt_id == _JADE_  || opt_id == _COBIDE_  || opt_id == _BSA_ )
            cpy->fit = a->fit;
        break;
    default:
        fprintf(stderr, "\nInvalid optimization identifier @CopyAgent.\n");
        DestroyAgent(&cpy, opt_id);
        return NULL;
        break;
    }

    return cpy;
}

/* It evaluate an agent according to each technique
Parameters:
s: search space
a: agent
opt_id: identifier of optimization technique
Evaluate: pointer to the function used to evaluate
arg: list of additional arguments */
void EvaluateAgent(SearchSpace *s, Agent *a, int opt_id, prtFun Evaluate, va_list arg)
{
    if (opt_id < 1) // invalid opt_id
    {
      fprintf(stderr, "\nInvalid optimization identifier @EvaluateAgent.\n");
      return;
    }

    if (a == NULL) // not allocated agent
    {
        fprintf(stderr, "\nNull pointer to Agent @EvaluateAgent.\n");				return;
    }

    int i;
    double eva;
    va_list argtmp;

    va_copy(argtmp, arg);

    switch (opt_id)
    {
	case _COBIDE_:
	case _JADE_:
        a->fit = Evaluate(a, arg); /* It executes the fitness function for agent  */

        if (a->fit < s->gfit)
        { /* It updates the global best value and position */
            s->best = i;
            s->gfit = a->fit;
            for (i = 0; i < s->n; i++)
                s->g[i] = a->x[i];
        }

        break;
    case _LOA_:
        /* saving the last fitness value */
        a->pfit = a->fit;
        /* saving the previous location */
        for (i = 0; i < s->n; i++)
            a->prev_x[i] = a->x[i];

        a->fit = Evaluate(a, arg);
        
        /* if the actual fit is the best fitness so far of the agent */
        if (a->fit < a->best_fit)
        {
            a->best_fit = a->fit;
            /* update the best visited location */
            for (i = 0; i < s->n; i++)
                a->xl[i] = a->x[i];
            /* The this lion is the best solution so far */
            if (a->fit < s->gfit)
            {
                s->gfit = a->fit;
                /* update the global best visited location */
                for (i = 0; i < s->n; i++)
                    s->g[i] = a->x[i];
            }
        }
        break;

      case _SA_:
        a->fit = Evaluate(a, arg);
        /* If the actual position is the best solution so far */
        if (a->fit < s->gfit)
        {
          s->gfit = a->fit;
          /* update the global best solution */
          memcpy(s->g, a->x, s->n * sizeof(double));
        }
        break;
    }

    va_copy(arg, argtmp);

}

/* It generates a new agent according to each technique
Paremeters:
s: search space
opt_id: identifier of the optimization technique */
Agent *GenerateNewAgent(SearchSpace *s, int opt_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @GenerateNewAgent.\n");
        exit(-1);
    }

    Agent *a = NULL;
    int i, j;
    double r, signal;

    switch (opt_id)
    {
    case _PSO_:
        break;
    case _BA_:
        a = CreateAgent(s->n, _BA_, _NOTENSOR_);

        /* The factor 0.001 limits the step sizes of random walks */
        for (j = 0; j < s->n; j++)
            a->x[j] = s->g[j] + 0.001 * GenerateUniformRandomNumber(0, 1);
        break;
    case _FPA_:
        break;
    case _FA_:
        break;
    case _CS_:
        a = CreateAgent(s->n, _CS_, _NOTENSOR_);
        break;
    case _GA_:
        break;
    case _BHA_:
        a = CreateAgent(s->n, _BHA_, _NOTENSOR_);
        break;
    case _WCA_:
        a = CreateAgent(s->n, _WCA_, _NOTENSOR_);
        break;
    case _MBO_:
        break;
    case _ABC_:
        a = CreateAgent(s->n, _ABC_, _NOTENSOR_);
        break;
    case _BSA_:
        a = CreateAgent(s->n, _BSA_, _NOTENSOR_);
        break;
    case _JADE_:
        a = CreateAgent(s->n, _JADE_, _NOTENSOR_);
        break;
    case _COBIDE_:
        a = CreateAgent(s->n, _COBIDE_, _NOTENSOR_);
        break;
    case _ABO_:
        a = CreateAgent(s->n, _ABO_, _NOTENSOR_);
        break;
    case _HS_:
        a = CreateAgent(s->n, _HS_, _NOTENSOR_);

        for (j = 0; j < s->n; j++)
        {
            r = GenerateUniformRandomNumber(0, 1);
            if (s->HMCR >= r)
            {
                i = GenerateUniformRandomNumber(0, s->m);
                r = GenerateUniformRandomNumber(0, 1);
                a->x[j] = s->a[i]->x[j];
                if (s->PAR >= r)
                {
                    signal = GenerateUniformRandomNumber(0, 1);
                    r = GenerateUniformRandomNumber(0, 1);
                    if (signal >= 0.5)
                        a->x[j] = s->a[i]->x[j] + r * s->bw;
                    else
                        a->x[j] = s->a[i]->x[j] - r * s->bw;
                }
            }
            else
            {
                r = (s->UB[j] - s->LB[j]) * GenerateUniformRandomNumber(0, 1) + s->LB[j];
                a->x[j] = r;
            }
        }
        break;
    default:
        fprintf(stderr, "\nInvalid optimization identifier @GenerateNewAgent.\n");
        return NULL;
        break;
    }

    return a;
}


/* It copies the agents from s to oldS
Parameters:
s: source search space
oldS: destination search space 
tensor_dim: identifier of tensor's dimension*/
void CopySearchSpaceAgents(SearchSpace *s, SearchSpace *oldS, int opt_id, int tensor_id)
{
    int j, k;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @CopySearchSpaceAgents.\n");
        exit(-1);
    }

    if (!oldS)
    {
        fprintf(stderr, "\nSearch space not allocated @CopySearchSpaceAgents.\n");
        exit(-1);
    }

    for (j = 0; j < oldS->m; j++)
	{

		if(oldS->a[j]->t  && tensor_id > 0) DestroyTensor(&(oldS->a[j]->t), oldS->n);
        DestroyAgent(&(oldS->a[j]), opt_id);
        oldS->a[j] = CopyAgent(s->a[j], opt_id, tensor_id);
		if(s->a[j]->t && tensor_id > 0) oldS->a[j]->t = CopyTensor(s->a[j]->t, s->n, tensor_id);
	}
}

/* It performs a SearchSpace permutation
Parameters:
s: search space
opt_id: identifier of the optimization technique
tensor_dim: identifier of tensor's dimension*/
void TensorPermutation(SearchSpace *s, int opt_id, int tensor_dim)
{
	int i;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @Permutation.\n");
        exit(-1);
    }
	Agent *tmp = NULL;
	double **t = NULL;
	for (i = 0; i < s->m; i++)
	{
		//generate a random position
		int r = rand() % s->m;
		if (r!=i){
			tmp = CopyAgent(s->a[i], opt_id, tensor_dim);
			t = CopyTensor(s->a[i]->t, s->n, tensor_dim);

			DestroyTensor(&(s->a[i]->t), s->n);
			DestroyAgent(&(s->a[i]), opt_id);

			s->a[i] = CopyAgent(s->a[r], opt_id, tensor_dim);
			s->a[i]->t = CopyTensor(s->a[r]->t, s->n, tensor_dim);

			DestroyTensor(&(s->a[r]->t), s->n);
			DestroyAgent(&(s->a[r]), opt_id);


			s->a[r] = CopyAgent(tmp, opt_id,tensor_dim);
			s->a[r]->t = CopyTensor(t, s->n, tensor_dim);
		
			DestroyTensor(&(t), s->n);
			DestroyAgent(&tmp, opt_id);
		}
	}
	
	
}

/* It performs a SearchSpace permutation
Parameters:
s: search space
opt_id: identifier of the optimization technique
tensor_dim: identifier of tensor's dimension*/
void Permutation(SearchSpace *s, int opt_id, int tensor_dim)
{
	int i;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @Permutation.\n");
        exit(-1);
    }
	Agent *tmp = NULL;
	for (i = 0; i < s->m; i++)
	{
		//generate a random position
		int r = rand() % s->m;
		if (r!=i){
			tmp = CopyAgent(s->a[i], opt_id, tensor_dim);
			DestroyAgent(&(s->a[i]), opt_id);
			s->a[i] = CopyAgent(s->a[r], opt_id, tensor_dim);
			DestroyAgent(&(s->a[r]), opt_id);
			s->a[r] = CopyAgent(tmp, opt_id,tensor_dim);
		
			DestroyAgent(&tmp, opt_id);
		}
	}
}

/**************************/

/* Search Space-related functions */
/* It creates a search space
Parameters:
m: number of agents
n: number of decision variables
opt_id: identifier of the optimization technique
additional parameters: related to each technique
PSO, BA, FPA and FA: do not require additional parameters
GP: it requires the minimum and maximum depth of a tree, number of terminals and a matrix (char **) with the terminals' names
Tensor-based approaches require the number of dimensions of the tensor, i.e., if it is a quaternion, octonion or sedenion */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id, ...){
    SearchSpace *s = NULL;
    va_list arg;

    if ((m < 1) || (n < 1) || (opt_id < 1)){
        fprintf(stderr, "\nInvalid parameters @CreateSearchSpace.\n");
        return NULL;
    }
    int i, j, remained_lions, tensor_dim;

    va_start(arg, opt_id);
    s = (SearchSpace *)malloc(sizeof(SearchSpace));
    s->m = m;
    s->n = n;
    s->gfit = DBL_MAX;
    s->iterations = 0;
    s->is_integer_opt = 1;
    s->tensor_dim = -1;

    /* PSO */
    s->w = NAN;
    s->w_min = NAN;
    s->w_max = NAN;
    s->c1 = NAN;
    s->c2 = NAN;

    /* BA */
    s->f_min = NAN;
    s->f_max = NAN;
    s->r = NAN;
    s->A = NAN;

    /* FPA */
    s->beta = NAN;
    s->p = NAN;

    /* FA */
    s->alpha = NAN;
    s->beta_0 = NAN;
    s->gamma = NAN;

    /* GP and GA */
    s->pReproduction = NAN;
    s->pMutation = NAN;
    s->pCrossover = NAN;

    /* WCA */
    s->nsr = 0;
    s->dmax = NAN;

    /* MBO */
    s->X = 0;
    s->M = 0;
    s->leftSide = 1;

    /* ABC */
    s->limit = 0;

    /* HS */
    s->HMCR = NAN;
    s->PAR = NAN;
    s->bw = NAN;

    /* IHS */
    s->PAR_min = NAN;
    s->PAR_max = NAN;
    s->bw_min = NAN;
    s->bw_max = NAN;

    /* BSO */
    s->p_one_cluster = NAN;
    s->p_one_center = NAN;
    s->p_two_centers = NAN;

    /* BSA */
    s->mix_rate = NAN;
    s->F = 0;

    /* JADE */	
    s->c = NAN;
    s->p_greediness = NAN;

    /* COBIDE */
    s->pb = NAN;
    s->ps = NAN;

    /* ABO */
    s->ratio_e = NAN;
    s->step_e = NAN;

    /* GP and LOA uses a different structure than that of others */
    if ((opt_id != _GP_) && (opt_id != _TGP_) && (opt_id != _LOA_)){
        s->a = (Agent **)malloc(s->m * sizeof(Agent *));
        s->a[0] = CreateAgent(s->n, opt_id, _NOTENSOR_);
        if (s->a[0]){
            /* Here, we verify whether opt_id is valid or not. In the latter case, function CreateAgent returns NULL. */
            for (i = 1; i < s->m; i++)
                s->a[i] = CreateAgent(s->n, opt_id, _NOTENSOR_);
            if (opt_id == _MBO_){ 
                s->k = va_arg(arg, int);
                for (i = 0; i < s->m; i++)
                {
                    s->a[i]->nb = (Agent **)malloc(s->k * sizeof(Agent *));
                    for (j = 0; j < s->k; j++)
                        s->a[i]->nb[j] = CreateAgent(s->n, opt_id, _NOTENSOR_);
                }
            }

            else if(opt_id == _SA_)
            {
              /* allocating the array of boudns for each agent */
              for(i = 0; i < s->m; i++)
              {
                s->a[i]->LB = (double *)malloc(s->n * sizeof(double));
                s->a[i]->UB = (double *)malloc(s->n * sizeof(double));
              }
            }
        }
        else{
            free(s->a);
            free(s);
            fprintf(stderr, "\nInvalid optimization identifier @CreateSearchSpace.\n");
            return NULL;
        }

        s->g = (double *)calloc(s->n, sizeof(double));
        s->t_g = NULL;
    }
    else{
        if ((opt_id == _GP_) || (opt_id == _TGP_)){
            s->min_depth = va_arg(arg, int);
            s->max_depth = va_arg(arg, int);
            s->n_terminals = va_arg(arg, int);
            s->n_constants = va_arg(arg, int);
            s->n_functions = va_arg(arg, int);
            s->terminal = va_arg(arg, char **);
            if(opt_id == _GP_) s->constant = va_arg(arg, double **);
            else s->t_constant = va_arg(arg, double ***); /* tensor-based GP */
            s->function = va_arg(arg, char **);

            s->T = (Node **)malloc(s->m * sizeof(Node *));
            for (i = 0; i < s->m; i++)
                s->T[i] = GROW(s, s->min_depth, s->max_depth);

            if (opt_id != _TGP_) tensor_dim = _NOTENSOR_;
            else tensor_dim = va_arg(arg, int);
    
            s->a = (Agent **)malloc(s->n_terminals * sizeof(Agent *));
            for (i = 0; i < s->n_terminals; i++)
                    s->a[i] = CreateAgent(s->n, opt_id, tensor_dim);
            
            s->tree_fit = (double *)malloc(s->m * sizeof(double));
            for (i = 0; i < s->m; i++)
                s->tree_fit[i] = DBL_MAX;

            s->g = (double *)calloc(s->n, sizeof(double));
        }
        if (opt_id == _LOA_){
            s->sex_rate = va_arg(arg, double);        /* getting the percent of females in each pride, 1-s->sex_rate is the percent of nomad females */
            s->nomad_percent = va_arg(arg, double);   /* getting the percent of nomad lions of the entire population */
            s->roaming_percent = va_arg(arg, double); /* getting the percentage of the territory that will be visited by resident males*/
            s->mating_prob = va_arg(arg, double);     /* getting the probability of a female mate with a male */
            s->pMutation = va_arg(arg, double);       /* getting the probability of mutation */
            s->imigration_rate = va_arg(arg, double); /* getting the percent of female lions that will imigrate */
            s->n_prides = va_arg(arg, int);           /* getting the number of prides */
            s->g = (double *)calloc(s->n, sizeof(double));
            s->n_female_nomads = round(s->m * s->nomad_percent * (1 - s->sex_rate));   /* determining de number of nomad females */
            s->female_nomads = (Agent **)malloc(sizeof(Agent *) * s->n_female_nomads); /* allocating the array of nomad females */
            for (i = 0; i < s->n_female_nomads; i++)
                s->female_nomads[i] = CreateAgent(s->n, opt_id, _NOTENSOR_);                   /* not using the array of agents */
            s->n_male_nomads = round(s->m * s->nomad_percent * s->sex_rate);       /* determining de number of nomad males */
            s->male_nomads = (Agent **)malloc(sizeof(Agent *) * s->n_male_nomads); /* allocating the array of nomad males */
            for (i = 0; i < s->n_male_nomads; i++)
                s->male_nomads[i] = CreateAgent(s->n, opt_id, _NOTENSOR_); /* not using the array of agents */

            remained_lions = s->m - s->n_female_nomads - s->n_male_nomads; /* determining how many lions will be in prides */

            /* determining randomly the number of lions on each of the n prides */
            int *qty_lions_each_pride = (int *)calloc(s->n_prides, sizeof(int)); /* each index represents how many lions are in pride i */
            for (i = 0; i < remained_lions; i++)                                 /* for each remaning lion that is not nomad... */
                qty_lions_each_pride[(int)GenerateUniformRandomNumber(0, s->n_prides)]++; /* sum one on a random index */
            
            s->pride_id = (struct Pride *)malloc(sizeof(struct Pride) * s->n_prides); /* allocating the array of prides */
            for (i = 0; i < s->n_prides; i++){                                                                                          /* for each pride... */
                s->pride_id[i].n_females = round(qty_lions_each_pride[i] * (1 - s->sex_rate));         /* determining de number of females in that pride */
                s->pride_id[i].females = (Agent **)malloc(sizeof(Agent *) * s->pride_id[i].n_females); /* allocating the array of females from that pride */
                for (j = 0; j < s->pride_id[i].n_females; j++)
                    s->pride_id[i].females[j] = CreateAgent(s->n, opt_id, _NOTENSOR_);                         /* not using the array of agents */
                s->pride_id[i].n_males = qty_lions_each_pride[i] - s->pride_id[i].n_females;       /* determining the number of males in that pride */
                s->pride_id[i].males = (Agent **)malloc(sizeof(Agent *) * s->pride_id[i].n_males); /* allocating the array of males from that pride */
                for (j = 0; j < s->pride_id[i].n_males; j++)
                    s->pride_id[i].males[j] = CreateAgent(s->n, opt_id, _NOTENSOR_); /* not using the array of agents */
            }
            free(qty_lions_each_pride);
        }
    }

    s->LB = (double *)malloc(s->n * sizeof(double));
    s->UB = (double *)malloc(s->n * sizeof(double));

    va_end(arg);

    return s;
}

/* It deallocates a search space
Parameters:
s: address of the search space to be deallocated
opt_id: identifier of the optimization technique */
void DestroySearchSpace(SearchSpace **s, int opt_id){
    SearchSpace *tmp = NULL;
    int i, j;

    tmp = *s;
    if (!tmp){
        fprintf(stderr, "\nSearch space not allocated @DestroySearchSpace.\n");
        exit(-1);
    }

    /* GP and LOA uses a different structure than that of others */
    if ((opt_id != _GP_) && (opt_id != _TGP_) && (opt_id != _LOA_)){ 
        if (opt_id == _MBO_){ /* We free the neighbours allocation */
            for (i = 0; i < tmp->m; i++){
                for (j = 0; j < tmp->k; j++)
                    if (tmp->a[i]->nb[j])
                        DestroyAgent(&(tmp->a[i]->nb[j]), opt_id);
                free(tmp->a[i]->nb);
            }
        }

        for (i = 0; i < tmp->m; i++)
            if (tmp->a[i])
                DestroyAgent(&(tmp->a[i]), opt_id);
        free(tmp->a);

        switch (opt_id){
            case _PSO_:
            case _BA_:
            case _FPA_:
            case _FA_:
            case _CS_:
            case _GA_:
            case _BHA_:
            case _WCA_:
            case _MBO_:
            case _ABC_:
            case _BSO_:
            case _BSA_:
            case _JADE_:
            case _COBIDE_:
            case _ABO_:
            case _HS_:
            case _SA_:
                if (tmp->g) free(tmp->g);
            break;
            default:
                fprintf(stderr, "\nInvalid optimization identifier @DestroySearchSpace.\n");
                break;
            }
        }
    else{
        
        if ((opt_id == _GP_) || (opt_id == _TGP_)){
            for (i = 0; i < tmp->m; i++)
                if (tmp->T[i]) DestroyTree(&(tmp->T[i]));
            if (tmp->T) free(tmp->T);

            for (i = 0; i < tmp->n_terminals; i++){
                if (tmp->a[i]) DestroyAgent(&(tmp->a[i]), opt_id);
                if (tmp->terminal[i]) free(tmp->terminal[i]);
            }
            if (tmp->a) free(tmp->a);
            if (tmp->terminal) free(tmp->terminal);

            if (tmp->function){
                for (i = 0; i < tmp->n_functions; i++)
                    if (tmp->function[i]) free(tmp->function[i]);
                free(tmp->function);
            }

            if (opt_id == _GP_){
                if (tmp->constant){
                    for (i = 0; i < tmp->n; i++)
                        if (tmp->constant[i]) free(tmp->constant[i]);
                    free(tmp->constant);
                }
            }else{ /* Tensor-based GP */
                if (tmp->t_constant){
                    for (i = 0; i < N_CONSTANTS; i++){
                        for(j = 0; j < tmp->n; j++)
                            if(tmp->t_constant[i][j]) free(tmp->t_constant[i][j]);
                        if(tmp->t_constant[i]) free(tmp->t_constant[i]);
                    }
                    free(tmp->t_constant);
                }
            }
            if (tmp->tree_fit) free(tmp->tree_fit);
            if (tmp->g) free(tmp->g);
        }
        if (opt_id == _LOA_){
            for (i = 0; i < tmp->n_female_nomads; i++)
                DestroyAgent(&(tmp->female_nomads[i]), opt_id);
            free(tmp->female_nomads);
            for (i = 0; i < tmp->n_male_nomads; i++)
                DestroyAgent(&(tmp->male_nomads[i]), opt_id);
            free(tmp->male_nomads);
            for (i = 0; i < tmp->n_prides; i++){
                for (j = 0; j < tmp->pride_id[i].n_females; j++)
                    DestroyAgent(&(tmp->pride_id[i].females[j]), opt_id);
                free(tmp->pride_id[i].females);
                for (j = 0; j < tmp->pride_id[i].n_males; j++)
                    DestroyAgent(&(tmp->pride_id[i].males[j]), opt_id);
                free(tmp->pride_id[i].males);
            }
            free(tmp->pride_id);
            free(tmp->g);
        }
    }

    if (tmp->LB) free(tmp->LB);
    if (tmp->UB) free(tmp->UB);

    free(tmp);
    tmp = NULL;
}

/* It initializes an allocated search space
Parameters:
s: search space
opt_id: identifier of the optimization technique */
void InitializeSearchSpace(SearchSpace *s, int opt_id){
    if (!s){
        fprintf(stderr, "\nSearch space not allocated @InitializeSearchSpace.\n");
        exit(-1);
    }

    int i, j, k;

    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
        case _CS_:
        case _GA_:
        case _BHA_:
        case _WCA_:
        case _MBO_:
        case _ABC_:
        case _BSO_:
        case _BSA_:
        case _JADE_:
        case _COBIDE_:
        case _ABO_:
        case _HS_:
            for (i = 0; i < s->m; i++){
                for (j = 0; j < s->n; j++)
                    s->a[i]->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
            }
            break;
        case _GP_:
            for (i = 0; i < s->n_terminals; i++){
                for (j = 0; j < s->n; j++){
                    if (s->is_integer_opt)
                        s->a[i]->x[j] = round(GenerateUniformRandomNumber(s->LB[j], s->UB[j]));
                    else
                        s->a[i]->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
                }
            }
            break;
        case _TGP_:
            for (i = 0; i < s->n_terminals; i++){
                for (j = 0; j < s->n; j++){
                    for (k = 0; k < s->tensor_dim; k++)
                        s->a[i]->t[j][k] = GenerateUniformRandomNumber(0, 1);
                    s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], s->tensor_dim);
                    if (s->is_integer_opt) s->a[i]->x[j] = round(s->a[i]->x[j]);
                }
            }
            break;
        case _LOA_:
            for (k = 0; k < s->n; k++){
                for (i = 0; i < s->n_female_nomads; i++)
                    s->female_nomads[i]->x[k] = GenerateUniformRandomNumber(s->LB[k], s->UB[k]);
                for (i = 0; i < s->n_male_nomads; i++)
                    s->male_nomads[i]->x[k] = GenerateUniformRandomNumber(s->LB[k], s->UB[k]);
                for (i = 0; i < s->n_prides; i++){
                    for (j = 0; j < s->pride_id[i].n_females; j++)
                        s->pride_id[i].females[j]->x[k] = GenerateUniformRandomNumber(s->LB[k], s->UB[k]);
                    for (j = 0; j < s->pride_id[i].n_males; j++)
                        s->pride_id[i].males[j]->x[k] = GenerateUniformRandomNumber(s->LB[k], s->UB[k]);
                }
            }
            break;
        case _SA_:
            /* Here we define the area that each agent will seach */
            /* for each decision variable */
            for (i = 0; i < s->n; i++)
            {
              double increment = (s->UB[i] - s->LB[i]) / s->m;
              /* the first agent */
              s->a[0]->LB[i] = s->LB[i];
              s->a[0]->UB[i] = s->LB[i] + increment;
              /* Generation random initial position */
              s->a[0]->x[i] = GenerateUniformRandomNumber(s->a[0]->LB[i], s->a[0]->UB[i]);
              /* for each agent */
              for (j = 1; j < s->m; j++)
              {
                s->a[j]->LB[i] = s->a[j - 1]->UB[i]; /* lower bound of the agent starts at the upper bound of the previous agent. */
                s->a[j]->UB[i] = s->a[j]->LB[i] + increment;

                /* Generation random initial position */
                s->a[j]->x[i] = GenerateUniformRandomNumber(s->a[j]->LB[i], s->a[j]->UB[i]);
              }
            }
            break;
    }
}

/* It shows a search space
Parameters:
s: search space
opt_id: identifier of the optimization technique */
void ShowSearchSpace(SearchSpace *s, int opt_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @ShowSearchSpace.\n");
        exit(-1);
    }

    int i, j, k;
    fprintf(stderr, "\nSearch space with %d agents and %d decision variables\n", s->m, s->n);

    switch (opt_id)
    {
    case _PSO_:
    case _BA_:
    case _FPA_:
    case _FA_:
    case _CS_:
    case _GA_:
    case _BHA_:
    case _WCA_:
    case _ABC_:
    case _BSO_:
    case _JADE_:
    case _COBIDE_:
    case _ABO_:
    case _HS_:
        for (i = 0; i < s->m; i++)
        {
            fprintf(stderr, "\nAgent %d-> ", i);
            for (j = 0; j < s->n; j++)
                fprintf(stderr, "x[%d]: %f   ", j, s->a[i]->x[j]);
            fprintf(stderr, "fitness value: %f", s->a[i]->fit);
        }
        break;

    case _SA_:
      for (i = 0; i < s->m; i++)
      {
          fprintf(stderr, "\nAgent %d-> ", i);
          for (j = 0; j < s->n; j++)
              fprintf(stderr, "\nx[%d]: %f   ", j, s->a[i]->x[j]);
          fprintf(stderr, "\nBoundaries");
          for (j = 0; j < s->n; j++)
              fprintf(stderr, "\nUB[%d]: %.2f, LB[%d]: %.2f", j, s->a[i]->UB[j], j, s->a[i]->LB[j]);
          fprintf(stderr, "\nfitness value: %f", s->a[i]->fit);
      }
      break;
    case _GP_:
        for (i = 0; i < s->m; i++)
            fprintf(stderr, "\nAgent %d-> fitness value %lf", i, s->tree_fit[i]);
        break;
    case _MBO_:
        for (i = 0; i < s->m; i++)
        {
            fprintf(stderr, "\nAgent %d-> ", i);
            for (j = 0; j < s->n; j++)
                fprintf(stderr, "x[%d]: %f   ", j, s->a[i]->x[j]);
            fprintf(stderr, "fitness value: %f", s->a[i]->fit);

            if (s->a[i]->nb[0] != NULL)
            { /* It shows the neighbours */
                for (k = 0; k < s->k; k++)
                { /* Leader has k neighbours*/
                    fprintf(stderr, "\n\tNeighbour %d-> ", k);
                    for (j = 0; j < s->n; j++)
                        fprintf(stderr, "x[%d]: %f   ", j, s->a[i]->nb[k]->x[j]);
                    fprintf(stderr, "fitness value: %f", s->a[i]->nb[k]->fit);
                }
                fprintf(stderr, "\n");
            }
        }
        break;
    case _LOA_:
        fprintf(stderr, "\nNomad Females:");
        for (i = 0; i < s->n_female_nomads; i++)
        {
            fprintf(stderr, "\n\tAgent %d-> ", i);
            for (j = 0; j < s->n; j++)
                fprintf(stderr, "x[%d]: %f   ", j, s->female_nomads[i]->x[j]);
            fprintf(stderr, "fitness value: %f", s->female_nomads[i]->fit);
        }

        fprintf(stderr, "\nNomad Males:");
        for (i = 0; i < s->n_male_nomads; i++)
        {
            fprintf(stderr, "\n\tAgent %d-> ", i);
            for (j = 0; j < s->n; j++)
                fprintf(stderr, "x[%d]: %f   ", j, s->male_nomads[i]->x[j]);
            fprintf(stderr, "fitness value: %f", s->male_nomads[i]->fit);
        }

        fprintf(stderr, "\nIn Prides:");
        for (i = 0; i < s->n_prides; i++)
        {
            fprintf(stderr, "\n\tPride %d: ", i);
            fprintf(stderr, "\n\tResident Males:");
            for (j = 0; j < s->pride_id[i].n_males; j++)
            {
                fprintf(stderr, "\n\t\tAgent %d-> ", j);
                for (k = 0; k < s->n; k++)
                    fprintf(stderr, "x[%d]: %f   ", k, s->pride_id[i].males[j]->x[k]);
                fprintf(stderr, "fitness value: %f", s->pride_id[i].males[j]->fit);
            }
            fprintf(stderr, "\n\tResident Females:");
            for (j = 0; j < s->pride_id[i].n_females; j++)
            {
                fprintf(stderr, "\n\t\tAgent %d-> ", j);
                for (k = 0; k < s->n; k++)
                    fprintf(stderr, "x[%d]: %f   ", k, s->pride_id[i].females[j]->x[k]);
                fprintf(stderr, "fitness value: %f", s->pride_id[i].females[j]->fit);
            }
        }
        break;
    default:
        fprintf(stderr, "\n Invalid optimization identifier @ShowSearchSpace.\n");
        break;
    }
    fprintf(stderr, "\n-----------------------------------------------------\n");
}

/* It evaluates a search space
 * This function only evaluates each agent and sets its best fitness value,
 * as well as it sets the global best fitness value and agent.
Parameters:
s: search space
EvaluateFun: pointer to the function used to evaluate particles (agents)
arg: list of additional arguments */
void EvaluateSearchSpace(SearchSpace *s, int opt_id, prtFun Evaluate, va_list arg)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @EvaluateSearchSpace.\n");
        exit(-1);
    }

    int i, j;
    double f, **t_tmp = NULL, *tmp = NULL;
    Agent *individual = NULL;
    va_list argtmp;

    va_copy(argtmp, arg);

    switch (opt_id)
    {
    case _BA_:
    case _FPA_:
    case _CS_:
    case _GA_:
    case _BHA_:
    case _WCA_:
    case _ABC_:
    case _HS_:
    case _BSA_:
    case _JADE_:
    case _COBIDE_:
    case _ABO_:
    case _BSO_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            if (f < s->a[i]->fit) /* It updates the fitness value */
                s->a[i]->fit = f;

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->best = i;
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                    s->g[j] = s->a[i]->x[j];
            }

            va_copy(arg, argtmp);
        }
        break;
    case _PSO_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            if (f < s->a[i]->fit)
            { /* It updates the local best value and position */
                s->a[i]->fit = f;
                for (j = 0; j < s->n; j++)
                    s->a[i]->xl[j] = s->a[i]->x[j];
            }

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                    s->g[j] = s->a[i]->x[j];
            }

            va_copy(arg, argtmp);
        }
        break;
    case _FA_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            s->a[i]->fit = f; /* It updates the fitness value of actual agent i */

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                    s->g[j] = s->a[i]->x[j];
            }

            va_copy(arg, argtmp);
        }
        break;
    case _GP_:
        individual = CreateAgent(s->n, _GP_, _NOTENSOR_);
        for (i = 0; i < s->m; i++)
        {
            tmp = RunTree(s, s->T[i]);
            memcpy(individual->x, tmp, s->n * sizeof(double)); /* It runs over a tree computing the output individual (current solution) */
            free(tmp);

            CheckAgentLimits(s, individual);

            f = Evaluate(individual, arg); /* It executes the fitness function for agent i */

            if (f < s->tree_fit[i]) /* It updates the fitness value */
                s->tree_fit[i] = f;

            if (s->tree_fit[i] < s->gfit)
            { /* It updates the global best value */
                s->best = i;
                s->gfit = s->tree_fit[i];
                for (j = 0; j < s->n; j++)
                    s->g[j] = individual->x[j];
            }

            va_copy(arg, argtmp);
        }
        DestroyAgent(&individual, _GP_);
        break;
    case _TGP_:
        individual = CreateAgent(s->n, _TGP_, s->tensor_dim);
        tmp = (double *)calloc(s->n, sizeof(double));
        for (i = 0; i < s->m; i++){
            t_tmp = RunTTree(s, s->T[i]);
            CheckTensorLimits(s, t_tmp, s->tensor_dim);
    
            for(j = 0; j < s->n; j++)
                tmp[j] = TensorSpan(s->LB[j], s->UB[j], t_tmp[j], s->tensor_dim);
            memcpy(individual->x, tmp, s->n * sizeof(double)); /* It runs over a tree computing the output individual (current solution) */
            DestroyTensor(&t_tmp, s->n);
        
            CheckAgentLimits(s, individual);

            f = Evaluate(individual, arg); /* It executes the fitness function for agent i */
            if (f < s->tree_fit[i]) /* It updates the fitness value */
                s->tree_fit[i] = f;

            /* It updates the global best value */
            if (s->tree_fit[i] < s->gfit){ 
                s->best = i;
                s->gfit = s->tree_fit[i];
                for (j = 0; j < s->n; j++)
                    s->g[j] = individual->x[j];
            }

            va_copy(arg, argtmp);
        }
        DestroyAgent(&individual, _TGP_);
        free(tmp);
        break;
    case _MBO_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */
            s->a[i]->fit = f;           /* It updates the fitness value of actual agent i */

            va_copy(arg, argtmp);
        }
        break;
    case _LOA_:
        for (i = 0; i < s->n_female_nomads; i++)
        {
            EvaluateAgent(s, s->female_nomads[i], _LOA_, Evaluate, arg);
            /* after the firt evaluation pfit still is DBL_MAX, we need to update it */
            s->female_nomads[i]->pfit = s->female_nomads[i]->fit;
        }
        for (i = 0; i < s->n_male_nomads; i++)
        {
            EvaluateAgent(s, s->male_nomads[i], _LOA_, Evaluate, arg);
            /* after the firt evaluation pfit still is DBL_MAX, we need to update it */
            s->male_nomads[i]->pfit = s->male_nomads[i]->fit;
        }
        for (i = 0; i < s->n_prides; i++)
        {
            for (j = 0; j < s->pride_id[i].n_females; j++)
            {
                EvaluateAgent(s, s->pride_id[i].females[j], _LOA_, Evaluate, arg);
                /* after the firt evaluation pfit still is DBL_MAX, we need to update it */
                s->pride_id[i].females[j]->pfit = s->pride_id[i].females[j]->fit;
            }
            for (j = 0; j < s->pride_id[i].n_males; j++)
            {
                EvaluateAgent(s, s->pride_id[i].males[j], _LOA_, Evaluate, arg);
                /* after the firt evaluation pfit still is DBL_MAX, we need to update it */
                s->pride_id[i].males[j]->pfit = s->pride_id[i].males[j]->fit;
            }
        }
        break;

    case _SA_:
      for (i = 0; i < s->m; i++)
        EvaluateAgent(s, s->a[i], _SA_, Evaluate, arg); /* It executes the fitness function for agent i */
      break;
    default:
        fprintf(stderr, "\n Invalid optimization identifier @EvaluateSearchSpace.\n");
        break;
    }
}

/* It checks whether a search space has been properly set or not
Parameters:
s: initialized search space
opt_id: identifier of the optimization technique */
char CheckSearchSpace(SearchSpace *s, int opt_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @CheckSearchSpace.\n");
        return 0;
    }

    char OK = 1;

    fprintf(stderr, "\nError summary: ");
    switch (opt_id)
    {
    case _PSO_:
        if (isnan((float)s->w))
        {
            fprintf(stderr, "\n  -> Inertia weight undefined.");
            OK = 0;
        }
        if (isnan((float)s->w_min))
        {
            fprintf(stderr, "\n  -> Minimum inertia weight undefined.");
            OK = 0;
        }
        if (isnan((float)s->w_max))
        {
            fprintf(stderr, "\n  -> Maximum inertia weight undefined.");
            OK = 0;
        }
        if (isnan((float)s->c1))
        {
            fprintf(stderr, "\n  -> C1 parameter undefined.");
            OK = 0;
        }
        if (isnan((float)s->c2))
        {
            fprintf(stderr, "\n  -> C2 parameter undefined.");
            OK = 0;
        }
        break;
    case _BA_:
        if (isnan((float)s->f_min))
        {
            fprintf(stderr, "\n  -> Minimum frequency undefined.");
            OK = 0;
        }
        if (isnan((float)s->f_max))
        {
            fprintf(stderr, "\n  -> Maximum frequency undefined.");
            OK = 0;
        }
        if (isnan((float)s->r))
        {
            fprintf(stderr, "\n  -> Pulse rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->A))
        {
            fprintf(stderr, "\n  -> Loudness undefined.");
            OK = 0;
        }
        break;
    case _FPA_:
        if (isnan((float)s->beta))
        {
            fprintf(stderr, "\n  -> Beta parameter used to compute the step based on Levy Flight undefined.");
            OK = 0;
        }
        if (isnan((float)s->p))
        {
            fprintf(stderr, "\n  -> Probability of local pollination undefined.");
            OK = 0;
        }
        break;
    case _FA_:
        if (isnan((float)s->alpha))
        {
            fprintf(stderr, "\n  -> Randomized parameter undefined.");
            OK = 0;
        }
        if (isnan((float)s->beta_0))
        {
            fprintf(stderr, "\n  -> Attractiveness undefined.");
            OK = 0;
        }
        if (isnan((float)s->gamma))
        {
            fprintf(stderr, "\n  -> Light absorption undefined.");
            OK = 0;
        }
        break;
    case _CS_:
        if (isnan((float)s->beta))
        {
            fprintf(stderr, "\n  -> Beta parameter used to compute the step based on Levy Flight undefined.");
            OK = 0;
        }
        if (isnan((float)s->p))
        {
            fprintf(stderr, "\n  -> Switch probability undefined.");
            OK = 0;
        }
        if (isnan((float)s->alpha))
        {
            fprintf(stderr, "\n  -> Step size undefined.");
            OK = 0;
        }
        break;
    case _GP_:
    case _TGP_:
    case _GA_:
        if (isnan((float)s->pMutation))
        {
            fprintf(stderr, "\n  -> Probability of mutation undefined.");
            OK = 0;
        }
        break;
    case _BHA_:
        break;
    case _WCA_:
        if (s->nsr == 0)
        {
            fprintf(stderr, "\n  -> Number of rivers undefined.");
            OK = 0;
        }
        if (isnan((float)s->dmax))
        {
            fprintf(stderr, "\n  -> Raining process maximum distance undefined.");
            OK = 0;
        }
        break;
    case _MBO_:
        if (s->k == 0)
        {
            fprintf(stderr, "\n  -> Number of neighbours solutions to be considered undefined.");
            OK = 0;
        }
        if (s->X == 0)
        {
            fprintf(stderr, "\n  -> Number of neighbour solutions to be shared with the next solution undefined.");
            OK = 0;
        }
        if (s->M == 0)
        {
            fprintf(stderr, "\n  -> Number of tours undefined.");
            OK = 0;
        }
        if (s->X >= s->k)
        {
            fprintf(stderr, "\n  -> Number of neighbour shared should be smaller than the number of neighbours considered.");
            OK = 0;
        }
        if (s->m < 3)
        {
            fprintf(stderr, "\n  -> Number of birds should be bigger than or equal to 3.");
            OK = 0;
        }
        break;
    case _ABC_:
        if (s->limit == 0)
        {
            fprintf(stderr, "\n  -> Number of trial limits must be greater than 0.");
            OK = 0;
        }
        break;
    case _HS_:
        if (isnan((float)s->HMCR))
        {
            fprintf(stderr, "\n  -> Harmony Memory Considering Rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->PAR))
        {
            fprintf(stderr, "\n  -> Pitch Adjusting Rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->PAR_min))
        {
            fprintf(stderr, "\n  -> Minimum Pitch Adjusting Rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->PAR_max))
        {
            fprintf(stderr, "\n  -> Maximum Pitch Adjusting Rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->bw))
        {
            fprintf(stderr, "\n  -> Bandwidth undefined.");
            OK = 0;
        }
        if (isnan((float)s->bw_min))
        {
            fprintf(stderr, "\n  -> Minimum Bandwidth undefined.");
            OK = 0;
        }
        if (isnan((float)s->bw_max))
        {
            fprintf(stderr, "\n  -> Maximum Bandwidth undefined.");
            OK = 0;
        }
        break;
    case _BSO_:
        if (isnan((float)s->k) || (s->k < 1))
        {
            fprintf(stderr, "\n  -> Number of clusters undefined or invalid.");
            OK = 0;
        }
        if (isnan((float)s->p_one_cluster))
        {
            fprintf(stderr, "\n  -> Probability of selecting a cluster center undefined.");
            OK = 0;
        }
        if (isnan((float)s->p_one_center))
        {
            fprintf(stderr, "\n  -> Probability of randomly selecting an idea from a probabilistic selected cluster undefined.");
            OK = 0;
        }
        if (isnan((float)s->p_two_centers))
        {
            fprintf(stderr, "\n  -> Probability of of creating a random combination of two probabilistic selected clusters undefined.");
            OK = 0;
        }
        break;
    case _LOA_:
        if (isnan((float)s->sex_rate))
        {
            fprintf(stderr, "\n  -> Sex rate undefined.");
            OK = 0;
        }
        if (isnan((float)s->nomad_percent))
        {
            fprintf(stderr, "\n  -> Nomad percentage undefined.");
            OK = 0;
        }
        if (isnan((float)s->roaming_percent))
        {
            fprintf(stderr, "\n  -> Roaming percentage undefined.");
            OK = 0;
        }
        if (isnan((float)s->mating_prob))
        {
            fprintf(stderr, "\n  -> Mating probability undefined.");
            OK = 0;
        }
        if (isnan((float)s->imigration_rate))
        {
            fprintf(stderr, "\n  -> Imigration rate undefined.");
            OK = 0;
        }
        if (s->n_prides <= 0)
        {
            fprintf(stderr, "\n  -> Number of prides not valid.");
            OK = 0;
        }
        if (isnan(s->pMutation))
        {
            fprintf(stderr, "\n  -> Mutation probability undefined.");
            OK = 0;
        }
        break;
    case _BSA_:
        if (isnan((float)s->mix_rate))
        {
            fprintf(stderr, "\n  -> Mix Rate undefined.");
            OK = 0;
        }
        if (s->F <= 0)
        {
            fprintf(stderr, "\n  -> F undefined.");
            OK = 0;
        }

        break;
    case _JADE_:
        if (isnan((float)s->c))
        {
            fprintf(stderr, "\n  -> c undefined.");
            OK = 0;
        }
        if (isnan((float)s->p_greediness))
        {
            fprintf(stderr, "\n  -> p undefined.");
            OK = 0;
        }

        break;
    case _COBIDE_:
        if (isnan((float)s->pb))
        {
            fprintf(stderr, "\n  -> pb undefined.");
            OK = 0;
        }
        if (isnan((float)s->ps))
        {
            fprintf(stderr, "\n  -> ps undefined.");
            OK = 0;
        }

        break;
    case _ABO_:
        if (isnan((float)s->ratio_e))
        {
            fprintf(stderr, "\n  -> proportion of sunspot butterflies undefined.");
            OK = 0;
        }
        if (isnan((float)s->step_e))
        {
            fprintf(stderr, "\n -> step parameter undefined.");
            OK = 0;
        }
    case _SA_:
      if ((s->cooling_schedule_id < 0) || (s->cooling_schedule_id > TOTAL_COOLING_SCHEDULES))
      {
        fprintf(stderr, "\n  -> Undefined Cooling Schedule. @CheckSearchSpace.\n");
        OK = 0;
      }
      if (isnan(s->end_temperature))
      {
        fprintf(stderr, "\n  -> Undefined End Temperature. @CheckSearchSpace.\n");
        OK = 0;
      }
        break;
    default:
        fprintf(stderr, "\n Invalid optimization identifier @CheckSearchSpace.\n");
        return 0;
        break;
    }
    if (s->iterations <= 0)
    {
        fprintf(stderr, "\nNumber of iterations undefined or less than 0.\n");
        OK = 0;
    }

    if (OK)
        fprintf(stderr, "\nNo errors were found! Enjoy it!\n");

    return OK;
}

/**************************/

/* General-purpose functions */
/* It generates a random number uniformly distributed between low and high
Parameters:
low: lower bound
high: upper bound
This algorithm has been inspired by: http://www.cprogramming.com/tutorial/random.html */
double GenerateUniformRandomNumber(double low, double high)
{
    return randinter(low, high);
}

/* It generates a random number drawn from a Gaussian (normal) distribution
Parameters:
mean: mean of the distribution
variance: variance of the distribution */
double GenerateGaussianRandomNumber(double mean, double variance)
{
    return randGaussian(mean, variance);
}

/* It generates a random number drawn from a Cauchy distribution
Parameters:
location: location of the distribution
scale: scale of the distribution */
double GenerateCauchyRandomNumber(double location, double scale)
{
	return randCauchy(location,scale);
}

/* It generates an n-dimensional array drawn from a Levy distribution
 * The formulation used here is based on the paper "Multiobjective Cuckoo Search for Design Optimization", X.-S. Yang and S. Deb, Computers & Operations Research, 2013.
Parameters:
n: dimension of the output array
beta: input parameter used in the formulation */
double *GenerateLevyDistribution(int n, double beta)
{
    double *L = NULL, sigma_u, sigma_v = 1;
    double *u = NULL, *v = NULL;
    int i;

    if (n < 1)
    {
        fprintf(stderr, "Invalid input paramater @GenerateLevyDistribution.\n");
        return NULL;
    }

    L = (double *)malloc(n * sizeof(double));

    sigma_u = pow((tgamma(1 + beta) * sin(M_PI * beta / 2)) / (tgamma((1 + beta) / 2) * beta * pow(2, (beta - 1) / 2)), 1 / beta); /* Equation 16 */

    u = (double *)malloc(n * sizeof(double));
    v = (double *)malloc(n * sizeof(double));
    sigma_u = pow(sigma_u, 2);
    for (i = 0; i < n; i++)
    { /* It computes Equation 15 */
        u[i] = GenerateGaussianRandomNumber(0, sigma_u);
        v[i] = GenerateGaussianRandomNumber(0, sigma_v);
    }

    for (i = 0; i < n; i++)
        L[i] = 0.01 * (u[i] / pow(fabs(v[i]), 1 / beta)); /* It computes Equation 14 (part of it) */

    free(u);
    free(v);

    return L;
}

/* It computes the Euclidean distance between two n-dimensional arrays
Parameters:
x: n-dimension array
y: n-dimension array */
double EuclideanDistance(double *x, double *y, int n)
{
    double sum = 0.0;
    int i;

    for (i = 0; i < n; i++)
        sum += pow(x[i] - y[i], 2);

    return sqrt(sum);
}

/* It generates a perpendicular vector to a given vector
Parameters:
x: n-dimension array
n: dimension of vector */
double *GetPerpendicularVector(double *x, int n)
{
    int i;
    double *perp_vector = (double *)calloc(n, sizeof(double));

    for (i = 0; i < n - 1; i += 2)
    {
        perp_vector[i] = -1 * x[i + 1];
        perp_vector[i + 1] = x[i];
    }

    return perp_vector;
}

/* It normalizes a given vector
Parameters:
x: n-dimension array
n: dimension of vector */
void NormalizeVector(double *x, int n)
{
    int i;
    double magnitude = 0;

    for (i = 0; i < n; i++)
        magnitude += x[i] * x[i];

    magnitude = sqrt(magnitude);

    for (i = 0; i < n; i++)
        x[i] = x[i] / magnitude;
}

/* It is used to sort by agent's fitness (asceding order of fitness) */
int SortAgent(const void *a, const void *b)
{
    const Agent *x = *(Agent **)a, *y = *(Agent **)b;

    if (x->fit != y->fit)
        if (x->fit > y->fit)
            return 1;
        else
            return -1;
    else
        return 0;
}

/* It is used to sort an array of Data by asceding order of the variable val */
int SortDataByVal(const void *a, const void *b)
{
    const Data *x = (Data *)a, *y = (Data *)b;

    if (x->val != y->val)
        if (x->val > y->val)
            return 1;
        else
            return -1;
    else
        return 0;
}

/* It waives a comment in a model file
Parameters:
fp = file pointer */
void WaiveComment(FILE *fp)
{
    char c;

    fscanf(fp, "%c", &c);
    while ((c != '\n') && (!feof(fp)))
        fscanf(fp, "%c", &c);
}

/* It loads a search space with parameters specified in a file
Parameters:
fileName: path to the file that contains the parameters of the search space
opt_id: identifier of the optimization technique */
SearchSpace *ReadSearchSpaceFromFile(char *fileName, int opt_id){
    FILE *fp = NULL;
    SearchSpace *s = NULL;
    int i, j, m, n, k, iterations, n_terminals = 0, n_functions = 0, min_depth, max_depth;
    int has_constant = 0, is_integer_opt, same_range;
    double pReproduction, pMutation, pCrossover, **constant = NULL, *LB = NULL, *UB = NULL;
    double ***t_constant = NULL, sex_rate, nomad_percent, roaming_percent, mating_prob, imigration_rate;
    int n_prides, tensor_dim = -1;
    char line[LINE_SIZE], *pline = NULL, **function = NULL, **terminal = NULL;
    Node *head = NULL, *tail = NULL, *aux = NULL;

    char cooling_schedule_name[256]; /* SA - to hold the string coming from the file*/

    fp = fopen(fileName, "r");
    if (!fp){
        fprintf(stderr, "\nUnable to open file %s @ReadSearchSpaceFromFile.\n", fileName);
        return NULL;
    }

    if(opt_id != _TGP_) fscanf(fp, "%d %d %d", &m, &n, &iterations);
    else fscanf(fp, "%d %d %d %d", &m, &n, &iterations, &tensor_dim);
    WaiveComment(fp);
    
    switch (opt_id){
        case _PSO_:
            s = CreateSearchSpace(m, n, _PSO_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->c1), &(s->c2));
            WaiveComment(fp);
            fscanf(fp, "%lf %lf %lf", &(s->w), &(s->w_min), &(s->w_max));
            WaiveComment(fp);
            break;
        case _BA_:
            s = CreateSearchSpace(m, n, _BA_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->f_min), &(s->f_max));
            WaiveComment(fp);
            fscanf(fp, "%lf %lf", &(s->A), &(s->r));
            WaiveComment(fp);
            break;
        case _FPA_:
            s = CreateSearchSpace(m, n, _FPA_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->beta), &(s->p));
            WaiveComment(fp);
            break;
        case _FA_:
            s = CreateSearchSpace(m, n, _FA_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf %lf", &(s->alpha), &(s->beta_0), &(s->gamma));
            WaiveComment(fp);
            break;
        case _CS_:
            s = CreateSearchSpace(m, n, _CS_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf %lf", &(s->beta), &(s->p), &(s->alpha));
            WaiveComment(fp);
            break;
        case _GA_:
            s = CreateSearchSpace(m, n, _GA_);
            s->iterations = iterations;
            fscanf(fp, "%lf", &(s->pMutation));
            WaiveComment(fp);
            break;
        case _BHA_:
            s = CreateSearchSpace(m, n, _BHA_);
            s->iterations = iterations;
            break;
        case _WCA_:
            s = CreateSearchSpace(m, n, _WCA_);
            s->iterations = iterations;
            fscanf(fp, "%d %lf", &(s->nsr), &(s->dmax));
            WaiveComment(fp);
            break;
        case _MBO_:
            fscanf(fp, "%d", &k);
            s = CreateSearchSpace(m, n, _MBO_, k);
            s->iterations = iterations;
            fscanf(fp, "%d %d", &(s->X), &(s->M));
            WaiveComment(fp);
            break;
        case _ABC_:
            s = CreateSearchSpace(m, n, _ABC_);
            s->iterations = iterations;
            fscanf(fp, "%d", &(s->limit));
            WaiveComment(fp);
            break;
        case _HS_:
            s = CreateSearchSpace(m, n, _HS_);
            s->iterations = iterations;
            fscanf(fp, "%lf", &(s->HMCR));
            WaiveComment(fp);
            fscanf(fp, "%lf %lf %lf", &(s->PAR), &(s->PAR_min), &(s->PAR_max));
            WaiveComment(fp);
            fscanf(fp, "%lf %lf %lf", &(s->bw), &(s->bw_min), &(s->bw_max));
            WaiveComment(fp);
            break;
        case _BSO_:
            s = CreateSearchSpace(m, n, _BSO_);
            s->iterations = iterations;
            fscanf(fp, "%d", &(s->k));
            WaiveComment(fp);
            fscanf(fp, "%lf %lf %lf", &(s->p_one_cluster), &(s->p_one_center), &(s->p_two_centers));
            WaiveComment(fp);
            break;
        case _GP_:
        case _TGP_:
            fscanf(fp, "%lf %lf %lf", &pReproduction, &pMutation, &pCrossover);
            WaiveComment(fp);
            fscanf(fp, "%d %d", &min_depth, &max_depth);
            WaiveComment(fp);

            /* Loading function nodes */
            fgets(line, LINE_SIZE, fp);
            pline = strtok(line, " \t");
            j = 0;
            while ((pline) && (*pline != '#')){
                aux = CreateNode(pline, 0, 0);

                if (!head) head = aux;
                else tail->right = aux;
                tail = aux;

                n_functions++;
                pline = strtok(NULL, " \t");
            }

            function = (char **)malloc(n_functions * sizeof(char *));
            for (j = 0; j < n_functions; j++)
                function[j] = (char *)malloc(TERMINAL_LENGTH * sizeof(char));

            j = 0;
            aux = head;
            while (aux){
                strcpy(function[j++], aux->elem);
                aux = aux->right;
            }   
            DestroyTree(&head);
            /*****************************/

            /* Loading terminal nodes */
            fgets(line, LINE_SIZE, fp);
            pline = strtok(line, " \t");
            j = 0;
            while ((pline) && (*pline != '#')){
                aux = CreateNode(pline, 0, 0);
                if (!strcmp(pline, "CONST")) has_constant = 1;

                if (!head) head = aux;
                else
                    tail->right = aux;
                tail = aux;

                n_terminals++;
                pline = strtok(NULL, " \t");
            }

            terminal = (char **)malloc(n_terminals * sizeof(char *));
            for (j = 0; j < n_terminals; j++)
                terminal[j] = (char *)malloc(TERMINAL_LENGTH * sizeof(char));

            j = 0;
            aux = head;
            while (aux){
                strcpy(terminal[j++], aux->elem);
                aux = aux->right;
            }
            DestroyTree(&head);
            /*****************************/

            fscanf(fp, "%d %d", &is_integer_opt, &same_range);
            WaiveComment(fp);

            /* loading lower and upper bounds */
            LB = (double *)malloc(n * sizeof(double));
            UB = (double *)malloc(n * sizeof(double));

            if (same_range){
                for (j = 0; j < n; j++){
                    fscanf(fp, "%lf %lf", &(LB[j]), &(UB[j]));
                    WaiveComment(fp);
                }   
            }
            else{
                fscanf(fp, "%lf %lf", &(LB[0]), &(UB[0]));
                WaiveComment(fp);
                for (j = 1; j < n; j++){
                    LB[j] = LB[0];
                    UB[j] = UB[0];
                }   
            }
            /* loading constants */
            if (has_constant){
                if(opt_id == _GP_){
                    constant = (double **)malloc(n * sizeof(double *));
                    for (j = 0; j < n; j++)
                        constant[j] = (double *)malloc(N_CONSTANTS * sizeof(double));

                    for (i = 0; i < n; i++)
                        for (j = 0; j < N_CONSTANTS; j++)
                            constant[i][j] = GenerateUniformRandomNumber(LB[i], UB[i]);
                            
                }else{ /* tensor-based GP */
                    /* here we generate N_CONSTANTS random matrices within the range [0,1] */
                    t_constant = (double ***)malloc(N_CONSTANTS * sizeof(double **));
                    for(i = 0; i < N_CONSTANTS; i++){
                        t_constant[i] = (double **)malloc(n * sizeof(double *));
                        for (j = 0; j < n; j++)
                            t_constant[i][j] = (double *)malloc(tensor_dim * sizeof(double));
                    }
                    
                    for (i = 0; i < N_CONSTANTS; i++)
                        for (j = 0; j < n; j++)
                            for (k = 0; k < tensor_dim; k++)
                                t_constant[i][j][k] = GenerateUniformRandomNumber(0, 1);
                            
                }
            }
            /*********************/
            fprintf(stderr,"\nFLAG 1");
            if(opt_id == _GP_) s = CreateSearchSpace(m, n, _GP_, min_depth, max_depth, n_terminals, N_CONSTANTS, n_functions, terminal, constant, function);
            else s = CreateSearchSpace(m, n, _TGP_, min_depth, max_depth, n_terminals, N_CONSTANTS, n_functions, terminal, t_constant, function, tensor_dim);
            fprintf(stderr,"\nFLAG 2");
            
            s->iterations = iterations;
            s->pReproduction = pReproduction;
            s->pMutation = pMutation;
            s->pCrossover = pCrossover;
            s->is_integer_opt = is_integer_opt;
            s->tensor_dim = tensor_dim;

            for (j = 0; j < s->n; j++){
                s->LB[j] = LB[j];
                s->UB[j] = UB[j];
            }
            free(LB);
            free(UB);
            break;
        case _LOA_:
            fscanf(fp, "%lf %lf %lf %lf %lf %lf %d", &sex_rate, &nomad_percent, &roaming_percent, &mating_prob, &pMutation, &imigration_rate, &n_prides);
            s = CreateSearchSpace(m, n, _LOA_, sex_rate, nomad_percent, roaming_percent, mating_prob, pMutation, imigration_rate, n_prides);
            s->iterations = iterations;
            WaiveComment(fp);
            break;
        case _BSA_:
            s = CreateSearchSpace(m, n, _BSA_);
            s->iterations = iterations;
            fscanf(fp, "%lf %d", &(s->mix_rate), &(s->F));
            WaiveComment(fp);
            break;
         case _JADE_:
            s = CreateSearchSpace(m, n, _JADE_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->c), &(s->p_greediness));
            WaiveComment(fp);
            break;
         case _COBIDE_:
            s = CreateSearchSpace(m, n, _COBIDE_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->pb), &(s->ps));
            WaiveComment(fp);
            break;
         case _ABO_:
            s = CreateSearchSpace(m, n, _ABO_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->ratio_e), &(s->step_e));
            WaiveComment(fp);
            break;
         case _SA_:
            s = CreateSearchSpace(m, n, _SA_);
            s->iterations = iterations;
            fscanf(fp, "%lf %lf", &(s->init_temperature), &(s->end_temperature));
            WaiveComment(fp);
            fscanf(fp, "%s %lf", cooling_schedule_name, &(s->func_param));
            WaiveComment(fp);
            s->cooling_schedule_id = getCoolingScheduleId(cooling_schedule_name);
            break;
        default:
            fprintf(stderr, "\nInvalid optimization identifier @ReadSearchSpaceFromFile.\n");
            break;
    }

    if ((opt_id != _GP_) && (opt_id != _TGP_)){
        for (j = 0; j < s->n; j++){
            fscanf(fp, "%lf %lf", &(s->LB[j]), &(s->UB[j]));
            WaiveComment(fp);
        }
    }

    fclose(fp);

    return s;
}

/* It returns the identifier of the function used as input
Parameters:
s: string with the function node description */
int getFUNCTIONid(char *s)
{
    if (!strcmp(s, "SUM"))
        return _SUM_;
    else if (!strcmp(s, "SUB"))
        return _SUB_;
    else if (!strcmp(s, "MUL"))
        return _MUL_;
    else if (!strcmp(s, "DIV"))
        return _DIV_;
    else if (!strcmp(s, "EXP"))
        return _EXP_;
    else if (!strcmp(s, "SQRT"))
        return _SQRT_;
    else if (!strcmp(s, "LOG"))
        return _LOG_;
    else if (!strcmp(s, "ABS"))
        return _ABS_;
    else if (!strcmp(s, "AND"))
        return _AND_;
    else if (!strcmp(s, "OR"))
        return _OR_;
    else if (!strcmp(s, "XOR"))
        return _XOR_;
    else if (!strcmp(s, "NOT"))
        return _NOT_;
    else if (!strcmp(s, "TSUM"))
        return _TSUM_;
    else if (!strcmp(s, "TSUB"))
        return _TSUB_;
    else if (!strcmp(s, "TMUL"))
        return _TMUL_;
    else if (!strcmp(s, "TDIV"))
        return _TDIV_;
    else
    {
        fprintf(stderr, "\nUndefined function @getFUNCTIONid.");
        exit(-1);
    }
}

/* It selects k elements based on the roulette selection method.
 * The output is an array with the indices of the selected elements.
Parameters:
s: search space
k: number of elements to be selected */
int *RouletteSelection(SearchSpace *s, int k)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @RouletteSelection.\n");
        return NULL;
    }

    if (k < 1)
    {
        fprintf(stderr, "\nInvalid input @RouletteSelection.\n");
        return NULL;
    }

    int *elem = NULL, i, j;
    double sum, *accum = NULL, prob;
    Data *D = NULL;

    elem = (int *)malloc(k * sizeof(int));
    D = (Data *)malloc(s->m * sizeof(Data));

    /* It normalizes the fitness of each agent ***/
    sum = 0;
    for (i = 0; i < s->m; i++)
    {
        D[i].id = i;
        D[i].val = 1 / s->tree_fit[i];
        sum += D[i].val;
    }
    for (i = 0; i < s->m; i++)
        D[i].val /= sum;

    /* It sorts the population by ascending values of fitness */
    qsort(D, s->m, sizeof(Data), SortDataByVal);

    /* It computes the accumulate normalized fitness */
    accum = (double *)calloc(s->m, sizeof(double));
    for (i = 0; i < s->m; i++)
    {
        for (j = i; j >= 0; j--)
            accum[i] += D[j].val;
    }

    for (j = 0; j < k; j++)
    {
        /* It picks up the selected individual */
        prob = GenerateUniformRandomNumber(0, 1);
        i = 0;
        while ((accum[i] < prob) && (i < s->m))
            i++;
        if (i)
            elem[j] = D[i - 1].id;
        else
            elem[j] = D[i].id;
        elem[j] = D[i].id;
    }

    free(D);
    free(accum);

    return elem;
}

int *RouletteSelectionGA(SearchSpace *s, int k)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @RouletteSelectionGA.\n");
        return NULL;
    }

    if (k < 1)
    {
        fprintf(stderr, "\nInvalid input @RouletteSelectionGA.\n");
        return NULL;
    }

    int *elem = NULL, i, j;
    double min, sum, *accum = NULL, prob;
    Data *D = NULL;

    elem = (int *)malloc(k * sizeof(int));
    D = (Data *)malloc(s->m * sizeof(Data));

    /* It normalizes the fitness of each agent ***/
    sum = 0;
    min = DBL_MAX;

    for(i = 0; i < s->m; i++)
        min = s->a[i]->fit < min ? s->a[i]->fit : min;

    for (i = 0; i < s->m; i++) {
        D[i].id = i;
        D[i].val = s->a[i]->fit + min != 0 ? ((-2)*min) : 0;
        D[i].val = 1 / D[i].val;
        sum += D[i].val;
    }
    for (i = 0; i < s->m; i++)
        D[i].val /= sum;

    /* It sorts the population by ascending values of fitness */
    qsort(D, s->m, sizeof(Data), SortDataByVal);

    /* It computes the accumulate normalized fitness */
    accum = (double *)calloc(s->m, sizeof(double));
    for (i = 0; i < s->m; i++)
    {
        for (j = i; j >= 0; j--)
            accum[i] += D[j].val;
    }

    for (j = 0; j < k; j++)
    {
        /* It picks up the selected individual */
        prob = GenerateUniformRandomNumber(0, 1);
        i = 0;
        while ((accum[i] < prob) && (i < s->m))
            i++;
        if (i)
            elem[j] = D[i - 1].id;
        else
            elem[j] = D[i].id;
        elem[j] = D[i].id;
    }

    free(D);
    free(accum);

    return elem;
}
/**************************/

/* Tree-related functions */
/* It creates a tree node
Parameters:
value: content of the node
node_id: identifier of the node id, i.e. its position in the array of terminals, functions or constants
status: TERMINAL|FUNCTION|CONSTANT|NEW_TERMINAL
n_decision_variables: only when status = NEW_TERMINAL */
Node *CreateNode(char *value, int node_id, char status, ...)
{
    Node *tmp = NULL;
    tmp = (Node *)malloc(sizeof(Node));
    va_list arg;
    int n_decision_variables;

    if (!value)
    {
        fprintf(stderr, "\nInvalid input @CreateNode.\n");
        return NULL;
    }

    va_start(arg, status);
    n_decision_variables = va_arg(arg, int);

    tmp->id = node_id;
    tmp->left = tmp->right = tmp->parent = NULL;
    tmp->status = status;
    tmp->left_son = 1; /* by default, every node is a left node */
    tmp->elem = (char *)malloc((strlen(value) + 1) * sizeof(char));
    strcpy(tmp->elem, value);

    tmp->val = NULL;
    if (status == NEW_TERMINAL)
        tmp->val = (double *)malloc(n_decision_variables * sizeof(double));

    va_end(arg);

    return tmp;
}

/* It creates a random tree based on the GROW algorithm described in "Two Fast Tree-Creation Algorithms for Genetic Programming", S. Lukw, IEEE Transactions on Evolutionary Computation, 2000.
Parameters:
s: search space
dmin: minimum depth
dmax: maximum depth */
Node *GROW(SearchSpace *s, int min_depth, int max_depth)
{
    int i, aux, const_id;
    Node *tmp = NULL, *node = NULL;

    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @GROW.\n");
        return NULL;
    }

    if (min_depth == max_depth)
    {
        aux = round(GenerateUniformRandomNumber(0, s->n_terminals - 1));
        if (!strcmp(s->terminal[aux], "CONST"))
        {
            const_id = round(GenerateUniformRandomNumber(0, s->n_constants - 1));
            return CreateNode(s->terminal[aux], const_id, CONSTANT);
        }
        return CreateNode(s->terminal[aux], aux, TERMINAL);
    }
    else
    {
        aux = round(GenerateUniformRandomNumber(0, s->n_functions + s->n_terminals - 1));
        if (aux >= s->n_functions)
        { /* If aux is a terminal node */
            aux = aux - s->n_functions;
            if (!strcmp(s->terminal[aux], "CONST"))
            {
                const_id = round(GenerateUniformRandomNumber(0, s->n_constants - 1));
                tmp = CreateNode(s->terminal[aux], const_id, CONSTANT);
            }
            else
                tmp = CreateNode(s->terminal[aux], aux, TERMINAL);
            return tmp;
        }
        else
        { /* The new node is function one */
            node = CreateNode(s->function[aux], aux, FUNCTION);
            for (i = 0; i < N_ARGS_FUNCTION[getFUNCTIONid(s->function[aux])]; i++)
            {
                tmp = GROW(s, min_depth + 1, max_depth);
                if (!i)
                    node->left = tmp;
                else
                {
                    node->right = tmp;
                    tmp->left_son = 0;
                }
                tmp->parent = node;
            }
            return node;
        }
    }
}

/* It deallocates a tree
Parameters:
T: pointer to the tree */
void DestroyTree(Node **T)
{
    if (*T)
    {
        DestroyTree(&(*T)->left);
        DestroyTree(&(*T)->right);
        free((*T)->elem);
        if ((*T)->status == NEW_TERMINAL)
            free((*T)->val);
        free(*T);
        *T = NULL;
    }
}

/* It stores a tree in a text file (prefix mode)
Parameters:
s: search space
T: pointer to the tree
fileName: output file name */
void PrintTree2File(SearchSpace *s, Node *T, char *fileName)
{
    FILE *fp = NULL;

    if (!T)
    {
        fprintf(stderr, "\nTree not allocated @PrintTree2File.\n");
        exit(-1);
    }

    fp = fopen(fileName, "a");
    PreFixPrintTree4File(s, T, fp);
    fprintf(fp, "\n");
    fclose(fp);
}

/* It performs a prefix search in tree and saves the nodes in a text file
Parameters:
s: search space
T: pointer to the tree
fileName: output file name */
void PreFixPrintTree4File(SearchSpace *s, Node *T, FILE *fp)
{
    int j;
    if (T)
    {
        if (T->status != TERMINAL)
            fprintf(fp, "(");
        if (T->status == CONSTANT)
        {
            for (j = 0; j < s->n - 1; j++)
                fprintf(fp, "%lf,", s->constant[j][T->id]);
            fprintf(fp, "%lf", s->constant[j][T->id]);
        }
        else
            fprintf(fp, "%s ", T->elem);
        PreFixPrintTree4File(s, T->left, fp);
        PreFixPrintTree4File(s, T->right, fp);
        if (T->status != TERMINAL)
            fprintf(fp, ")");
    }
}

/* It runs a given tree and outputs its solution array
Parameters:
s: search space
T: current tree */
double *RunTree(SearchSpace *s, Node *T)
{
    double *x = NULL, *y = NULL, *out = NULL;
    int i;

    if (T)
    {
        x = RunTree(s, T->left);  /* It runs over the subtree on the left */
        y = RunTree(s, T->right); /* It runs over the subtree on the right */

        if (T->status == TERMINAL || T->status == CONSTANT || T->status == NEW_TERMINAL)
        {
            out = (double *)calloc(s->n, sizeof(double));
            if (T->status == CONSTANT)
            {
                for (i = 0; i < s->n; i++)
                    out[i] = s->constant[i][T->id];
            }
            else
            {
                if (T->status == NEW_TERMINAL)
                {
                    for (i = 0; i < s->n; i++)
                        out[i] = T->val[i];
                }
                else
                {
                    for (i = 0; i < s->n; i++)
                        out[i] = s->a[T->id]->x[i];
                }
            }
            return out;
        }
        else
        {
            if (!strcmp(T->elem, "SUM"))
                out = f_SUM_(x, y, s->n);
            else if (!strcmp(T->elem, "SUB"))
                out = f_SUB_(x, y, s->n);
            else if (!strcmp(T->elem, "MUL"))
                out = f_MUL_(x, y, s->n);
            else if (!strcmp(T->elem, "DIV"))
                out = f_DIV_(x, y, s->n);
            else if (!strcmp(T->elem, "EXP"))
            {
                if (x)
                    out = f_EXP_(x, s->n);
                else
                    out = f_EXP_(y, s->n);
            }
            else if (!strcmp(T->elem, "SQRT"))
            {
                if (x)
                    out = f_SQRT_(x, s->n);
                else
                    out = f_SQRT_(y, s->n);
            }
            else if (!strcmp(T->elem, "LOG"))
            {
                if (x)
                    out = f_LOG_(x, s->n);
                else
                    out = f_LOG_(y, s->n);
            }
            else if (!strcmp(T->elem, "AND"))
                out = f_AND_(x, y, s->n);
            else if (!strcmp(T->elem, "OR"))
                out = f_OR_(x, y, s->n);
            else if (!strcmp(T->elem, "XOR"))
                out = f_XOR_(x, y, s->n);
            else if (!strcmp(T->elem, "NOT"))
            {
                if (x)
                    out = f_NOT_(x, s->n);
                else
                    out = f_NOT_(y, s->n);
            }
            /* it deallocates the sons of the current one, since they have been used already */
            if (x)
                free(x);
            if (y)
                free(y);
            return out;
        }
    }
    else
        return NULL;
}

/* It copies a given tree
Parameters:
T: tree */
Node *CopyTree(Node *T)
{
    Node *root = NULL;

    if (!T)
    {
        fprintf(stderr, "\nThere is no tree allocated @CopyTree.\n");
        return NULL;
    }
    else
    {
        root = CreateNode(T->elem, T->id, T->status);
        root->left_son = T->left_son;
        PreFixTravel4Copy(T->left, root);
        PreFixTravel4Copy(T->right, root);

        return root;
    }
}

/* It performs a prefix travel on a tree
Parameters:
T: pointer to the subtree on the left
Parent: pointer to the subtree on the right */
void PreFixTravel4Copy(Node *T, Node *Parent)
{
    Node *aux = NULL;
    if (T)
    {
        aux = CreateNode(T->elem, T->id, T->status);
        aux->left_son = T->left_son;
        aux->left = NULL;
        aux->right = NULL;
        if (T->left_son)
            Parent->left = aux;
        else
            Parent->right = aux;
        aux->parent = Parent;

        PreFixTravel4Copy(T->left, aux);
        PreFixTravel4Copy(T->right, aux);
    }
}

/* It returns the size of a tree (number of nodes)
Parameters:
T: pointer to the tree */
int getSizeTree(Node *T)
{
    if (T)
        return 1 + getSizeTree(T->left) + getSizeTree(T->right);
    else
        return 0;
}

/* It performs the mutation of a tree T
Paremeters:
s: search space
T: pointer to the node to be mutated
p: probability of mutation at a function node */
Node *Mutation(SearchSpace *s, Node *T, float p)
{
    if (!s || !T)
    {
        fprintf(stderr, "\nThere is no tree or search space allocated @Mutation.\n");
        return NULL;
    }

    Node *NewTree = NULL, *tmp = NULL, *aux = NULL, *MutatedTree = NULL;
    int mutation_point, size_tree = getSizeTree(T), ctr = 0;
    double r;
    char left_son;

    MutatedTree = CopyTree(T);
    mutation_point = round(GenerateUniformRandomNumber(2, size_tree)); /* Mutation point cannot be the root */

    r = GenerateUniformRandomNumber(0, 1);
    if (p > r)
        NewTree = PreFixPositioningTree(MutatedTree, mutation_point, &left_son, FUNCTION, &ctr); /* the mutation point is a function node */
    else
        NewTree = PreFixPositioningTree(MutatedTree, mutation_point, &left_son, TERMINAL, &ctr); /* the mutation point is a terminal node */

    /* if the mutation point's parent is not a root (this may happen when the mutation point is a function, \
     and PreFixPositioningTree stops at a terminal node whose father is a root */
    if (NewTree)
    {
        aux = GROW(s, s->min_depth, s->max_depth); /* It creates the new subtree */

        /* It deletes the old subtree */
        if (left_son)
            tmp = NewTree->left;
        else
            tmp = NewTree->right;
        DestroyTree(&tmp);

        /* it connects the new subtree to the mutated tree */
        if (left_son)
        {
            NewTree->left = aux;
            aux->left_son = 1;
        }
        else
        {
            NewTree->right = aux;
            aux->left_son = 0;
        }
        aux->parent = NewTree;
    }
    else
    {
        DestroyTree(&MutatedTree);
        MutatedTree = GROW(s, s->min_depth, s->max_depth);
    }

    return MutatedTree;
}

/* It performs the crossover between father and mother trees
Parameters:
Father: pointer to the father tree
Mother: pointer to the mother tree
p: probability of mutation on a function node */
Node **Crossover(Node *Father, Node *Mother, float p)
{
    Node **offspring = NULL, *aux_father = NULL, *aux_mother = NULL, *tmp = NULL;
    int ctr = 0, crossover_point, size_tree;
    double r;
    char left_son_father, left_son_mother;

    if (!Father || !Mother)
    {
        fprintf(stderr, "\nInvalid input data @Crossover.\n");
        return NULL;
    }

    offspring = (Node **)malloc(2 * sizeof(Node *));

    /* It generates the offsprings */
    size_tree = getSizeTree(Father);
    crossover_point = round(GenerateUniformRandomNumber(2, size_tree)); /* Crossover point cannot be the root */
    offspring[0] = CopyTree(Father);
    r = GenerateUniformRandomNumber(0, 1);
    if (p >= r)
        aux_father = PreFixPositioningTree(offspring[0], crossover_point, &left_son_father, FUNCTION, &ctr); /* the mutation point is a function node */
    else
        aux_father = PreFixPositioningTree(offspring[0], crossover_point, &left_son_father, TERMINAL, &ctr); /* the mutation point is a terminal node */

    size_tree = getSizeTree(Mother);
    crossover_point = round(GenerateUniformRandomNumber(2, size_tree)); /* Crossover point cannot be the root */
    offspring[1] = CopyTree(Mother);
    ctr = 0;
    r = GenerateUniformRandomNumber(0, 1);
    if (p >= r)
        aux_mother = PreFixPositioningTree(offspring[1], crossover_point, &left_son_mother, FUNCTION, &ctr); /* the mutation point is a function node */
    else
        aux_mother = PreFixPositioningTree(offspring[1], crossover_point, &left_son_mother, TERMINAL, &ctr); /* the mutation point is a terminal node */

    /* If the crossover points have been properly found */
    if ((aux_father) && (aux_mother))
    {
        /* It performs the crossover for offspring #1 */
        if (left_son_father)
        {
            tmp = aux_father->left;
            if (left_son_mother)
            {
                aux_father->left = aux_mother->left;
                (aux_mother->left)->left_son = 1;
            }
            else
            {
                aux_father->left = aux_mother->right;
                (aux_mother->right)->left_son = 1;
            }
        }
        else
        {
            tmp = aux_father->right;
            if (left_son_mother)
            {
                aux_father->right = aux_mother->left;
                (aux_mother->left)->left_son = 0;
            }
            else
            {
                aux_father->right = aux_mother->right;
                (aux_mother->right)->left_son = 0;
            }
        }
        aux_mother->parent = aux_father;

        /* it performs the crossover for offspring #2 */
        if (left_son_mother)
        {
            aux_mother->left = tmp;
            tmp->left_son = 1;
        }
        else
        {
            aux_mother->right = tmp;
            tmp->left_son = 0;
        }
        tmp->parent = aux_mother;
    }

    return offspring;
}

/* It returns the parent of the pos-th node using a prefix travel
Parameters:
T: pointer to the tree
pos: position of the node to be retrieved
left_son: flag to identify whether the pos-th node is a left-son or not
status: status of the node (FUNCTION|TERMINAL)
ctr: pointer to the integer used to count nodes through the previx travel */
Node *PreFixPositioningTree(Node *T, int pos, char *left_son, int status, int *ctr)
{
    Node *Aux = NULL;

    if (T)
    {
        (*ctr)++;
        if (*ctr == pos)
        {
            *left_son = T->left_son;
            *ctr = 0;

            if (status == TERMINAL)
                return T->parent;

            /* If the node is a terminal and status = FUNCTION, thus the breakpoint will be its father (if this last is not a root),
             which is certainly a function node */
            else if ((T->parent)->parent)
            {
                *left_son = (T->parent)->left_son;
                return (T->parent)->parent;
            }
            else
                return NULL;
        }
        else
        {
            Aux = PreFixPositioningTree(T->left, pos, left_son, status, ctr);
            if (Aux)
                return Aux;
            else
            {
                Aux = PreFixPositioningTree(T->right, pos, left_son, status, ctr);
                if (Aux)
                    return Aux;
                else
                    return NULL;
            }
        }
    }
    else
        return NULL;
}

/* It performs the Geometric Semantic Genetic Programming crossover operator for boolean functions
Parameters:
s: search space
T1: pointer to the first tree
T2: pointer to the second tree */
Node *SGXB(SearchSpace *s, Node *T1_tmp, Node *T2_tmp)
{
    Node *T3 = NULL, *TR = NULL, *TR_cpy = NULL, *LeftTree = NULL;
    Node *RightTree = NULL, *T1 = NULL, *T2 = NULL, *NOT = NULL;

    if (!s || !T1_tmp || !T2_tmp)
    {
        fprintf(stderr, "\nInput error @SGXB.\n");
        return NULL;
    }

    T1 = CopyTree(T1_tmp);
    T2 = CopyTree(T2_tmp);

    /* It generates a random tree. It is expected a random tree with boolean functions if properly defined when creating the search space. */
    TR = GROW(s, s->min_depth, s->max_depth);
    TR_cpy = CopyTree(TR);

    T3 = CreateNode("OR", getFUNCTIONid("OR"), FUNCTION); /* It creates the root */
    T3->parent = NULL;

    LeftTree = CreateNode("AND", getFUNCTIONid("AND"), FUNCTION); /* It creates the tree on the left */
    T3->left = LeftTree;
    LeftTree->parent = T3;
    LeftTree->left = T1;
    T1->parent = LeftTree;
    LeftTree->right = TR;
    TR->parent = LeftTree;
    TR->left_son = 0;

    RightTree = CreateNode("AND", getFUNCTIONid("AND"), FUNCTION); /* It creates the tree on the right */
    T3->right = RightTree;
    RightTree->parent = T3;
    RightTree->left_son = 0;
    NOT = CreateNode("NOT", getFUNCTIONid("NOT"), FUNCTION);
    RightTree->left = NOT;
    NOT->parent = RightTree;
    RightTree->right = T2;
    T2->parent = RightTree;
    T2->left_son = 0;
    NOT->left = TR_cpy;
    TR_cpy->parent = NOT;

    return T3;
}

/* It performs the Geometric Semantic Genetic Programming mutation operator for boolean functions
Parameters:
s: search space
T: pointer to the tree */
Node *SGMB(SearchSpace *s, Node *T_tmp)
{
    Node *TM = NULL, *T = NULL, *M = NULL, *NOT = NULL;
    double r;
    int i;

    if (!s || !T_tmp)
    {
        fprintf(stderr, "\nInput error @SGMB.\n");
        return NULL;
    }

    r = randinter(0, 1);
    T = CopyTree(T_tmp);

    M = CreateNode("TMP", 0, NEW_TERMINAL, s->n);
    for (i = 0; i < s->n; i++)
        M->val[i] = round(GenerateUniformRandomNumber(s->LB[0], s->UB[0])); /* Creating a random minterm */

    if (r <= 0.5)
    {
        TM = CreateNode("OR", getFUNCTIONid("OR"), FUNCTION);
        TM->parent = NULL;
        TM->left = T;
        T->parent = TM;
        TM->right = M;
        M->parent = TM;
        M->left_son = 0;
    }
    else
    {
        TM = CreateNode("AND", getFUNCTIONid("AND"), FUNCTION);
        TM->parent = NULL;
        TM->left = T;
        T->parent = TM;
        NOT = CreateNode("NOT", getFUNCTIONid("NOT"), FUNCTION);
        TM->right = NOT;
        NOT->parent = TM;
        NOT->left_son = 0;
        NOT->left = M;
        M->parent = NOT;
    }

    return TM;
}
/***********************/

/* It performs the Geometric Semantic Genetic Programming crossover operator for real-valued functions
Parameters:
s: search space
T1: pointer to the first tree
T2: pointer to the second tree */
Node *SGXE(SearchSpace *s, Node *T1_tmp, Node *T2_tmp)
{
    Node *T3 = NULL, *TR = NULL, *LeftTree = NULL;
    Node *RightTree = NULL, *T1 = NULL, *T2 = NULL, *NOT_TR = NULL;
    int i;

    if (!s || !T1_tmp || !T2_tmp)
    {
        fprintf(stderr, "\nInput error @SGXE.\n");
        return NULL;
    }

    T1 = CopyTree(T1_tmp);
    T2 = CopyTree(T2_tmp);

    /* It generates an array with random values within [0,1] */
    TR = CreateNode("TMP", 0, NEW_TERMINAL, s->n);
    for (i = 0; i < s->n; i++)
        TR->val[i] = GenerateUniformRandomNumber(0, 1); /* Creating an array composed of random numbers */

    T3 = CreateNode("SUM", getFUNCTIONid("SUM"), FUNCTION); /* It creates the root */
    T3->parent = NULL;

    LeftTree = CreateNode("MUL", getFUNCTIONid("MUL"), FUNCTION); /* It creates the tree on the left */
    T3->left = LeftTree;
    LeftTree->parent = T3;
    LeftTree->left = T1;
    T1->parent = LeftTree;
    LeftTree->right = TR;
    TR->parent = LeftTree;
    TR->left_son = 0;

    RightTree = CreateNode("MUL", getFUNCTIONid("MUL"), FUNCTION); /* It creates the tree on the right */
    T3->right = RightTree;
    RightTree->parent = T3;
    RightTree->left_son = 0;

    NOT_TR = CreateNode("TMP", 0, NEW_TERMINAL, s->n);
    for (i = 0; i < s->n; i++)
        NOT_TR->val[i] = 1 - TR->val[i]; /* Creating 1-TR */

    RightTree->left = NOT_TR;
    NOT_TR->parent = RightTree;
    RightTree->right = T2;
    T2->parent = RightTree;
    T2->left_son = 0;

    return T3;
}

/* It performs the Geometric Semantic Genetic Programming mutation operator for real-valued functions
Parameters:
s: search space
T1: pointer to the first tree
T2: pointer to the second tree */
Node *SGME(SearchSpace *s, Node *T1_tmp, Node *T2_tmp)
{
    Node *T3 = NULL, *TR = NULL, *LeftTree = NULL;
    Node *RightTree = NULL, *T1 = NULL, *T2 = NULL, *NOT_TR = NULL;
    int i, j;

    if (!s || !T1_tmp || !T2_tmp)
    {
        fprintf(stderr, "\nInput error @SGME.\n");
        return NULL;
    }

    T1 = CopyTree(T1_tmp);
    T2 = CopyTree(T2_tmp);

    /* It generates an array with random values within [0,1] */
    TR = CreateNode("TMP", 0, NEW_TERMINAL, s->n);
    for (i = 0; i < s->n; i++)
        TR->val[i] = GenerateUniformRandomNumber(0, 1); /* Creating an array composed of random numbers */

    /* Now we choose a random number within [0,2] in order to pick some
    function bounded within [0,1] at random */
    j = round(GenerateUniformRandomNumber(0, 2));
    switch (j)
    {
    case 0:
        for (i = 0; i < s->n; i++)
            TR->val[i] = exp(TR->val[i]);
        break;
    case 1:
        for (i = 0; i < s->n; i++)
            TR->val[i] = fabs(sin(TR->val[i]));
        break;
    case 2:
        for (i = 0; i < s->n; i++)
            TR->val[i] = cos(sin(TR->val[i]));
        break;
    }

    T3 = CreateNode("SUM", getFUNCTIONid("SUM"), FUNCTION); /* It creates the root */
    T3->parent = NULL;

    LeftTree = CreateNode("MUL", getFUNCTIONid("MUL"), FUNCTION); /* It creates the tree on the left */
    T3->left = LeftTree;
    LeftTree->parent = T3;
    LeftTree->left = T1;
    T1->parent = LeftTree;
    LeftTree->right = TR;
    TR->parent = LeftTree;
    TR->left_son = 0;

    RightTree = CreateNode("MUL", getFUNCTIONid("MUL"), FUNCTION); /* It creates the tree on the right */
    T3->right = RightTree;
    RightTree->parent = T3;
    RightTree->left_son = 0;

    NOT_TR = CreateNode("TMP", 0, NEW_TERMINAL, s->n);
    for (i = 0; i < s->n; i++)
        NOT_TR->val[i] = 1 - TR->val[i]; /* Creating 1-TR */

    RightTree->left = NOT_TR;
    NOT_TR->parent = RightTree;
    RightTree->right = T2;
    T2->parent = RightTree;
    T2->left_son = 0;

    return T3;
}

/* Tensor-related functions */
/* It allocates a new tensor
Parameters:
n: number of decision variables
tensor_dim: tensor space dimension */
double **CreateTensor(int n, int tensor_dim){
    if (tensor_dim <= 0){
        fprintf(stderr, "\nInvalid parameters @CreateTensor.\n");
        return NULL;
    }
    double **t = NULL;
    int i;

    t = (double **)calloc(n, sizeof(double *));
    for (i = 0; i < n; i++)
        t[i] = (double *)calloc(tensor_dim, sizeof(double));

    return t;
}

/* It deallocates a new tensor
Parameters:
*t: pointer to the tensor
n: number of decision variables */
void DestroyTensor(double ***t, int n){
    double **tmp = NULL;
    int i;

    tmp = *t;
    if (!tmp){
        fprintf(stderr, "\nTensor not allocated @DeallocateTensor.\n");
        exit(-1);
    }

    for (i = 0; i < n; i++)
        free(tmp[i]);
    free(tmp);
}

/* It initializes an allocated search space with tensors
Parameters:
s: search space
tensor_id: identifier of the tensor space dimension */
void InitializeTensorSearchSpace(SearchSpace *s, int tensor_id){
    if (!s){
        fprintf(stderr, "\nSearch space not allocated @InitializeTensorSearchSpace.\n");
        exit(-1);
    }

    int i, j, k;

    for (i = 0; i < s->m; i++){
        for (j = 0; j < s->n; j++){
            for (k = 0; k < tensor_id; k++)
                s->a[i]->t[j][k] = GenerateUniformRandomNumber(0, 1);
            s->a[i]->x[j] = TensorSpan(s->LB[j], s->UB[j], s->a[i]->t[j], tensor_id);
        }
    }
}

/* It shows a search space with tensors
Parameters:
s: search space
tensor_id: identifier of the tensor space dimension */
void ShowTensorSearchSpace(SearchSpace *s, int tensor_id){
    if (!s){
        fprintf(stderr, "\nSearch space not allocated @ShowTensorSearchSpace.\n");
        exit(-1);
    }

    int i, j, k;
    fprintf(stderr, "\nSearch space with %d agents, %d decision variables and %d-D tensors\n", s->m, s->n, tensor_id);

    for (i = 0; i < s->m; i++){
        fprintf(stderr, "\nAgent %d->\n", i);
        for (j = 0; j < s->n; j++){
            for (k = 0; k < tensor_id; k++)
                fprintf(stderr, "t[%d][%d]: %f   ", j, k, s->a[i]->t[j][k]);
            fprintf(stderr, "\n");
        }
        fprintf(stderr, "fitness value: %f", s->a[i]->fit);
    }
    fprintf(stderr, "\n-----------------------------------------------------\n");
}

/* It checks whether a given tensor has excedeed boundaries
Parameters:
s: search space
a: tensor */
void CheckTensorLimits(SearchSpace *s, double **t, int tensor_dim)
{
    if (!s)
    {
        fprintf(stderr, "\nInvalid SearchSpace parameters @CheckTensorLimits.\n");
        exit(-1);
    }

    if (!t)
    {
        fprintf(stderr, "\nInvalid Tensor parameters @CheckTensorLimits.\n");
        exit(-1);
    }

    int j, k;

    for (j = 0; j < s->n; j++)
    {
        for (k = 0; k < tensor_dim; k++)
        {
            if (t[j][k] < 0)
                t[j][k] = 0;
            else if (t[j][k] > 1)
                t[j][k] = 1;
        }
    }
}

/* It copies a given tensor
Parameters:
t: tensor vector
n: problem's dimension
tensor_id: identifier of the tensor space dimension */
double **CopyTensor(double **t, int n, int tensor_id)
{
    if (!t)
    {
        fprintf(stderr, "\nNo tensor allocated @CopyTensor.\n");
        exit(-1);
    }

    int i;
    double **cpy = NULL;

    cpy = CreateTensor(n, tensor_id);
    for (i = 0; i < n; i++)
        memcpy(cpy[i], t[i], tensor_id * sizeof(double));

    return cpy;
}

/* It computes the norm of a given tensor
Parameters:
t: tensor vector
tensor_id: identifier of the tensor space dimension */
double TensorNorm(double *t, int tensor_id)
{
    if (tensor_id <= 0)
    {
        fprintf(stderr, "\nInvalid parameters @TensorNorm.\n");
        return -1;
    }

    double norm = 0;
    int i;

    for (i = 0; i < tensor_id; i++)
        norm += pow(t[i], 2);
    norm = sqrt(norm);

    return norm;
}

/* It generates a new tensor
Paremeters:
s: search space
tensor_id: identifier of tensor's dimension */
double **GenerateNewTensor(SearchSpace *s, int tensor_id)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @GenerateNewTensor.\n");
        exit(-1);
    }

    double **t = NULL;
    int j, k;

    t = CreateTensor(s->n, tensor_id);
    for (j = 0; j < s->n; j++)
        for (k = 0; k < tensor_id; k++)
            t[j][k] = GenerateUniformRandomNumber(0, 1);

    return t;
}

/* It maps the tensor value to a real one bounded by [L,U]
Parameters:
L: lower bound
U: upper bound
t: tensor vector
tensor_id: identifier of tensor's dimension */
double TensorSpan(double L, double U, double *t, int tensor_dim)
{
    if (tensor_dim <= 0)
    {
        fprintf(stderr, "\nInvalid parameters @TensorSpan.\n");
        return -1;
    }

    double span = 0;
    int i;

    span = (U - L) * (TensorNorm(t, tensor_dim) / sqrt(tensor_dim)) + L;

    return span;
}

/* It calculates the Euclidean Distance between tensors
Parameters:
t: first tensor
s: second tensor
n: problem's dimension
tensor_id: identifier of tensor's dimension */
double TensorEuclideanDistance(double **t, double **s, int n, int tensor_id)
{
    if (tensor_id <= 0)
    {
        fprintf(stderr, "\nInvalid parameters @TensorEuclideanDistance.\n");
        return -1;
    }

    double distance = 0, p_distance = 0;
    int j, k;

    for (j = 0; j < n; j++)
    {
        for (k = 0; k < tensor_id; k++)
            p_distance += pow(t[j][k] - s[j][k], 2);
        distance += sqrt(p_distance);
        p_distance = 0;
    }

    distance = sqrt(distance);

    return distance;
}

/* It evaluates a tensor-based search space
 * This function only evaluates each agent and sets its best fitness value,
 * as well as it sets the global best fitness value and agent.
Parameters:
s: search space
opt_id: optimization technique identifier
tensor_id: identifier of tensor's dimension
EvaluateFun: pointer to the function used to evaluate particles (agents)
arg: list of additional arguments */
void EvaluateTensorSearchSpace(SearchSpace *s, int opt_id, int tensor_id, prtFun Evaluate, va_list arg)
{
    if (!s)
    {
        fprintf(stderr, "\nSearch space not allocated @EvaluateTensorSearchSpace.\n");
        exit(-1);
    }

    int i, j, k;
    double f, *tmp = NULL;
    Agent *individual = NULL;
    va_list argtmp;

    va_copy(argtmp, arg);

    switch (opt_id)
    {
    case _BA_:
    case _FPA_:
    case _CS_:
    case _BHA_:
    case _ABC_:
	case _BSA_:
    case _HS_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            if (f < s->a[i]->fit) /* It updates the fitness value */
                s->a[i]->fit = f;

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                {
                    s->g[j] = s->a[i]->x[j];
                    for (k = 0; k < tensor_id; k++)
                        s->t_g[j][k] = s->a[i]->t[j][k];
                }
            }

            va_copy(arg, argtmp);
        }
        break;
    case _PSO_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            if (f < s->a[i]->fit)
            { /* It updates the local best value and position */
                s->a[i]->fit = f;
                for (j = 0; j < s->n; j++)
                    for (k = 0; k < tensor_id; k++)
                        s->a[i]->t_xl[j][k] = s->a[i]->t[j][k];
            }

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                {
                    s->g[j] = s->a[i]->x[j];
                    for (k = 0; k < tensor_id; k++)
                        s->t_g[j][k] = s->a[i]->t[j][k];
                }
            }
            va_copy(arg, argtmp);
        }
        break;
    case _FA_:
        for (i = 0; i < s->m; i++)
        {
            f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */

            s->a[i]->fit = f; /* It updates the fitness value of actual agent i */

            if (s->a[i]->fit < s->gfit)
            { /* It updates the global best value and position */
                s->gfit = s->a[i]->fit;
                for (j = 0; j < s->n; j++)
                {
                    s->g[j] = s->a[i]->x[j];
                    for (k = 0; k < tensor_id; k++)
                        s->t_g[j][k] = s->a[i]->t[j][k];
                }
            }

            va_copy(arg, argtmp);
        }
        break;
    default:
        fprintf(stderr, "\n Invalid optimization identifier @EvaluateTensorSearchSpace.\n");
        break;
    }
}

/* It runs a given tensor-based tree and outputs its solution array
Parameters:
s: search space
T: current tree */
double **RunTTree(SearchSpace *s, Node *T){
    double **x = NULL, **y = NULL, **out = NULL;
    int i, j;

    if (T){
        x = RunTTree(s, T->left);  /* It runs over the subtree on the left */
        y = RunTTree(s, T->right); /* It runs over the subtree on the right */

        if (T->status == TERMINAL || T->status == CONSTANT){
            out = CreateTensor(s->n, s->tensor_dim);
            if (T->status == CONSTANT){
                for (i = 0; i < s->n; i++)
                    for(j = 0; j < s->tensor_dim; j++)
                        out[i][j] = s->t_constant[T->id][i][j];
            }
            else{ /* it is a terminal node */
                for (i = 0; i < s->n; i++)
                    for(j = 0; j < s->tensor_dim; j++)
                        out[i][j] = s->a[T->id]->t[i][j];
            }
            return out;
        }
        else{
            if (!strcmp(T->elem, "TSUM"))
                out = f_TSUM_(x, y, s->n, s->tensor_dim);
            else if (!strcmp(T->elem, "TSUB"))
                out = f_TSUB_(x, y, s->n, s->tensor_dim);
            else if (!strcmp(T->elem, "TMUL"))
                out = f_TMUL_(x, y, s->n, s->tensor_dim);
            else if (!strcmp(T->elem, "TDIV"))
                out = f_TDIV_(x, y, s->n, s->tensor_dim);
            
            /* it deallocates the sons of the current one, since they have been used already */
            if (x) DestroyTensor(&x, s->n);
            if (y) DestroyTensor(&y, s->n);
            return out;
        }
    }
    else return NULL;
}


/***********************/

/* Simulated Annealing (SA) related functions */
/* It returns the identifier of the function used as the SA Cooling Schedule
Parameters:
s: string with the cooling function name */
int getCoolingScheduleId(char *s)
{
    if (!strcmp(s, "BOLTZMANN_ANNEALING"))
        return BOLTZMANN_ANNEALING;
    else if(!strcmp(s, "FAST_SCHEDULE_ANNEALING"))
        return FAST_SCHEDULE_ANNEALING;
    else {
        fprintf(stderr, "\nUndefined function for Cooling Schedule @getCoolingScheduleId.");
        exit(-1);
    }
}

/***********************/
