/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:25:44 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 05:29:42 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_header.h"

void	sa(t_stack *stack_a)
{
	if (stack_a->top < 1)
		return ;
	ft_swap(&(stack_a->arr[stack_a->top]), &(stack_a->arr[stack_a->top - 1]));
}

void	sb(t_stack *stack_b)
{
	if (stack_b->top < 1)
		return ;
	ft_swap(&(stack_b->arr[stack_b->top]), &(stack_b->arr[stack_b->top - 1]));
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_b->top == -1)
		return ;
	stack_a->top++;
	stack_a->arr[stack_a->top] = stack_b->arr[stack_b->top];
	stack_b->arr[stack_b->top] = 0;
	stack_b->top--;
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top == -1)
		return ;
	stack_b->top++;
	stack_b->arr[stack_b->top] = stack_a->arr[stack_a->top];
	stack_a->arr[stack_a->top] = 0;
	stack_a->top--;
}
