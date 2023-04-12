/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:28 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 18:49:43 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	should_die(t_philosopher *self)
{
	int	*input;
	int	is_odd;

	input = self->args->input;
	is_odd = input[N_PHILO] % 2;
	if (is_odd)
	{
		if (input[N_PHILO] == 1 || input[MS_EAT] * 3 >= input[MS_DIE]
			|| input[MS_EAT] * 2 + input[MS_SLEEP] >= input[MS_DIE])
			return (true);
	}
	else
	{
		if (input[MS_EAT] * 2 >= input[MS_DIE]
			|| input[MS_EAT] + input[MS_SLEEP] >= input[MS_DIE])
			return (true);
	}
	return (false);
}

static bool	finish_eating(t_philosopher *self)
{
	if (get_sim_state(self->args) == DONE)
		return (true);
	if (self->args->input[N_EAT] == -1)
		return (false);
	pthread_mutex_lock(&(self->checker_lock));
	if (self->n_eat == self->args->input[N_EAT])
	{
		pthread_mutex_unlock(&(self->checker_lock));
		return (true);
	}
	pthread_mutex_unlock(&(self->checker_lock));
	return (false);
}

static bool	check_death(t_philosopher *self)
{
	struct timeval	now;

	if (get_sim_state(self->args) == DONE)
		return (true);
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&(self->args->deathcheck_lock));
	pthread_mutex_lock(&(self->checker_lock));
	if ((now.tv_sec - self->last_eat.tv_sec) * 1000 + (now.tv_usec
			- self->last_eat.tv_usec) / 1000 >= self->args->input[MS_DIE])
	{
		philo_talk(self, DIED);
		update_sim_state(self->args, DONE);
		pthread_mutex_unlock(&(self->args->deathcheck_lock));
		pthread_mutex_unlock(&(self->checker_lock));
		return (true);
	}
	pthread_mutex_unlock(&(self->checker_lock));
	pthread_mutex_unlock(&(self->args->deathcheck_lock));
	return (false);
}

void	*checker_routine(void *arg)
{
	t_philosopher	*self;
	bool			should_check_death;

	self = (t_philosopher *)arg;
	should_check_death = should_die(self);
	while (usleep(500) == 0)
	{
		if (should_check_death && check_death(self) == true)
		{
			pthread_mutex_unlock(self->left_fork);
			pthread_mutex_unlock(self->right_fork);
			return (NULL);
		}
		else if (finish_eating(self) == true)
		{
			pthread_mutex_lock(&(self->args->eat_protector));
			(self->args->eat_left)--;
			if (self->args->eat_left == 0)
				update_sim_state(self->args, DONE);
			pthread_mutex_unlock(&(self->args->eat_protector));
			return (NULL);
		}
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*self;

	self = (t_philosopher *)arg;
	if (self->id % 2 == 0)
		usleep(500);
	while (get_sim_state(self->args) == DOING)
	{
		pthread_mutex_lock(self->left_fork);
		philo_talk(self, WAITING);
		pthread_mutex_lock(self->right_fork);
		philo_talk(self, WAITING);
		pthread_mutex_lock(&(self->checker_lock));
		gettimeofday(&(self->last_eat), NULL);
		(self->n_eat)++;
		pthread_mutex_unlock(&(self->checker_lock));
		philo_talk(self, EATING);
		usleep(self->args->input[MS_EAT] * 1000);
		pthread_mutex_unlock(self->right_fork);
		pthread_mutex_unlock(self->left_fork);
		philo_talk(self, SLEEPING);
		usleep(self->args->input[MS_SLEEP] * 1000);
		philo_talk(self, THINKING);
	}
	return (NULL);
}
