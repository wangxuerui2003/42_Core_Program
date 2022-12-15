/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:07:53 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 05:40:54 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_header.h"

static int	*ps_copy_arr(int *arr, int len)
{
	int	i;
	int	*new_arr;

	i = -1;
	new_arr = malloc(len * sizeof(int));
	while (++i < len)
		new_arr[i] = arr[i];
	return (new_arr);
}

static void	indexing_stack(int *stack_arr, int *sorted_arr, int len)
{
	int	i;
	int	j;

	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
		{
			if (stack_arr[i] == sorted_arr[j])
			{
				stack_arr[i] = j + 1;
				j = len;
			}
		}
	}
}

static void	sort(t_stack *stack_a,
	t_stack *stack_b, int len, int *sorted_arr)
{
	if (stack_a->top == 2)
		sort_three(stack_a);
	if (len >= 100)
		sort_big(stack_a, stack_b, len, sorted_arr);
	else
		sort_small(stack_a, stack_b, len, sorted_arr);
}

int	main(int ac, char **av)
{
	int		len;
	int		i;
	int		*sorted_arr;
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (ac < 2)
		exit(0);
	get_stack_a(ac, av, &stack_a);
	len = stack_a->top + 1;
	get_stack_b(stack_a->top, &stack_b);
	sorted_arr = ps_copy_arr(stack_a->arr, len);
	ft_quick_sort(sorted_arr, 0, len - 1);
	indexing_stack(stack_a->arr, sorted_arr, len);
	i = 0;
	while (++i <= len)
		sorted_arr[i - 1] = i;
	sort(stack_a, stack_b, len, sorted_arr);
	free(stack_a->arr);
	free(stack_b->arr);
	free(stack_a);
	free(stack_b);
	free(sorted_arr);
}
