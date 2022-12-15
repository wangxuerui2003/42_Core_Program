/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:17:40 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/09 22:18:50 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

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

int	fully_sorted(t_stack *stack_a, int *sorted_arr, int len)
{
	int	i;
	int	j;

	i = stack_a->top;
	j = -1;
	if (stack_a->top != len - 1)
		return (0);
	while (i >= 0)
	{
		if (stack_a->arr[i] != sorted_arr[++j])
			return (0);
		--i;
	}
	return (1);
}
