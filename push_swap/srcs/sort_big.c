/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:17:06 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 10:38:39 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

static int	get_chunk_size(int len)
{
	if (len >= 80 && len <= 250)
		return (len / 5);
	return (len / 10);
}

static int	can_push(t_stack *stack_a, t_stack *stack_b,
	int len, int *sorted_arr)
{
	(void)len;
	(void)sorted_arr;
	if (stack_b->arr[stack_b->top] == stack_b->top)
	{
		pa(stack_a, stack_b);
		return (1);
	}
	return (0);
}

static int	smart_rotate(t_stack *stack_a,
	t_stack *stack_b, int len, int *sorted_arr)
{
	int	swap;
	int	i;

	swap = 0;
	i = stack_b->top;
	while (stack_b->arr[i] != stack_b->top + 1)
		i--;
	while (stack_b->arr[stack_b->top] != stack_b->top + 1 + swap)
	{
		if (swap == 1 || can_push(stack_a, stack_b, len, sorted_arr) == 0)
		{
			if (i >= stack_b->top / 2)
				rb(stack_b);
			else
				rrb(stack_b);
		}
		else
			swap = 1;
	}
	return (swap);
}

static void	push_back(t_stack *stack_a,
	t_stack *stack_b, int len, int *sorted_arr)
{
	while (stack_b->top > 0)
	{
		if (smart_rotate(stack_a, stack_b, len, sorted_arr))
		{
			pa(stack_a, stack_b);
			sa(stack_a);
		}
		else
			pa(stack_a, stack_b);
	}
	pa(stack_a, stack_b);
}

void	sort_big(t_stack *stack_a, t_stack *stack_b, int len, int *sorted_arr)
{
	int	chunk_size;
	int	current;

	current = 1;
	chunk_size = get_chunk_size(len);
	while (stack_a->top >= 0)
	{
		if (stack_a->arr[stack_a->top] < (chunk_size * current))
		{
			pb(stack_a, stack_b);
			if (stack_b->arr[stack_b->top]
				< chunk_size * current - (chunk_size / 2))
				rb(stack_b);
		}
		else
			ra(stack_a);
		if (stack_b->top + 2 == chunk_size * current)
			current++;
	}
	push_back(stack_a, stack_b, len, sorted_arr);
}
