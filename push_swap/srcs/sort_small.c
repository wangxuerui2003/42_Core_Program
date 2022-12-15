/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:06:59 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 01:37:46 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

static int	find_index(t_stack *stack, int num)
{
	int	i;
	int	*arr;
	int	top;

	i = 0;
	arr = stack->arr;
	top = stack->top;
	while (i <= top)
	{
		if (arr[i] == num)
			return (i);
		i++;
	}
	return (-1);
}

void	sort_three(t_stack *stack_a)
{
	int	*arr;
	int	top;

	arr = stack_a->arr;
	top = stack_a->top;
	if (arr[top] > arr[top - 1] && arr[top - 1] > arr[0])
	{
		sa(stack_a);
		rra(stack_a);
	}
	if (arr[top] > arr[top - 1] && arr[top - 1] < arr[0] && arr[top] > arr[0])
		ra(stack_a);
	if (arr[top] < arr[top - 1] && arr[top - 1] > arr[0] && arr[top] < arr[0])
	{
		rra(stack_a);
		sa(stack_a);
	}
	if (arr[top] > arr[top - 1] && arr[top] < arr[0] && arr[top - 1] < arr[0])
		sa(stack_a);
	if (arr[top] < arr[top - 1] && arr[top] > arr[0] && arr[0] < arr[top - 1])
		rra(stack_a);
}

void	sort_small(t_stack *stack_a, t_stack *stack_b, int len, int *sorted_arr)
{
	int	min;
	int	min_index;
	int	i;

	(void)len;
	i = -1;
	while (stack_a->top > 2)
	{
		min = sorted_arr[++i];
		min_index = find_index(stack_a, min);
		if (min_index >= stack_a->top / 2)
			while (stack_a->arr[stack_a->top] != min)
				ra(stack_a);
		else
			while (stack_a->arr[stack_a->top] != min)
				rra(stack_a);
		pb(stack_a, stack_b);
	}
	sort_three(stack_a);
	while (stack_b->top >= 0)
		pa(stack_a, stack_b);
}
