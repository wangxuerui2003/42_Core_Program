/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 05:18:41 by wxuerui           #+#    #+#             */
/*   Updated: 2022/11/29 20:52:09 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_HEADER_H
# define CHECKER_HEADER_H

# include "libft.h"

# define NORMAL_EXIT 0
# define ERROR_EXIT 1

/*Colours*/
# define BOLD		"\x1b[1m"
# define RED		"\x1b[31m"
# define GREEN 		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

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
void	rr(t_stack *stack_a, t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);

#endif