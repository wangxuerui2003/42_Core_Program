/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:15:10 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/09 23:34:14 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

void	sa(t_stack *stack_a)
{
	if (stack_a->top < 1)
		return ;
	ft_swap(&(stack_a->arr[stack_a->top]), &(stack_a->arr[stack_a->top - 1]));
	ft_putstr_fd("sa\n", 1);
}

void	sb(t_stack *stack_b)
{
	if (stack_b->top < 1)
		return ;
	ft_swap(&(stack_b->arr[stack_b->top]), &(stack_b->arr[stack_b->top - 1]));
	ft_putstr_fd("sb\n", 1);
}

void	ss(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top < 1)
		return ;
	ft_swap(&(stack_a->arr[stack_a->top]), &(stack_a->arr[stack_a->top - 1]));
	if (stack_b->top < 1)
		return ;
	ft_swap(&(stack_b->arr[stack_b->top]), &(stack_b->arr[stack_b->top - 1]));
	ft_putstr_fd("ss\n", 1);
}

void	pa(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_b->top == -1)
		return ;
	stack_a->top++;
	stack_a->arr[stack_a->top] = stack_b->arr[stack_b->top];
	stack_b->arr[stack_b->top] = 0;
	stack_b->top--;
	ft_putstr_fd("pa\n", 1);
}

void	pb(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->top == -1)
		return ;
	stack_b->top++;
	stack_b->arr[stack_b->top] = stack_a->arr[stack_a->top];
	stack_a->arr[stack_a->top] = 0;
	stack_a->top--;
	ft_putstr_fd("pb\n", 1);
}
