/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:16:45 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/09 20:17:13 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

void	ra(t_stack *stack_a)
{
	int	i;

	i = stack_a->top;
	if (stack_a->top < 1)
		return ;
	while (i > 0)
	{
		ft_swap(&stack_a->arr[i], &stack_a->arr[i - 1]);
		i--;
	}
	ft_putstr_fd("ra\n", 1);
}

void	rb(t_stack *stack_b)
{
	int	i;

	i = stack_b->top;
	if (stack_b->top < 1)
		return ;
	while (i > 0)
	{
		ft_swap(&stack_b->arr[i], &stack_b->arr[i - 1]);
		i--;
	}
	ft_putstr_fd("rb\n", 1);
}

void	rra(t_stack *stack_a)
{
	int	i;

	i = 0;
	if (stack_a->top < 1)
		return ;
	while (i < stack_a->top)
	{
		ft_swap(&stack_a->arr[i], &stack_a->arr[i + 1]);
		i++;
	}
	ft_putstr_fd("rra\n", 1);
}

void	rrb(t_stack *stack_b)
{
	int	i;

	i = 0;
	if (stack_b->top < 1)
		return ;
	while (i < stack_b->top)
	{
		ft_swap(&stack_b->arr[i], &stack_b->arr[i + 1]);
		i++;
	}
	ft_putstr_fd("rrb\n", 1);
}
