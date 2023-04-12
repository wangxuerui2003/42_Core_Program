/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:20 by wxuerui           #+#    #+#             */
/*   Updated: 2023/03/01 13:49:40 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_routine(t_philosopher *philosophers, t_args *args)
{
	int	i;

	i = -1;
	gettimeofday(&(args->start_time), NULL);
	while (++i < args->input[N_PHILO])
	{
		gettimeofday(&(philosophers[i].last_eat), NULL);
		if (pthread_create(&(philosophers[i].tid), NULL,
				philo_routine, &(philosophers[i])) == -1)
			return (false);
		if (pthread_create(&(philosophers[i].checker_tid),
				NULL, checker_routine, &(philosophers[i])) == -1)
			return (false);
		pthread_detach(philosophers[i].checker_tid);
	}
	return (true);
}

t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philosopher) * args->input[N_PHILO]);
	if (philosophers == NULL)
		return (NULL);
	i = -1;
	while (++i < args->input[N_PHILO])
	{
		philosophers[i].id = i + 1;
		philosophers[i].left_fork = &(forks[i]);
		philosophers[i].right_fork = &(forks[(i + 1) % args->input[N_PHILO]]);
		philosophers[i].args = args;
		if (pthread_mutex_init(&(philosophers[i].checker_lock), NULL) == -1)
			return (NULL);
		philosophers[i].n_eat = 0;
	}
	return (philosophers);
}

pthread_mutex_t	*init_forks(t_args *args)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * args->input[N_PHILO]);
	if (forks == NULL)
		return (NULL);
	i = -1;
	while (++i < args->input[N_PHILO])
	{
		if (pthread_mutex_init(&(forks[i]), NULL) == -1)
			return (NULL);
	}
	return (forks);
}

bool	init_args(t_args *args, int ac, char **av)
{
	int	i;

	i = 0;
	args->input[N_EAT] = -1;
	while (++i < ac)
	{
		if (ft_isposint(av[i]) == false)
			return (false);
		args->input[i - 1] = ft_atoi(av[i]);
	}
	args->sim_state = DOING;
	args->eat_left = args->input[N_PHILO];
	if (pthread_mutex_init(&(args->printer_lock), NULL) == -1)
		return (false);
	if (pthread_mutex_init(&(args->statecheck_lock), NULL) == -1)
		return (false);
	if (pthread_mutex_init(&(args->eat_protector), NULL) == -1)
		return (false);
	if (pthread_mutex_init(&(args->deathcheck_lock), NULL) == -1)
		return (false);
	return (true);
}
