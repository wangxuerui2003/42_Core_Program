/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:18:24 by wxuerui           #+#    #+#             */
/*   Updated: 2022/08/10 06:35:52 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_header.h"

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

void	choose_op(t_stack *stack_a, t_stack *stack_b, char *op)
{
	if (ft_strncmp(op, "pa", ft_strlen(op) - 1) == 0)
		pa(stack_a, stack_b);
	else if (ft_strncmp(op, "pb", ft_strlen(op) - 1) == 0)
		pb(stack_a, stack_b);
	else if (ft_strncmp(op, "sa", ft_strlen(op) - 1) == 0)
		sa(stack_a);
	else if (ft_strncmp(op, "sb", ft_strlen(op) - 1) == 0)
		sb(stack_b);
	else if (ft_strncmp(op, "ra", ft_strlen(op) - 1) == 0)
		ra(stack_a);
	else if (ft_strncmp(op, "rb", ft_strlen(op) - 1) == 0)
		rb(stack_b);
	else if (ft_strncmp(op, "rra", ft_strlen(op) - 1) == 0)
		rra(stack_a);
	else if (ft_strncmp(op, "rrb", ft_strlen(op) - 1) == 0)
		rrb(stack_b);
	else if (ft_strncmp(op, "rr", ft_strlen(op) - 1) == 0)
		rr(stack_a, stack_b);
	else if (ft_strncmp(op, "rrr", ft_strlen(op) - 1) == 0)
		rrr(stack_a, stack_b);
	else if (ft_strncmp(op, "ss", ft_strlen(op) - 1) == 0)
		ss(stack_a, stack_b);
}

void	do_ps_ops(t_stack *stack_a, t_stack *stack_b)
{
	char	*op;

	op = get_next_line(STDIN_FILENO);
	while (op != NULL)
	{
		choose_op(stack_a, stack_b, op);
		free(op);
		op = get_next_line(STDIN_FILENO);
	}
}

void	check_result(t_stack *stack_a,
	t_stack *stack_b, int len, int *sorted_arr)
{
	int	i;
	int	ok;

	i = -1;
	ok = -1;
	(void)stack_b;
	if (stack_a->top + 1 != len)
		ok = 0;
	else
	{
		while (++i < len)
			if (stack_a->arr[i] != sorted_arr[len - i - 1])
				ok = 0;
	}
	if (ok != 0)
		ok = 1;
	if (ok == 1)
		ft_putstr_fd(GREEN "OK\n", 1);
	else
		ft_putstr_fd(RED "KO\n", 2);
}

int	main(int ac, char **av)
{
	int		len;
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
	do_ps_ops(stack_a, stack_b);
	check_result(stack_a, stack_b, len, sorted_arr);
	free(stack_a->arr);
	free(stack_b->arr);
	free(stack_a);
	free(stack_b);
	free(sorted_arr);
}
