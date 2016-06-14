#include "common.h"

/* Agent-related functions */
/* It creates an agent
Parameters:
n: number of decision variables
opt_id: identifier of the optimization technique */
Agent *CreateAgent(int n, int opt_id){
    if((n < 1) || opt_id < 1){
        fprintf(stderr,"\nInvalid parameters @CreateAgent.\n");
        return NULL;
    }
    
    Agent *a = NULL;
    a = (Agent *)malloc(sizeof(Agent));
    a->v = NULL;
    a->xl = NULL;
    a->fit = DBL_MAX;
    a->pfit = DBL_MAX;
    a->n = n;
    
    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
            a->x = (double *)calloc(n,sizeof(double));
            a->v = (double *)calloc(n,sizeof(double));
            if(opt_id == _PSO_) a->xl = (double *)calloc(n,sizeof(double));
        break;
        default:
            free(a);
            fprintf(stderr,"\nInvalid optimization identifier @CreateAgent\n");
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
    if(!tmp){
        fprintf(stderr,"\nAgent not allocated @DestroyAgent.\n");
        exit(-1);
    }
    
    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
            if(tmp->x) free(tmp->x);
            if(tmp->v) free(tmp->v);
            if(opt_id == _PSO_) if(tmp->xl) free(tmp->xl);
        break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroyAgent.\n");
        break;
    }
    
    free(tmp);
}

/* It checks whether a given agent has excedeed boundaries
Parameters:
s: search space
a: agent */
void CheckAgentLimits(SearchSpace *s, Agent *a){
    if((!s) || (!a)){
        fprintf(stderr,"\nInvalid input parameters @CheckAgentLimits.\n");
        exit(-1);
    }
    
    int j;

    for(j = 0; j < a->n; j++){
        if(a->x[j] < s->LB[j]) a->x[j] = s->LB[j];
        else if(a->x[j] > s->UB[j]) a->x[j] = s->UB[j];
    }
}

/* It copies an agent
Parameters:
a: agent
opt_id: identifier of the optimization technique */
Agent *CopyAgent(Agent *a, int opt_id){
    if(!a){
        fprintf(stderr,"\nAgent not allocated @CopyAgent.\n");
        exit(-1);
    }
    
    Agent *cpy = NULL;
    cpy = CreateAgent(a->n, opt_id);
    
    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
            memcpy(cpy->x, a->x, a->n*sizeof(double));
            memcpy(cpy->v, a->v, a->n*sizeof(double));
            if(opt_id == _PSO_) memcpy(cpy->xl, a->xl, a->n*sizeof(double));
        break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @CopyAgent.\n");
            DestroyAgent(&cpy, opt_id);
            return NULL;
        break;
    }
    
    return cpy;
}

/* It generates a new agent according to each technique
Paremeters:
s: search space
opt_id: identifier of the optimization technique */
Agent *GenerateNewAgent(SearchSpace *s, int opt_id){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @GenerateNewAgent.\n");
        exit(-1);
    }
    
    Agent *a = NULL;
    int j;
        
    switch (opt_id){
        case _PSO_:
        break;
        case _BA_:
            a = CreateAgent(s->n, _BA_);
            
            /* The factor 0.001 limits the step sizes of random walks */ 
            for(j = 0; j < s->n; j++)
                a->x[j] = s->g[j]+0.001*GenerateUniformRandomNumber(0,1); 
        break;
        case _FPA_:
        break;
        case _FA_:
        break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @GenerateNewAgent.\n");
            return NULL;
        break;
    }
    
    return a;
}

/**************************/

/* Search Space-related functions */
/* It creates a search space
Parameters:
m: number of agents
n: number of decision variables
opt_id: identifier of the optimization technique */
SearchSpace *CreateSearchSpace(int m, int n, int opt_id){
    SearchSpace *s = NULL;
    
    if((m < 1) || (n < 1) || (opt_id < 1)){
        fprintf(stderr,"\nInvalid parameters @CreateSearchSpace.\n");
        return NULL;
    }
    int i;
    
    s = (SearchSpace *)malloc(sizeof(SearchSpace));
    s->m = m;
    s->n = n;
    s->gfit = DBL_MAX;
    s->w = 0;
    s->w_min = 0;
    s->w_max = 0;
    s->c1 = 0;
    s->c2 = 0;
    
    s->a = (Agent **)malloc(s->m*sizeof(Agent *));
    s->a[0] = CreateAgent(s->n, opt_id);
    if(s->a[0]){ /* Here, we verify whether opt_id is valid or not. In the latter case, function CreateAgent returns NULL. */
        for(i = 1; i < s->m; i++)
            s->a[i] = CreateAgent(s->n, opt_id);
    }else{
        free(s->a);
        free(s);
        return NULL;
    }
    
    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
            s->g = (double *)calloc(s->n,sizeof(double));
        break;
    }
    
    s->LB = (double *)malloc(s->n*sizeof(double));
    s->UB = (double *)malloc(s->n*sizeof(double));
    
    return s;
}

/* It deallocates a search space
Parameters:
s: address of the search space to be deallocated
opt_id: identifier of the optimization technique */
void DestroySearchSpace(SearchSpace **s, int opt_id){
    SearchSpace *tmp = NULL;
    int i;
    
    tmp = *s;
    if(!tmp){
        fprintf(stderr,"\nSearch space not allocated @DestroySearchSpace.\n");
        exit(-1);
    }
    
    for(i = 0; i < tmp->m; i++)
        if(tmp->a[i]) DestroyAgent(&(tmp->a[i]), opt_id);
    free(tmp->a);
    
    if(tmp->LB) free(tmp->LB);
    if(tmp->UB) free(tmp->UB);
    
    switch (opt_id){
        case _PSO_:
        case _BA_:
        case _FPA_:
        case _FA_:
            if(tmp->g) free(tmp->g);
        break;
        default:
            fprintf(stderr,"\nInvalid optimization identifier @DestroySearchSpace.\n");
        break;       
    }
    
    free(tmp);
}

/* It initializes an allocated search space
Parameters:
s: search space */
void InitializeSearchSpace(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @InitializeSearchSpace.\n");
        exit(-1);
    }
    
    int i, j;
    for(i = 0; i < s->m; i++){
        for(j = 0; j < s->n; j++)
            s->a[i]->x[j] = (double)randinter((float)s->LB[j],(float) s->UB[j]);
    }
}

/* It shows a search space
Parameters:
s: search space */
void ShowSearchSpace(SearchSpace *s){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @ShowSearchSpace.\n");
        exit(-1);
    }
    
    int i, j;
    fprintf(stderr,"\nSearch space with %d agents and %d decision variables\n", s->m, s->n);
    for(i = 0; i < s->m; i++){
        fprintf(stderr,"\nAgent %d-> ", i);
        for(j = 0; j < s->n; j++)
            fprintf(stderr,"x[%d]: %f   ", j, s->a[i]->x[j]);
        fprintf(stderr,"fitness value: %f", s->a[i]->fit);
    }
    fprintf(stderr,"\n-----------------------------------------------------\n");
}

/* It evaluates a search space
 * This function only evaluates each agent and sets its best fitness value,
 * as well as it sets the global best fitness value and agent.
Parameters:
s: search space
EvaluateFun: pointer to the function used to evaluate particles (agents)
arg: list of additional arguments */
void EvaluateSearchSpace(SearchSpace *s, prtFun Evaluate, va_list arg){
    if(!s){
        fprintf(stderr,"\nSearch space not allocated @EvaluateSearchSpace.\n");
        exit(-1);
    }
    
    int i, j;
    double f;
    va_list argtmp;
    
    for(i = 0; i < s->m; i++){
        f = Evaluate(s->a[i], arg); /* It executes the fitness function for agent i */
        
        if(f < s->a[i]->fit) /* It updates the fitness value */
            s->a[i]->fit = f;
        
        if(s->a[i]->fit < s->gfit){ /* It updates the global best value and position */
            s->gfit = s->a[i]->fit;
            for(j = 0; j < s->n; j++)
                s->g[j] = s->a[i]->x[j];
        }
        
        va_copy(arg, argtmp);
    }
}
/**************************/

/* General-purpose functions */
/* It generates a random number uniformly distributed between low and high
Parameters:
low: lower bound
high: upper bound
This algorithm has been inspired by: http://www.cprogramming.com/tutorial/random.html */
double GenerateUniformRandomNumber(double low, double high){
    return randinter(low, high);
}

/* It generates a random number drawn from a Gaussian (normal) distribution
Parameters:
mean: mean of the distribution
variance: variance of the distribution */
double GenerateGaussianRandomNumber(double mean, double variance){
    return randGaussian(mean, variance);
}

/* It generates an n-dimensional array drawn from a Levy distribution
 * The formulation used here is based on the paper "Multiobjective Cuckoo Search for Design Optimization", X.-S. Yang and S. Deb, Computers & Operations Research, 2013.
Parameters:
n: dimension of the output array
beta: input parameter used in the formulation */
double *GenerateLevyDistribution(int n, double beta){
    double *L = NULL, sigma_u, sigma_v = 1;
    double *u = NULL, *v = NULL;
    int i;
    
    if(n < 1){
        fprintf(stderr,"Invalid input paramater @GenerateLevyDistribution.\n");
        return NULL;
    }
    
    L = (double *)malloc(n*sizeof(double));
    
    sigma_u = pow((tgamma(1+beta)*sin(M_PI*beta/2))/(tgamma((1+beta)/2)*beta*pow(2,(beta-1)/2)), 1/beta); /* Equation 16 */
    
    u = (double *)malloc(n*sizeof(double));
    v = (double *)malloc(n*sizeof(double));
    sigma_u = pow(sigma_u, 2);
    for(i = 0; i < n; i++){ /* It computes Equation 15 */
        u[i] = GenerateGaussianRandomNumber(0, sigma_u);
        v[i] = GenerateGaussianRandomNumber(0, sigma_v);
    }
    
    for(i = 0; i < n; i++)
        L[i] = 0.01*(u[i]/pow(fabs(v[i]), 1/beta)); /* It computes Equation 14 (part of it) */
    
    free(u);
    free(v);
    
    return L;
}

/* It computes the Euclidean distance between two n-dimensional arrays
Parameters:
x: n-dimension array
y: n-dimension array */
double EuclideanDistance(double *x, double *y, int n){
    double sum = 0.0;
    int i;
    
    for(i = 0; i < n; i++)
        sum+=pow(x[i]-y[i],2);
    
    return sqrt(sum);
}

/* It computes the compare function used on Quick Sort (qsort) */
int CompareForQSort(const void *a, const void *b){
    const Agent *ap = *(Agent **)a, *bp = *(Agent **)b;
    if (ap->fit < bp->fit) {
        return -1;
    }
    if (ap->fit > bp->fit)
        return 1;
    return 0;
}

/* It waives a comment in a model file
Parameters:
fp = file pointer */
void WaiveComment(FILE *fp){
    char c;
    
    fscanf(fp, "%c", &c);
    while((c != '\n') && (!feof(fp))) fscanf(fp, "%c", &c);
    
}

/* It loads a search space with parameters specified in a file
Parameters:
fileName: path to the file that contains the parameters of the search space
opt_id: identifier of the optimization technique */
SearchSpace *ReadSearchSpaceFromFile(char *fileName, int opt_id){
    FILE *fp = NULL;
    SearchSpace *s = NULL;
    int j, m, n, iterations;
    
    fp = fopen(fileName, "r");
    if(!fp){
        fprintf(stderr,"\nUnable to open file %s @ReadSearchSpaceFromFile.\n", fileName);
        return NULL;
    }
    
    fscanf(fp, "%d %d %d", &m, &n, &iterations);
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
        default:
            fprintf(stderr,"\nInvalid optimization identifier @ReadSearchSpaceFromFile.\n");
        break;
    }
    
    for(j = 0; j < s->n; j++){
        fscanf(fp, "%lf %lf", &(s->LB[j]), &(s->UB[j]));
        WaiveComment(fp);
    }
    fclose(fp);
    
    return s;
}
/**************************/