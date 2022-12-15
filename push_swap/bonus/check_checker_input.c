/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_checker_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:24:07 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 05:48:11 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_header.h"

static int	check_number(char *num)
{
	int	i;

	i = -1;
	if (num == NULL)
		return (0);
	if ((ft_atoi(num) == 0 && ft_strlen(num) != 1)
		|| (ft_atoi(num) == -1 && ft_strlen(num) != 2))
		return (0);
	if (num[0] == '-')
		i++;
	while (num[++i] != '\0')
	{
		if (ft_isdigit(num[i]) == 0)
			return (0);
	}
	return (1);
}

static void	check_number_errors(char **splitted, int numbers,
	t_stack **stack_a, int *index)
{
	int	i;
	int	j;

	i = -1;
	while (splitted[++i] != NULL)
	{
		j = -1;
		while ((*stack_a)->top != -1 && ++j <= (*stack_a)->top)
		{
			if ((*stack_a)->arr[numbers - j - 1] == ft_atoi(splitted[i]))
			{
				ft_putstr_fd("Error\n", STDERR_FILENO);
				while (splitted[i] != NULL)
					free(splitted[i++]);
				free(splitted);
				free((*stack_a)->arr);
				free(*stack_a);
				exit(ERROR_EXIT);
			}
		}
		((*stack_a)->arr)[(*index)--] = ft_atoi(splitted[i]);
		(*stack_a)->top++;
		free(splitted[i]);
	}
	free(splitted);
}

static void	check_input_error(char **splitted, t_stack **stack_a, int *numbers)
{
	int	i;

	i = -1;
	while (splitted[++i] != NULL)
	{
		if (check_number(splitted[i]) == 0)
		{
			while (splitted[i] != NULL)
				free(splitted[i++]);
			free(splitted);
			free(*stack_a);
			ft_putstr_fd("Error\n", STDERR_FILENO);
			exit(ERROR_EXIT);
		}
		free(splitted[i]);
		++(*numbers);
	}
	free(splitted);
}

void	get_stack_a(int ac, char **av, t_stack **stack_a)
{
	int		i;
	int		index;
	int		numbers;
	char	**splitted;

	(void)av;
	*stack_a = malloc(sizeof(t_stack));
	i = 0;
	numbers = 0;
	while (++i < ac)
	{
		splitted = ft_split(av[i], ' ');
		check_input_error(splitted, stack_a, &numbers);
	}
	(*stack_a)->arr = malloc(numbers * sizeof(int));
	(*stack_a)->top = -1;
	index = numbers - 1;
	i = 0;
	while (++i < ac)
	{
		splitted = ft_split(av[i], ' ');
		check_number_errors(splitted, numbers, stack_a, &index);
	}
}

void	get_stack_b(int top, t_stack **stack_b)
{
	int	i;

	*stack_b = malloc(sizeof(t_stack));
	(*stack_b)->top = -1;
	(*stack_b)->arr = malloc((top + 1) * sizeof(int));
	i = -1;
	while (++i <= top)
		(*stack_b)->arr[i] = 0;
}
