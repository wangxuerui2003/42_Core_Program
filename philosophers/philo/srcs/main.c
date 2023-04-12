/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:25 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/01 19:13:07 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_talk(t_philosopher *philosopher, int philo_state)
{
	struct timeval	now;
	time_t			sim_time;

	pthread_mutex_lock(&(philosopher->args->printer_lock));
	gettimeofday(&now, NULL);
	sim_time = (now.tv_sec - philosopher->args->start_time.tv_sec) * 1000
		+ (now.tv_usec - philosopher->args->start_time.tv_usec) / 1000;
	if (get_sim_state(philosopher->args) == DONE)
	{
		pthread_mutex_unlock(&(philosopher->args->printer_lock));
		return ;
	}
	if (philo_state == EATING)
		printf(GREEN "%ld %i is eating\n" RESET, sim_time, philosopher->id);
	else if (philo_state == THINKING)
		printf(BLUE "%ld %i is thinking\n" RESET, sim_time, philosopher->id);
	else if (philo_state == SLEEPING)
		printf(MAGENTA "%ld %i is sleeping\n" RESET, sim_time, philosopher->id);
	else if (philo_state == WAITING)
		printf(YELLOW "%ld %i has taken a fork\n" RESET,
			sim_time, philosopher->id);
	else
		printf(RED "%ld %i died\n" RESET, sim_time, philosopher->id);
	pthread_mutex_unlock(&(philosopher->args->printer_lock));
}

void	terminate(t_philosopher *philosophers, pthread_mutex_t *forks,
					t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&(args->deathcheck_lock));
	pthread_mutex_unlock(&(args->eat_protector));
	pthread_mutex_unlock(&(args->printer_lock));
	pthread_mutex_unlock(&(args->statecheck_lock));
	while (++i < args->input[N_PHILO])
	{
		pthread_join(philosophers[i].tid, NULL);
		pthread_mutex_unlock(&(philosophers[i].checker_lock));
		pthread_mutex_destroy(&(philosophers[i].checker_lock));
		pthread_mutex_destroy(&(forks[i]));
	}
	pthread_mutex_destroy(&(args->deathcheck_lock));
	pthread_mutex_destroy(&(args->eat_protector));
	pthread_mutex_destroy(&(args->printer_lock));
	pthread_mutex_destroy(&(args->statecheck_lock));
	free(forks);
	free(philosophers);
}

int	main(int ac, char **av)
{
	t_args			args;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;

	if (ac != 5 && ac != 6)
		return (error_output(ERR_ARGS));
	if (init_args(&args, ac, av) == false)
		return (error_output(ERR_VAL));
	forks = init_forks(&args);
	if (forks == NULL)
		return (error_output(ERR_UNKNOWN));
	philosophers = init_philosophers(&args, forks);
	if (philosophers == NULL)
		return (error_output(ERR_UNKNOWN));
	if (start_routine(philosophers, &args) == false)
		return (error_output(ERR_UNKNOWN));
	terminate(philosophers, forks, &args);
	return (0);
}
