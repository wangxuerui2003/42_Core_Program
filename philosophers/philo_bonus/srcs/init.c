/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:41:18 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 19:06:12 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Take the arguments from command line, in the order of:
 * number_of_philosophers, time_to_die, time_to_eat, time_to_sleep,
 * [number_of_time_must_eat]
 * 
 * @param ac argc
 * @param av argv
 * @return t_args* Return a pointer to the
 * struct of args back to the main function
 */
t_args	*take_input(int ac, char **av)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		error_exit(EMSG_MEMORY);
	if (!(ft_isposint(av[1]) && ft_isposint(av[2])
			&& ft_isposint(av[3]) && ft_isposint(av[4])))
		error_exit(EMSG_INVALID_ARG);
	args->num_philo = ft_atoi(av[1]);
	if (args->num_philo == 0)
		error_exit(EMSG_INVALID_ARG);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	args->must_eat = -1;
	if (ac == 6)
	{
		if (ft_isposint(av[5]) == 0)
			error_exit(EMSG_INVALID_ARG);
		args->must_eat = ft_atoi(av[5]);
	}
	return (args);
}

/**
 * @brief Create forks by giving an initial value num_philo
 * to a named semaphore called "forks".
 * 
 * @param args t_args *
 * @return sem_t* 
 */
sem_t	*create_forks(t_args *args)
{
	sem_t	*forks;

	forks = sem_open("forks", O_CREAT, 0644, args->num_philo);
	if (forks == SEM_FAILED)
		error_exit(EMSG_SEM_OPEN);
	if (sem_unlink("forks") != 0)
		error_exit(EMSG_SEM_UNLINK);
	return (forks);
}

/**
 * @brief Init named semaphore "start", "printer"
 * and "eat_protector".
 * 
 * @param args 
 */
void	init_semaphores(t_args *args)
{
	args->start_simulation = sem_open("start", O_CREAT, 0644, 0);
	if (args->start_simulation == SEM_FAILED)
		error_exit(EMSG_SEM_OPEN);
	if (sem_unlink("start") != 0)
		error_exit(EMSG_SEM_UNLINK);
	args->sem_print = sem_open("printer", O_CREAT, 0644, 1);
	if (args->sem_print == SEM_FAILED)
		error_exit(EMSG_SEM_OPEN);
	if (sem_unlink("printer") != 0)
		error_exit(EMSG_SEM_UNLINK);
	args->eat_protector = sem_open("eat_protector", O_CREAT, 0644, 1);
	if (args->eat_protector == SEM_FAILED)
		error_exit(EMSG_SEM_OPEN);
	if (sem_unlink("eat_protector") != 0)
		error_exit(EMSG_SEM_UNLINK);
}

/**
 * @brief forking the processes (philosophers) and suspend them
 * until the main process executed the start_simulation function.
 * 
 * @param args 
 * @param forks 
 * @return t_philo* philosophers array
 */
t_philo	*init_simulation(t_args *args, sem_t *forks)
{
	int		i;
	int		pid;
	t_philo	*philos;

	init_semaphores(args);
	i = -1;
	philos = malloc(sizeof(t_philo) * args->num_philo);
	if (philos == NULL)
		error_exit(EMSG_MEMORY);
	while (++i < args->num_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			sem_wait(args->start_simulation);
			philosophizing(args, forks, i + 1);
		}
		philos[i].pid = pid;
		philos[i].id = i;
	}
	return (philos);
}
