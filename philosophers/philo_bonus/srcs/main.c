/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:09:37 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 19:08:02 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Wait for any child process (philosopher) and check the exit signal,
 * if exited with EXIT_FAILURE, that means some function caused an error,
 * if exited with SIGKILL, that means some philosopher died,
 * for both situations, kill all the other processes and exit.
 * 
 * @param args 
 * @param philos 
 */
void	wait_for_deathnerror(t_args *args, t_philo *philos)
{
	int			i;
	int			estatus;

	i = -1;
	while (++i < args->num_philo)
	{
		waitpid(-1, &estatus, 0);
		if (WEXITSTATUS(estatus) == SIGKILL)
		{
			i = -1;
			while (++i < args->num_philo)
				kill(philos[i].pid, SIGINT);
			return ;
		}
		else if (WEXITSTATUS(estatus) == EXIT_FAILURE)
		{
			i = -1;
			while (++i < args->num_philo)
				kill(philos[i].pid, EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * @brief Wait for any child process (philosopher) and check the exit signal,
 * if exited with EXIT_FAILURE, that means some function caused an error,
 * if exited with SIGKILL, that means some philosopher died,
 * for both situations, kill all the other processes and exit.
 * If exited normally, means a philo has finished eating.
 * @param args 
 * @param philos 
 */
void	wait_for_philos(t_args *args, t_philo *philos)
{
	int		i;
	int		estatus;

	i = -1;
	while (++i < args->num_philo)
	{
		waitpid(-1, &estatus, 0);
		if (WEXITSTATUS(estatus) == SIGKILL)
		{
			i = -1;
			while (++i < args->num_philo)
				kill(philos[i].pid, SIGINT);
			return ;
		}
		else if (WEXITSTATUS(estatus) == EXIT_FAILURE)
		{
			i = -1;
			while (++i < args->num_philo)
				kill(philos[i].pid, EXIT_FAILURE);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * @brief Close all semaphores and free all heap allocated memory
 * 
 * @param args 
 * @param philos 
 * @param forks 
 */
void	terminate(t_args *args, t_philo *philos, sem_t *forks)
{
	sem_close(forks);
	sem_close(args->start_simulation);
	sem_close(args->sem_print);
	free(args);
	free(philos);
}

int	main(int ac, char **av)
{
	t_args	*args;
	sem_t	*forks;
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		error_exit(EMSG_USAGE);
	args = take_input(ac, av);
	forks = create_forks(args);
	philos = init_simulation(args, forks);
	start_simulation(args);
	wait_for_philos(args, philos);
	terminate(args, philos, forks);
	return (0);
}
