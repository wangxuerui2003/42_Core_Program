/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:10:02 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 18:34:45 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief ASCII to Integer
 * 
 * @param str The string to be converted
 * @return int Integer converted, or 0 for fail to convert
 */
int	ft_atoi(char *str)
{
	int	num;
	int	i;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == '\n' || str[i] == ' ' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - 48);
	return (num * sign);
}

/**
 * @brief Checks whether the number inputted is positive or 0
 * 
 * @param str the number will be checked
 * @return true 1, false 0
 */
int	ft_isposint(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Philosopher announce their action with semaphore protection
 * preventing 2 philosophers talking at the same time.
 * 
 * @param philo philosopher
 * @param msg the action
 */
void	philo_talk(t_philo *philo, int philo_state)
{
	time_t		sim_time;
	t_timeval	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->args->sem_print);
	sim_time = (now.tv_sec * 1000 - (philo->args->start_time.tv_sec * 1000))
		+ (now.tv_usec / 1000 - philo->args->start_time.tv_usec / 1000);
	if (philo_state == EATING)
		printf(GREEN "%ld %i is eating\n" RESET, sim_time, philo->id);
	else if (philo_state == THINKING)
		printf(BLUE "%ld %i is thinking\n" RESET, sim_time, philo->id);
	else if (philo_state == SLEEPING)
		printf(MAGENTA "%ld %i is sleeping\n" RESET, sim_time, philo->id);
	else if (philo_state == WAITING)
		printf(YELLOW "%ld %i has taken a fork\n" RESET,
			sim_time, philo->id);
	else
		printf(RED "%ld %i died\n" RESET, sim_time, philo->id);
	sem_post(philo->args->sem_print);
}

/**
 * @brief Print a custom error message and exit with error
 * 
 * @param msg Error Message
 */
void	error_exit(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * @brief Check if the philosopher is dead with semaphore protection
 * to protect philosopher from dying while eating, eating here means
 * updating the last_eat timeval.
 * 
 * @param args philo and args
 * @return int 1 for true, 0 for false
 */
int	check_death(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	sem_wait(philo->args->eat_protector);
	if ((now.tv_sec - philo->last_eat.tv_sec) * 1000 + (now.tv_usec
			- philo->last_eat.tv_usec) / 1000 > philo->args->time_die)
	{
		philo_talk(philo, DIED);
		sem_wait(philo->args->sem_print);
		return (1);
	}
	sem_post(philo->args->eat_protector);
	return (0);
}
