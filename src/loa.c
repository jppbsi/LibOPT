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


#include "loa.h"

/* In each pride, some females look for a prey (hunt)
Parameters:
s: search space
pride: pride identification number
selected_females: binary array (zeroed) that each index indicates if a female is hunting right now or not
Evaluate: pointer to the function used to evaluate lionsses
arg: list of additional arguments */
void Hunting(SearchSpace *s, int pride, int *selected_females, prtFun Evaluate, va_list arg)
{
  int i, j, n_selected, index, center_index;
  int *group = calloc(3, sizeof(int));               /* counter of members of each group */
  int range_group[3][2];                             /* matrix that represents the interval of each grupo (in indexes) */
  int *cumulative_finesses = calloc(3, sizeof(int)); /* cumulative finesses if each group */
  Agent **Hunters = NULL;                            /* array of hunters */
  double *Prey = NULL;                               /* prey position in search space */

  /* determining which and how many females will hunt */
  n_selected = 0;
  /* for each female in the pride... */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    selected_females[i] = round(GenerateUniformRandomNumber(0, 1)); /* determine if a female is selected or not */
    /* determining the size (in members) of each group */
    if (selected_females[i])
    {                                                      /* if ith female was selected */
      group[(int)(GenerateUniformRandomNumber(0, 2.9))]++; /* sum one on a random group (index from 0 to 2)*/
      n_selected++;
    }
  }

  Hunters = (Agent **)calloc(n_selected, sizeof(Agent *)); /* allocating the array of hunters */
  /* putting each of the selected lionesses randomly in to the Hunters array */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    if (selected_females[i])
    {
      /* try a position on the array. repeat until find a empty slot (Hunters[index] == 0)*/
      do
      {
        index = (int)GenerateUniformRandomNumber(0, n_selected - 0.001);
      } while (Hunters[index] != 0);
      Hunters[index] = s->pride_id[pride].females[i];
    }
  }

  /* determining the interval of indexes of each group */
  /* for the first group */
  range_group[0][0] = 0;
  range_group[0][1] = group[0];
  /* for the second group */
  range_group[1][0] = group[0];
  range_group[1][1] = group[0] + group[1];
  /* for the third group */
  range_group[2][0] = group[0] + group[1];
  range_group[2][1] = group[0] + group[1] + group[2];

  /* dealocating the group counter array */
  free(group);

  /* determining the cumulative finesses for each group */
  for (i = 0; i < 3; i++)
  {
    for (j = range_group[i][0]; j < range_group[i][1]; j++)
      cumulative_finesses[i] += Hunters[j]->fit;
  }

  /* determining the center group */
  center_index = 0; /* assuming that the center is the fist group */
  for (i = 1; i < 3; i++)
  {
    if (cumulative_finesses[center_index] > cumulative_finesses[i])
      center_index = i;
  }

  /* dealocating the cumulative finesses array */
  free(cumulative_finesses);

  /* Generating a Prey in center of hunters*/
  Prey = (double *)calloc(s->n, sizeof(double));
  /* for each decision variable if the prey */
  for (i = 0; i < s->n; i++)
  {
    /* for each  selected lioness */
    for (j = 0; j < n_selected; j++)
      Prey[i] += Hunters[j]->x[i];
    Prey[i] = Prey[i] / n_selected;

    // Checking if the prey has excedeed boundaries
    if (Prey[i] < s->LB[i])
      Prey[i] = s->LB[i];
    else if (Prey[i] > s->UB[i])
      Prey[i] = s->UB[i];
  }

  /* lioness attacking the prey */
  for (i = 0; i < n_selected; i++)
  {
    /* if the lioness is from the center group... */
    if ((i >= range_group[center_index][0]) && (i < range_group[center_index][1]))
    {
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
      {
        if (Prey[j] > Hunters[i]->x[j])
          Hunters[i]->x[j] = GenerateUniformRandomNumber(Hunters[i]->x[j], Prey[j]);
        else
          Hunters[i]->x[j] = GenerateUniformRandomNumber(Prey[j], Hunters[i]->x[j]);
      }
    }
    /* lioness is from the left wing or of the right wing group */
    else
    {
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
      {
        if (Prey[j] > (2 * Prey[j] - Hunters[i]->x[j]))
          Hunters[i]->x[j] = GenerateUniformRandomNumber((2 * Prey[j] - Hunters[i]->x[j]), Prey[j]);
        else
          Hunters[i]->x[j] = GenerateUniformRandomNumber(Prey[j], (2 * Prey[j] - Hunters[i]->x[j]));
      }
    }
    CheckAgentLimits(s, Hunters[i]);
    /* Calculating the new fitness of the lioness */
    EvaluateAgent(s, Hunters[i], _LOA_, Evaluate, arg);

    /* if ith lioness improves its own fitness */
    if (Hunters[i]->fit < Hunters[i]->pfit)
    {
      /* the prey will scape */
      double improve_perc = Hunters[i]->fit / Hunters[i]->pfit;
      for (j = 0; j < s->n; j++)
        Prey[j] = Prey[j] + GenerateUniformRandomNumber(0, 1) * improve_perc * (Prey[j] - Hunters[i]->x[j]);
    }
  }

  free(Prey);
  free(Hunters);
}

/* In each pride, remained females go toward a safe place
Parameters:
s: search space
pride: pride identification number
selected_females: binary array declared (zeroed) in'runLOA()' and modified on 'hunting()' that each ith element indicates if the ith female is hunting right now or not
Evaluate: pointer to the function used to evaluate lionsses
arg: list of additional arguments */
void MovingSafePlace(SearchSpace *s, int pride, int *selected_females, prtFun Evaluate, va_list arg)
{
  int i, j;
  int tournament_size, index, pride_size, territory_index;
  int sucess = 0;               /* counter of how many lions improved its fitness in the last iteration */
  char *selected = NULL;         /* binary array that indicates if a agent was already selected (1) for tournament or not (0) */
  Agent **pride_members = NULL; /* array of all agents of the pride */
  double r1[s->n];              /* vector of direction */
  double *r2 = NULL;            /* pointer to vector of direction perpendicular to r1 */

  pride_size = s->pride_id[pride].n_females + s->pride_id[pride].n_males; /* pride size is the number of males + the number of females */
  pride_members = (Agent **)malloc(pride_size * sizeof(Agent *));         /* allocating the array of members */

  /* for each female in the pride */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    pride_members[i] = s->pride_id[pride].females[i]; /* pointing to the females of the pride */
    /* if female improved its fitness in the last iteration */
    if (s->pride_id[pride].females[i]->fit < s->pride_id[pride].females[i]->pfit)
      sucess++;
  }

  /* for each male in the pride */
  for (i = 0; i < s->pride_id[pride].n_males; i++)
  {
    pride_members[i + s->pride_id[pride].n_females] = s->pride_id[pride].males[i]; /* pointing to the males of the pride */
    /* if male improved its fitness in the last iteration */
    if (s->pride_id[pride].males[i]->fit < s->pride_id[pride].males[i]->pfit)
      sucess++;
  }

  selected = (char *)calloc(pride_size, sizeof(char)); /* allocating the binary array */
  tournament_size = (int)fmax(2, ceil(sucess / 2));  /* determining the tournament size */

  /* for each female in the pride */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    /* if the ith female is not hunting */
    if (!selected_females[i])
    {

      /* determinig which lion will be select to tournament */
      for (j = 0; j < tournament_size; j++)
      {
        do
        {
          index = (int)GenerateUniformRandomNumber(0, pride_size - 0.001);
        } while (selected[index]);
        selected[index] = 1; /* mark as selected */
      }

      /* determinig the best territory (winner of the tournament) */
      territory_index = 0;
      for (j = 1; j < pride_size; j++)
      {
        /* if the territory was selected for tournament AND the jth territory is better than the index-th */
        if ((selected[j]) && (pride_members[j]->best_fit < pride_members[territory_index]->best_fit))
          territory_index = j;
      }

      /* determing the vector of direction from female previous position to the selected position (territory) */
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
        r1[j] = pride_members[territory_index]->xl[j] - s->pride_id[pride].females[i]->prev_x[j];

      /* determing the r2 vector (perpendicular to r1)*/
      r2 = GetPerpendicularVector(r1, s->n);

      /* making the magnitude of r2 1 */
      NormalizeVector(r2, s->n);

      /* determing the distance between the actual position and the selected position */
      double distance = EuclideanDistance(s->pride_id[pride].females[i]->x, pride_members[territory_index]->xl, s->n);
      /* determing the random angle */
      double theta = GenerateUniformRandomNumber(-M_PI / 6, M_PI / 6);
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
        s->pride_id[pride].females[i]->x[j] = s->pride_id[pride].females[i]->x[j] + 2 * distance * GenerateUniformRandomNumber(0, 1) * r1[j] +
                                              GenerateUniformRandomNumber(-1, 1) * tan(theta) * distance * r2[j];

      CheckAgentLimits(s, s->pride_id[pride].females[i]);
      EvaluateAgent(s, s->pride_id[pride].females[i], _LOA_, Evaluate, arg);

      /* if is not the last female */
      if (i < s->pride_id[pride].n_females - 1)
      {
        /* reset the selected array for the next tournament */
        memset(selected, 0, sizeof(char) * pride_size);
      }
      free(r2);
    }
  }
  free(pride_members);
  free(selected);
}

/* In each pride, male lions roams in that pride's territory(best position of each lion in the pride)
Parameters:
s: search space
pride: pride identification number
Evaluate: pointer to the function used to evaluate lions
arg: list of additional arguments */
void Roaming(SearchSpace *s, int pride, prtFun Evaluate, va_list arg)
{
  int i, j, k;
  int pride_size, n_territory, index;
  int *selected = NULL;
  Agent **pride_members = NULL;
  double step, angle, distance;

  pride_size = s->pride_id[pride].n_males + s->pride_id[pride].n_females;
  pride_members = (Agent **)malloc(pride_size * sizeof(Agent *));

  /* for each female in the pride */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
    pride_members[i] = s->pride_id[pride].females[i]; /* pointing to the females of the pride */

  /* for each male in the pride */
  for (i = 0; i < s->pride_id[pride].n_males; i++)
    pride_members[i + s->pride_id[pride].n_females] = s->pride_id[pride].males[i]; /* pointing to the males of the pride */

  selected = (int *)calloc(pride_size, sizeof(int));

  /* determining the size of the territory */
  n_territory = round(s->roaming_percent * pride_size);

  /* for each male in pride */
  for (i = 0; i < s->pride_id[pride].n_males; i++)
  {
    /* randomly selecting n_territory places of pride's territory */
    for (j = 0; j < n_territory; j++)
    {
      do
      {
        index = (int)GenerateUniformRandomNumber(0, pride_size - 0.001);
      } while (selected[index]);
      selected[index] = 1; /* mark as selected */
    }
    /* for each territory */
    for (j = 0; j < pride_size; j++)
    {
      /* if the jth territory was selected */
      if (selected[j])
      {
        angle = GenerateUniformRandomNumber(-M_PI / 6, M_PI / 6);
        distance = EuclideanDistance(s->pride_id[pride].males[i]->x, pride_members[j]->xl, s->n);
        step = GenerateUniformRandomNumber(0, 2 * distance);
        /* for each decision variable */
        for (k = 0; k < s->n; k++)
          s->pride_id[pride].males[i]->x[k] = s->pride_id[pride].males[i]->x[k] + step + angle; /* Updates the actual male position */

        CheckAgentLimits(s, s->pride_id[pride].males[i]);

        EvaluateAgent(s, s->pride_id[pride].males[i], _LOA_, Evaluate, arg);
      }
    }
    /* saving the last fitness value */
    s->pride_id[pride].males[i]->pfit = s->pride_id[pride].males[i]->fit;
    /* selecting the best visited position by ith male as its current position */
    s->pride_id[pride].males[i]->fit = s->pride_id[pride].males[i]->best_fit;
    /* for each decision variable */
    for (k = 0; k < s->n; k++)
      s->pride_id[pride].males[i]->x[k] = s->pride_id[pride].males[i]->xl[k];

    /* if is not the last male */
    if (i < s->pride_id[pride].n_males - 1)
    {
      /* reset the selected array for the next random selection */
      for (j = 0; j < pride_size; j++)
        selected[j] = 0;
    }
  }
  free(pride_members);
  free(selected);
}

/* Nomad lions (female and male) move randomly in search space
Parameters:
s: search space
extra_male_nomads: number of extra male nomads that moved out from the prides
Evaluate: pointer to the function used to evaluate male and female lions
arg: list of additional arguments */
void NomadMovingRandom(SearchSpace *s, int extra_male_nomads, prtFun Evaluate, va_list arg)
{
  int i, j;
  double pr, randj;

  /* for each nomad female */
  for (i = 0; i < s->n_female_nomads; i++)
  {
    /* determining the probability */
    pr = 0.1 + fmin(0.5, (s->female_nomads[i]->fit + s->female_nomads[i]->best_fit) / s->female_nomads[i]->best_fit);
    /* for each  decision variable */
    for (j = 0; j < s->n; j++)
    {
      randj = GenerateUniformRandomNumber(0, 1);
      if (randj <= pr)
        s->female_nomads[i]->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]); /* Generating new position */
    }

    CheckAgentLimits(s, s->female_nomads[i]);
    EvaluateAgent(s, s->female_nomads[i], _LOA_, Evaluate, arg);
  }

  /* for each nomad male */
  for (i = 0; i < s->n_male_nomads + extra_male_nomads; i++)
  {
    /* determining the probability */
    pr = 0.1 + fmin(0.5, (s->male_nomads[i]->fit + s->male_nomads[i]->best_fit) / s->male_nomads[i]->best_fit);
    /* for each  decision variable */
    for (j = 0; j < s->n; j++)
    {
      randj = GenerateUniformRandomNumber(0, 1);
      if (randj <= pr)
        s->male_nomads[i]->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]); /* Generating new position */
    }

    CheckAgentLimits(s, s->male_nomads[i]);
    EvaluateAgent(s, s->male_nomads[i], _LOA_, Evaluate, arg);
  }
}

/* In every pride, a female mate with one or several resident males with a determined probability, producing 2 offsprings(a male and a female)
Parameters:
s: search space
pride: pride identification number
n_offsprings: number of offsprings that will be generated by matting
Evaluate: pointer to the function used to evaluate the cubs
arg: list of additional arguments */
void Mating(SearchSpace *s, int pride, int *n_offsprings, prtFun Evaluate, va_list arg)
{
  int i, j, k;
  int n_matting_females = 0, n_matting_males = 0;
  int male_index = s->pride_id[pride].n_males;     /* index position indicator for the new array of porintes (male) */
  int female_index = s->pride_id[pride].n_females; /* index position indicator for the new array of porintes (female) */
  int *selected_female = NULL;                     /* array indicating if a female was selected for matting */
  int *selected_male = NULL;                       /* array indicating if a male was selected for matting */
  double prob, Beta, sum;
  Agent **temp_males = NULL;   /* array of pointes to allocate new male cubs */
  Agent **temp_females = NULL; /* array of pointes to allocate new female cubs */
  /* each  selected female generate 2 cubs, a male and a female */
  Agent *offspring1 = NULL;
  Agent *offspring2 = NULL;

  /* allocating the 'selected' arrays */
  selected_female = (int *)calloc(s->pride_id[pride].n_females, sizeof(int));
  selected_male = (int *)calloc(s->pride_id[pride].n_males, sizeof(int));

  /* determining the number of female lions that will mate and which ones */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    prob = GenerateUniformRandomNumber(0, 1);
    if (prob <= s->mating_prob)
    {
      n_matting_females++;
      selected_female[i] = 1; /* mark the female as selected */
    }
  }

  /* determining the number of offsprings */
  *n_offsprings = 2 * n_matting_females; /* half males and half females */

  /* allocating the new arrays of agents*/
  temp_males = (Agent **)malloc((s->pride_id[pride].n_males + (int)(*n_offsprings / 2)) * sizeof(Agent *));
  temp_females = (Agent **)malloc((s->pride_id[pride].n_females + (int)(*n_offsprings / 2)) * sizeof(Agent *));

  /* copying the old arrays of agents to the new ones*/
  /* for males */
  for (i = 0; i < s->pride_id[pride].n_males; i++)
    temp_males[i] = s->pride_id[pride].males[i];
  /* for females */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
    temp_females[i] = s->pride_id[pride].females[i];

  /* dealocating the old arrays of agents */
  free(s->pride_id[pride].males);
  free(s->pride_id[pride].females);

  /* pointing the old ones to the new ones */
  s->pride_id[pride].males = temp_males;
  s->pride_id[pride].females = temp_females;

  /* Generating the offsprings */
  /* for each old female selected for matting */
  for (i = 0; i < s->pride_id[pride].n_females; i++)
  {
    if (selected_female[i])
    {
      n_matting_males = 0;
      /* the selected female needs to mate with, at least, one male. */
      do
      {
        /* determining which males and how many will matte with the ith female (50% each) */
        for (j = 0; j < s->pride_id[pride].n_males; j++)
        {
          prob = GenerateUniformRandomNumber(0, 1);
          if (prob <= 0.5)
          {
            selected_male[j] = 1; /* mark the female as selected */
            n_matting_males++;
          }
        }
      } while (n_matting_males == 0);
      /* allocating the offsprings */
      offspring1 = CreateAgent(s->n, _LOA_, _NOTENSOR_);
      offspring2 = CreateAgent(s->n, _LOA_, _NOTENSOR_);
      Beta = GenerateGaussianRandomNumber(0.5, 0.01); /* 0.01 indicates variance. The stand deviation is 0.1 */
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
      {
        /* summing the jth decision variale of all selected males */
        sum = 0;
        for (k = 0; k < s->pride_id[pride].n_males; k++)
        {
          if (selected_male[k])
            sum += s->pride_id[pride].males[k]->x[j];
        }
        offspring1->x[j] = Beta * s->pride_id[pride].females[i]->x[j] + (1 - Beta) / n_matting_males * sum;
        offspring2->x[j] = (1 - Beta) * s->pride_id[pride].females[i]->x[j] + Beta / n_matting_males * sum;
      }
      /* randomly selecting one of the offsprings as a male and the other one as female */
      prob = GenerateUniformRandomNumber(0, 1);
      /* offspring1 is a male and offspring2 is a female*/
      if (prob <= 0.5)
      {
        s->pride_id[pride].males[male_index] = offspring1;
        s->pride_id[pride].females[female_index] = offspring2;
      }
      /* offspring1 is a female and offspring2 is a male*/
      else
      {
        s->pride_id[pride].females[female_index] = offspring1;
        s->pride_id[pride].males[male_index] = offspring2;
      }
      /* selecting one of the cubs to have a mutation */
      prob = GenerateUniformRandomNumber(0, 1);
      /* offspring1 will mutate */
      if (prob <= 0.5)
      {
        /* for each decision variable */
        for (j = 0; j < s->n; j++)
        {
          prob = GenerateUniformRandomNumber(0, 1);
          if (prob <= s->pMutation)
            offspring1->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
        }
      }
      /* offspring2 will mutate*/
      else
      {
        /* for each decision variable */
        for (j = 0; j < s->n; j++)
        {
          prob = GenerateUniformRandomNumber(0, 1);
          if (prob <= s->pMutation)
            offspring2->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
        }
      }

      /* cheking the limits of the new agents */
      CheckAgentLimits(s, offspring1);
      CheckAgentLimits(s, offspring2);
      /* evaluating the offsprings */
      EvaluateAgent(s, offspring1, _LOA_, Evaluate, arg);
      EvaluateAgent(s, offspring2, _LOA_, Evaluate, arg);
      /* moving the idexes */
      male_index++;
      female_index++;
      /* zeroing the agents pointes */
      offspring1 = NULL;
      offspring2 = NULL;
      /* if is not the last iteraction */
      if (i < s->pride_id[pride].n_females - 1)
      {
        /* reseting the selected_males array */
        for (j = 0; j < s->pride_id[pride].n_males; j++)
          selected_male[j] = 0;
      }
    }
  }

  free(selected_female);
  free(selected_male);
}

/* A nomad female mate with one nomad male with a determined probability, producing 2 offsprings(a male and a female)
Parameters:
s: search space
n_offsprings: number of offsprings that will be generated by nomad matting
extra_male_nomads: number of extra male nomads that moved out from the prides
Evaluate: pointer to the function used to evaluate the cubs
arg: list of additional arguments */
void NomadMating(SearchSpace *s, int *n_offsprings, int extra_male_nomads, prtFun Evaluate, va_list arg)
{
  int i, j, k;
  int n_matting_females = 0;
  int male_index = s->n_male_nomads + extra_male_nomads; /* index position indicator for the new array of porintes (male) */
  int female_index = s->n_female_nomads;                 /* index position indicator for the new array of porintes (female) */
  int *selected_female = NULL;                           /* array indicating if a female was selected for matting */
  int selected_male;                                     /* index of selected male */
  double prob, Beta;
  Agent **temp_males = NULL;   /* array of pointes to allocate new male cubs */
  Agent **temp_females = NULL; /* array of pointes to allocate new female cubs */
  /* each  selected female generate 2 cubs, a male and a female */
  Agent *offspring1 = NULL;
  Agent *offspring2 = NULL;

  /* allocating the 'selected' arrays */
  selected_female = (int *)calloc(s->n_female_nomads, sizeof(int));

  /* determining the number of female lions that will mate and which ones */
  for (i = 0; i < s->n_female_nomads; i++)
  {
    prob = GenerateUniformRandomNumber(0, 1);
    if (prob <= s->mating_prob)
    {
      n_matting_females++;
      selected_female[i] = 1; /* mark the female as selected */
    }
  }

  /* determining the number of offsprings */
  *n_offsprings = 2 * n_matting_females; /* half males and half females */

  /* allocating the new arrays of agents*/
  temp_males = (Agent **)malloc((s->n_male_nomads + extra_male_nomads + (int)(*n_offsprings / 2)) * sizeof(Agent *));
  temp_females = (Agent **)malloc((s->n_female_nomads + (int)(*n_offsprings / 2)) * sizeof(Agent *));

  /* copying the old arrays of agents to the new ones*/
  /* for males */
  for (i = 0; i < s->n_male_nomads + extra_male_nomads; i++)
    temp_males[i] = s->male_nomads[i];
  /* for females */
  for (i = 0; i < s->n_female_nomads; i++)
    temp_females[i] = s->female_nomads[i];

  /* dealocating the old arrays of agents */
  free(s->male_nomads);
  free(s->female_nomads);

  /* pointing the old ones to the new ones */
  s->male_nomads = temp_males;
  s->female_nomads = temp_females;

  /* Generating the offsprings */
  /* for each old female selected for matting */
  for (i = 0; i < s->n_female_nomads; i++)
  {
    if (selected_female[i])
    {
      /* selecting a random male for mating with the ith selected female */
      selected_male = (int)GenerateUniformRandomNumber(0, s->n_male_nomads + extra_male_nomads - 0.001);
      /* allocating the offsprings */
      offspring1 = CreateAgent(s->n, _LOA_, _NOTENSOR_);
      offspring2 = CreateAgent(s->n, _LOA_, _NOTENSOR_);
      Beta = GenerateGaussianRandomNumber(0.5, 0.01); /* 0.01 indicates variance. The standard deviation is 0.1 */
      /* for each decision variable */
      for (j = 0; j < s->n; j++)
      {
        offspring1->x[j] = Beta * s->female_nomads[i]->x[j] + (1 - Beta) * s->male_nomads[selected_male]->x[j];
        offspring2->x[j] = (1 - Beta) * s->female_nomads[i]->x[j] + Beta * s->male_nomads[selected_male]->x[j];
      }
      /* randomly selecting one of the offsprings as a male and the other one as female */
      prob = GenerateUniformRandomNumber(0, 1);
      /* offspring1 is a male and offspring2 is a female */
      if (prob <= 0.5)
      {
        s->male_nomads[male_index] = offspring1;
        s->female_nomads[female_index] = offspring2;
      }
      /* offspring1 is a female and offspring2 is a male*/
      else
      {
        s->female_nomads[female_index] = offspring1;
        s->male_nomads[male_index] = offspring2;
      }
      /* selecting one of the cubs to have a mutation */
      prob = GenerateUniformRandomNumber(0, 1);
      /* offspring1 will mutate */
      if (prob <= 0.5)
      {
        /* for each decision variable */
        for (j = 0; j < s->n; j++)
        {
          prob = GenerateUniformRandomNumber(0, 1);
          if (prob <= s->pMutation)
            offspring1->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
        }
      }
      /* offspring2 will mutate*/
      else
      {
        /* for each decision variable */
        for (j = 0; j < s->n; j++)
        {
          prob = GenerateUniformRandomNumber(0, 1);
          if (prob <= s->pMutation)
            offspring2->x[j] = GenerateUniformRandomNumber(s->LB[j], s->UB[j]);
        }
      }

      /* cheking the limits of the new agents */
      CheckAgentLimits(s, offspring1);
      CheckAgentLimits(s, offspring2);
      /* evaluating the offsprings */
      EvaluateAgent(s, offspring1, _LOA_, Evaluate, arg);
      EvaluateAgent(s, offspring2, _LOA_, Evaluate, arg);
      /* moving the idexes */
      male_index++;
      female_index++;
      /* zeroing the agents pointes */
      offspring1 = NULL;
      offspring2 = NULL;
    }
  }
  free(selected_female);
}

/* In each pride, male lions become mature and fight with other males in their pride. Beaten males abandon their pride and become a nomad
Parameters:
s: search space
pride: pride identification number
n_male_offsprings: number of male offsprings generated by matting (half of total offsprings)
extra_male_nomads: number of extra male nomads that moved out from the prides */
void Defense(SearchSpace *s, int pride, int n_male_offsprings, int extra_male_nomads)
{
  int i;
  Agent **new_residents = NULL;
  Agent **temp_nomads = NULL;

  /* sorting male lions by fitness */
  qsort(s->pride_id[pride].males, s->pride_id[pride].n_males + n_male_offsprings, sizeof(Agent **), SortAgent);

  /* allocating the new arrays of agents*/
  new_residents = (Agent **)malloc(s->pride_id[pride].n_males * sizeof(Agent *));
  temp_nomads = (Agent **)malloc((s->n_male_nomads + extra_male_nomads + n_male_offsprings) * sizeof(Agent *));

  /* copying the best agents of the old array to the new one */
  /* for resident males */
  for (i = 0; i < s->pride_id[pride].n_males; i++)
    new_residents[i] = s->pride_id[pride].males[i];
  /* for nomad males */
  for (i = 0; i < s->n_male_nomads + extra_male_nomads; i++)
    temp_nomads[i] = s->male_nomads[i];

  /* adding the excess of males in pride to nomad males array */
  for (i = 0; i < n_male_offsprings; i++)
    temp_nomads[i + s->n_male_nomads + extra_male_nomads] = s->pride_id[pride].males[i + s->pride_id[pride].n_males];

  /* dealocating the old arrays of agents */
  free(s->male_nomads);
  free(s->pride_id[pride].males);

  /* pointing the old ones to the new ones */
  s->male_nomads = temp_nomads;
  s->pride_id[pride].males = new_residents;
}

/* Every nomad lion try to atack some prides, if the nomad is stronger (best fitness) than lion from the pride, they swap its positions
Parameters:
s: search space
n_nomad_male_offspring: number of male offsprings generated by nomad matting (half of total offsprings)
extra_male_nomads: number of extra male nomads that moved out from the prides */
void AtackPride(SearchSpace *s, int n_nomad_male_offspring, int extra_male_nomads)
{
  int i, j, k;
  int swapped; /* indicates if a swap happened. If the ith nomad male swap with a other male, the 2 inner loops stop and we try the next nomad male. */
  double prob;
  Agent *aux = NULL;

  /* for each nomad male (including nomad offsprings and kicked out males from pride that became nomad) */
  for (i = 0; i < s->n_male_nomads + n_nomad_male_offspring + extra_male_nomads; i++)
  {
    swapped = 0;
    /* determining if a pride will be attacked by the ith male */
    for (j = 0; j < s->n_prides && !swapped; j++)
    {
      prob = GenerateUniformRandomNumber(0, 1);
      /* the jth pride will be attacked */
      if (prob <= 0.5)
      {
        /* for each male in the jth pride */
        for (k = 0; k < s->pride_id[j].n_males && !swapped; k++)
        {
          /* if the ith nomad is better than the kth male of the jth pride */
          if (s->male_nomads[i]->fit < s->pride_id[j].males[k]->fit)
          {
            /* swap the lions. Male from pride become nomad and nomad become a resident male */
            aux = s->pride_id[j].males[k];
            s->pride_id[j].males[k] = s->male_nomads[i];
            s->male_nomads[i] = aux;
            swapped = 1;
          }
        }
      }
    }
  }
}

/* Some randomly selected females will migrate and will become nomads
Parameters:
s: search space
n_offsprings: array that each index contains the number of offsprings of each pride generated by mating
n_nomad_female_offspring: number of female offsprings generated by nomad matting (half of total offsprings)
extra_nomads: number of extra female nomads after pride females become nomads
n_migrating: array that each index contains the number of females that will migrate from each pride */
void Migration(SearchSpace *s, int *n_offsprings, int n_nomad_female_offspring, int *extra_nomads, int *n_migrating)
{
  int i, j, k;
  int *selected = NULL; /* binary array that indicates if a female from a pride will migrate */
  int nomad_index, female_pride_index, index;
  Agent **temp_nomads = NULL;
  Agent **temp_female_pride = NULL;

  nomad_index = s->n_female_nomads + n_nomad_female_offspring; /* start point index to insert migrating females */
  /* determining the number of females that will migrate from each pride */
  *extra_nomads = 0;
  for (i = 0; i < s->n_prides; i++)
  {
    n_migrating[i] = round(s->imigration_rate * s->pride_id[i].n_females) + (int)(n_offsprings[i] / 2);
    *extra_nomads += n_migrating[i];
  }
  /* allocating the new array of female nomads */
  temp_nomads = (Agent **)malloc((s->n_female_nomads + n_nomad_female_offspring + *extra_nomads) * sizeof(Agent *));
  /* copying the old female nomads to the new array */
  for (i = 0; i < s->n_female_nomads + n_nomad_female_offspring; i++)
    temp_nomads[i] = s->female_nomads[i];

  /* freeing the old array of nomads */
  free(s->female_nomads);
  /* pointng to the new array of nomads */
  s->female_nomads = temp_nomads;

  /* for each pride */
  for (i = 0; i < s->n_prides; i++)
  {
    female_pride_index = 0;
    /* allocating the new array of females of ith pride leaving space for nomad females get in (next step of LOA) */
    temp_female_pride = (Agent **)malloc((s->pride_id[i].n_females) * sizeof(Agent *));
    selected = (int *)calloc(s->pride_id[i].n_females + (int)(n_offsprings[i] / 2), sizeof(int));
    /* determining which females will migrate from ith pride */
    for (j = 0; j < n_migrating[i]; j++)
    {
      do
      {
        index = (int)GenerateUniformRandomNumber(0, (s->pride_id[i].n_females + (int)(n_offsprings[i] / 2)) - 0.001);
      } while (selected[index]);
      selected[index] = 1; /* mark as selected */
    }
    /* for each female in ith pride */
    for (j = 0; j < s->pride_id[i].n_females + (int)(n_offsprings[i] / 2); j++)
    {
      if (selected[j])
      {                                                            /* if the female was selected for migration */
        s->female_nomads[nomad_index] = s->pride_id[i].females[j]; /* female become nomad */
        nomad_index++;
      }
      else
      {                                                                    /* copy the pride female to the new array of females of the pride */
        temp_female_pride[female_pride_index] = s->pride_id[i].females[j]; /* stays in pride */
        female_pride_index++;
      }
    }
    /* freeing the old females of the pride array */
    free(s->pride_id[i].females);
    /* pointing to the new array */
    s->pride_id[i].females = temp_female_pride;
    free(selected);
  }
}

/* It executes the Lion Optimization Algorithm for function minimization
Parameters:
s: search space
Evaluate: pointer to the function used to evaluate the cubs */
void runLOA(SearchSpace *s, prtFun Evaluate, ...)
{
  va_list arg;
  int i, k;
  int *selected_females = NULL; /* binary array indicating if a female is hunting or not */
  int n_nomad_offspring, extra_male_nomads, extra_female_nomads, n_fill, pride_index;
  int empty_places[s->n_prides];      /* array that each index indicates the number of empty places in a pride */
  int n_pride_offspring[s->n_prides]; /* array that each index indicates the number of offsprings generated by a pride */
  int n_migrating[s->n_prides];       /* array that indicates the number of females that will migrate from the pride indicated by the index (will be filled in 'Migration')*/
  Agent **new_nomads = NULL;
  va_start(arg, Evaluate);

  EvaluateSearchSpace(s, _LOA_, Evaluate, arg); /* Initial evaluation */
  for (k = 0; k < s->iterations; k++)
  {
    fprintf(stderr, "\nRunning iteration %d/%d ... ", k + 1, s->iterations);
    /* For each pride */
    extra_male_nomads = 0;
    for (i = 0; i < s->n_prides; i++)
    {
      selected_females = (int *)calloc(s->pride_id[i].n_females, sizeof(int));
      Hunting(s, i, selected_females, Evaluate, arg); /* Random selected females go hunting */
      MovingSafePlace(s, i, selected_females, Evaluate, arg); /* the rest of females go toward a safe place*/
      Roaming(s, i, Evaluate, arg); /* each male in a pride roams in that pride's territory */
      Mating(s, i, &n_pride_offspring[i], Evaluate, arg);
      Defense(s, i, (int)(n_pride_offspring[i] / 2), extra_male_nomads);
      extra_male_nomads += (int)(n_pride_offspring[i] / 2);
      free(selected_females);
    }
    /* For Nomads */
    NomadMovingRandom(s, extra_male_nomads, Evaluate, arg);
    NomadMating(s, &n_nomad_offspring, extra_male_nomads, Evaluate, arg);
    /* nomad lions atack pride lions */
    AtackPride(s, (int)(n_nomad_offspring / 2), extra_male_nomads);
    /* females in pride become nomads */
    Migration(s, n_pride_offspring, (int)(n_nomad_offspring / 2), &extra_female_nomads, n_migrating);

    /**** POPULATION EQUILIBRIUM ****/
    /* some nomad females will become pride females, and the worst nomad females will die */
    /* sorting nomad females */
    qsort(s->female_nomads, s->n_female_nomads + (int)(n_nomad_offspring / 2) + extra_female_nomads, sizeof(Agent **), SortAgent);
    /* determinig the number of empty places in each pride and the total number of empty places */
    n_fill = 0;
    for (i = 0; i < s->n_prides; i++)
    {
      empty_places[i] = n_migrating[i] - (int)(n_pride_offspring[i] / 2);
      n_fill += empty_places[i];
    }
    /* the n_fill first females will be distributed randomly to prides to fill the empty places */
    /* for the first n_fill (best) nomad females */
    for (i = 0; i < n_fill; i++)
    {
      do
      {
        pride_index = (int)GenerateUniformRandomNumber(0, s->n_prides - 0.001);          /* destination pride of the ith nomad female */
      } while (!empty_places[pride_index]);                                              /* checks if the pride still have empty places to fill */
      int female_index = s->pride_id[pride_index].n_females - empty_places[pride_index]; /* the index to fill the first empty place in the array of females in pride */
      s->pride_id[pride_index].females[female_index] = s->female_nomads[i];
      empty_places[pride_index]--;
    }
    /* Allocating the new array of female nomads (removing the worst(die) and the best(fill pride) females ) */
    new_nomads = (Agent **)malloc(s->n_female_nomads * sizeof(Agent *));
    /* saving the nomads that will remain nomads */
    for (i = 0; i < s->n_female_nomads; i++)
      new_nomads[i] = s->female_nomads[n_fill + i];
    /* dealocating the worst female nomads */
    for (i = n_fill + s->n_female_nomads; i < (s->n_female_nomads + (int)(n_nomad_offspring / 2) + extra_female_nomads); i++)
      DestroyAgent(&(s->female_nomads[i]), _LOA_);
    /* freeing the old array of nomads */
    free(s->female_nomads);
    /* pointing to the new one */
    s->female_nomads = new_nomads;

    /* the worst males will die */
    /* sorting nomad males */
    qsort(s->male_nomads, s->n_male_nomads + (int)(n_nomad_offspring / 2) + extra_male_nomads, sizeof(Agent **), SortAgent);
    /* Allocating the new array of male nomads */
    new_nomads = (Agent **)malloc(s->n_male_nomads * sizeof(Agent *));
    /* saving the best nomads (will remain nomads) */
    for (i = 0; i < s->n_male_nomads; i++)
      new_nomads[i] = s->male_nomads[i];
    /* dealocating the worst male nomads */
    for (i = s->n_male_nomads; i < s->n_male_nomads + extra_male_nomads + (int)(n_nomad_offspring / 2); i++)
      DestroyAgent(&(s->male_nomads[i]), _LOA_);
    /* freeing the old array of nomads */
    free(s->male_nomads);
    /* pointing to the new one */
    s->male_nomads = new_nomads;

    fprintf(stderr, "OK (minimum fitness value %lf)", s->gfit);
  }
  va_end(arg);
}