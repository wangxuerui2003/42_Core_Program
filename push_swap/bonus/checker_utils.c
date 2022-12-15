/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:32:00 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 05:32:08 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_header.h"

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	print_stacks(t_stack *stack_a, t_stack *stack_b, int len)
{
	int	i;

	i = len;
	while (--i >= 0)
		ft_printf("%d\t\t%d\n", stack_a->arr[i], stack_b->arr[i]);
	ft_printf("_\t\t_\n---------------\n");
}
