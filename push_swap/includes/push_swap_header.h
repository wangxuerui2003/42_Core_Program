/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_header.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:08:12 by wxuerui           #+#    #+#             */
/*   Updated: 2022/11/29 20:50:39 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_HEADER_H
# define PUSH_SWAP_HEADER_H

# include "libft.h"

# define NORMAL_EXIT 0
# define ERROR_EXIT 1

/*Structure for stack*/
typedef struct s_stack {
	int	*arr;
	int	top;
}	t_stack;

/*Utils prototypes*/
void	ft_swap(int *a, int *b);
int		check_input(int ac, char **av);
void	get_stack_b(int top, t_stack **stack_b);
void	get_stack_a(int ac, char **av, t_stack **stack_a);
void	print_stacks(t_stack *stack_a, t_stack *stack_b, int len);

/*Sorting prototypes*/
void	sort_three(t_stack *stack_a);
void	sort_small(t_stack *stack_a,
			t_stack *stack_b, int len, int *sorted_arr);
void	sort_big(t_stack *stack_a, t_stack *stack_b, int len, int *sorted_arr);
int		fully_sorted(t_stack *stack_a, int *sorted_arr, int len);

/*Operations prototypes*/
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);
void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);
void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);

#endif