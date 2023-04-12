/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:31 by wxuerui           #+#    #+#             */
/*   Updated: 2023/02/27 22:05:19 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_isposint(char *num)
{
	int	i;

	i = -1;
	if (num == NULL || num[0] == '0')
		return (false);
	while (num[++i] != '\0')
	{
		if (num[i] < '0' || num[i] > '9')
			return (0);
	}
	return (1);
}

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

int	error_output(char *msg)
{
	int	i;

	i = -1;
	while (msg[++i] != '\0')
		write(STDERR_FILENO, msg + i, 1);
	write(STDERR_FILENO, "\n", 1);
	return (i + 1);
}

int	get_sim_state(t_args *args)
{
	int	state;

	pthread_mutex_lock(&(args->statecheck_lock));
	state = args->sim_state;
	pthread_mutex_unlock(&(args->statecheck_lock));
	return (state);
}

void	update_sim_state(t_args *args, int state)
{
	pthread_mutex_lock(&(args->statecheck_lock));
	args->sim_state = state;
	pthread_mutex_unlock(&(args->statecheck_lock));
}
