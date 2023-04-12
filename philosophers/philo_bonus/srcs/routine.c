/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:41:21 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 19:08:37 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	should_die(t_philo *self)
{
	if (self->args->num_philo % 2 == 1)
	{
		if (self->args->num_philo == 1
			|| self->args->time_eat * 3 >= self->args->time_die
			|| (self->args->time_eat * 2 + self->args->time_sleep)
			>= self->args->time_die)
			return (true);
	}
	else
	{
		if (self->args->time_eat * 2 >= self->args->time_die
			|| (self->args->time_eat + self->args->time_sleep)
			>= self->args->time_die)
			return (true);
	}
	return (false);
}

/**
 * @brief An infinite loop with 500us delay checking if the philosopher is dead
 * 
 * @param arg 
 * @return void* 
 */
void	*check_philo_status(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (usleep(500) == 0)
	{
		i = -1;
		while (++i < philo->args->num_philo)
		{
			if (check_death(philo) == 1)
				exit(SIGKILL);
		}
	}
	return (NULL);
}

/**
 * @brief Give some delay for even id philosophers to prevent the situation
 * that everyone has a fork and all dead.
 * Take 2 forks using sem_wait() and eat with protection
 * to prevent dying while eating.
 * Then release the forks and sleep.
 * 
 * @param self 
 * @param forks 
 */
void	routine(t_philo *self, sem_t *forks)
{
	if ((self->id) % 2 == 0)
		usleep(1000);
	while (true)
	{
		sem_wait(forks);
		philo_talk(self, WAITING);
		sem_wait(forks);
		philo_talk(self, WAITING);
		philo_talk(self, EATING);
		sem_wait(self->args->eat_protector);
		gettimeofday(&(self->last_eat), NULL);
		sem_post(self->args->eat_protector);
		usleep(self->args->time_eat * 1000);
		sem_post(forks);
		sem_post(forks);
		self->times_ate++;
		if (self->times_ate == self->args->must_eat)
			exit(EXIT_SUCCESS);
		philo_talk(self, SLEEPING);
		usleep(self->args->time_sleep * 1000);
		philo_talk(self, THINKING);
	}
}

/**
 * @brief Create the philosopher instance and create the death checking thread.
 * Then start the routine.
 * 
 * @param args 
 * @param forks 
 * @param id 
 */
void	philosophizing(t_args *args, sem_t *forks, int id)
{
	t_philo			self;
	pthread_t		check_status_tid;

	gettimeofday(&(args->start_time), NULL);
	self.id = id;
	self.times_ate = 0;
	self.last_eat = args->start_time;
	self.args = args;
	if (should_die(&self) == true)
	{
		if (pthread_create(&check_status_tid, NULL,
				check_philo_status, &self) != 0)
			error_exit(EMSG_T_CREATE);
		if (pthread_detach(check_status_tid) != 0)
			error_exit(EMSG_T_DETACH);
	}
	routine(&self, forks);
}

/**
 * @brief Start the simulation by posting the semaphore just enough times
 * so all philosophers can pass the lock.
 * 
 * @param args 
 */
void	start_simulation(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->num_philo)
		sem_post(args->start_simulation);
}
