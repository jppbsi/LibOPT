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

#include "sa.h"

/**
 * It calculates the new temperature of the system according to the Boltzmann annealing
 * @param  T0 starting temperature of the system (usually a large number)
 * @param  t current time of the system
 * @return new temperature of the system
 *
 * How to call this funcion from the model file
 * BOLTZMANN_ANNEALING 100.0 # <Cooling Schedule id> <useless for this model>
 */
double boltzmannAnnealing(double T0, double t)
{
  return T0 / log(1 + t);
}

/**
 * It calculates the initial temperature of the system automatically, based on the max number of iterations and the end temperature
 * @param  t_end        End temperature
 * @param  max_iter     Number of iterations
 * @return              Initial temperature of the system for the given number of iterations
 */
double initTemp_boltzmannAnnealing(double t_end, double max_iter)
{
  return t_end * log(1 + max_iter);
}

/**
 * It calculates the new temperature of the system according to the Fast Schedule annealing
 * @param  T current temperature of the system
 * @param  alpha decreasing constant 0.85 < alpha < 0.96
 * @return new temperature of the system
 *
 * How to call this funcion from the model file
 * FAST_SCHEDULE_ANNEALING 0.96 # <Cooling Schedule id> <Constant of temperature decrease>
 */
double fastScheduleAnnealing(double T, double alpha)
{
    return T * alpha;
}

void runSA(SearchSpace *s, prtFun Evaluate, ...)
{
  va_list arg, argtmp;

  va_start(arg, Evaluate);
  va_copy(argtmp, arg);

  if (!s)
  {
    fprintf(stderr, "\nSearch space not allocated @runSA.\n");
    exit(-1);
  }

  /* checking if the auto-temperature is necessary */
  if(s->init_temperature == 0) {
    fprintf(stderr, "\nWarming: Undefined Initial Temperature. We will determine it for you using the number of iterations. Be aware, that is not ideial. Read the SA documentations for more information at sa.h\n\n");

    switch (s->cooling_schedule_id)
    {
      case BOLTZMANN_ANNEALING:
          s->init_temperature = initTemp_boltzmannAnnealing(s->end_temperature, s->iterations);
          break;

      default:
          fprintf(stderr, "\n  Not yet compatible with this cooling schedule. Leaving... \n");
          exit(1);
          break;
    }
  }

  double current_temp; /* current system temperature */
  double prob; /* probability of accepting the new state */
  double T0; /* parameter for the Boltzmann annealing */
  double *new_pos = (double*)malloc(s->n * sizeof(double)); /* array that will store the next position of the particles */
  double *aux_ptr = NULL; /* temporary pointer to store the address of the agent position vector (better explanation below). */
  double prev_fit;
  int i, j;

  /* first evaluation of the search space */
  EvaluateSearchSpace(s, _SA_, Evaluate, arg);

  int t = 1; /* time */
  switch (s->cooling_schedule_id)
  {
    case BOLTZMANN_ANNEALING:
        current_temp = boltzmannAnnealing(s->init_temperature, t);
        break;

    case FAST_SCHEDULE_ANNEALING:
        current_temp = fastScheduleAnnealing(s->init_temperature, s->func_param);
        break;
  }

  while(current_temp > s->end_temperature)
  {
    /* for each particle... */
    for (i = 0; i < s->m; i++)
    {
      /* storing previous fitness of the agent (avoiding re-evaluation) */
      prev_fit = s->a[i]->fit;
      /* storing the address of the x array of the agent */
      aux_ptr = s->a[i]->x;
      /* calculating next random position for the agent */
      for (j = 0; j < s->n; j++)
          new_pos[j] = GenerateUniformRandomNumber(s->a[i]->LB[j], s->a[i]->UB[j]);
      /* poiting the x array of the agent to the new_pos random valued array */
      s->a[i]->x = new_pos; /* new_pos is the new position of the particle right now. */
      /* Evaluating the funcion at new_pos position */
      EvaluateAgent(s, s->a[i], _SA_, Evaluate, arg);
      /* checking if the the next position is an improvement over the last one */
      /* if the next position is better, just update it. */
      if(s->a[i]->fit < prev_fit)
      {
        new_pos = aux_ptr; /* making the old array of the actual agent beeing used for the next iteration. Poiting to the array that was previously from the agent. */
      }
      /* if not, generate a random number and check if the the probability is hight enough. Probability of changing position: e^-(delta_temp/current_temp) */
      else
      {
        // calculating the probability of updating the current state
        prob = exp(- (s->a[i]->fit - prev_fit) / current_temp);
        // if the probability is high enough, keep the next position
        if(prob > GenerateUniformRandomNumber(0, 1))
          new_pos = aux_ptr;
        // the probability is not high enough, we keep where we were
        else
        {
          /* restoring fitness of the agent (avoiding re-evaluation) */
          s->a[i]->fit = prev_fit;
          /* pointing back to the address of the x array of the agent */
          s->a[i]->x = aux_ptr;
        }
      }
    }
    t++;
    /* getting new temperature */
    switch (s->cooling_schedule_id)
    {
      case BOLTZMANN_ANNEALING:
          current_temp = boltzmannAnnealing(s->init_temperature, t);
          break;

      case FAST_SCHEDULE_ANNEALING:
          current_temp = fastScheduleAnnealing(current_temp, s->func_param);
          break;
    }
    fprintf(stderr, "Iteration %d: OK (minimum fitness value %lf). Temperature: %lf\n", t, s->gfit, current_temp);
  }
  free(new_pos);
  va_end(arg);
}
