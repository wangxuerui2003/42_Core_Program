/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheating_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:27:10 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 06:20:48 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_header.h"

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top < 1)
		return ;
	ft_swap(&(stack_a->arr[stack_a->top]), &(stack_a->arr[stack_a->top - 1]));
	if (stack_b->top < 1)
		return ;
	ft_swap(&(stack_b->arr[stack_b->top]), &(stack_b->arr[stack_b->top - 1]));
}

void	rr(t_stack *stack_a, t_stack *stack_b)
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
	i = stack_b->top;
	if (stack_b->top < 1)
		return ;
	while (i > 0)
	{
		ft_swap(&stack_b->arr[i], &stack_b->arr[i - 1]);
		i--;
	}
}

void	rrr(t_stack *stack_a, t_stack *stack_b)
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
	i = 0;
	if (stack_b->top < 1)
		return ;
	while (i < stack_b->top)
	{
		ft_swap(&stack_b->arr[i], &stack_b->arr[i + 1]);
		i++;
	}
}
