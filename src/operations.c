/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:52:29 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/10 17:53:21 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static void	ft_swap(t_stacks *stacks, int operation)
{
	int	buf;
	int stacksize;
	int *stack;
	int both_flag;

	both_flag = (operation == OPP_SS) ? 1 : 0;
	if (operation == OPP_SS)
		operation = OPP_SA;
	stacksize = (operation == OPP_SA) ? stacks->counter_a : stacks->counter_b;
	stack = (operation == OPP_SA) ? stacks->stack_a : stacks->stack_b;
	if (!stacksize)
		return ;
	buf = stack[stacksize - 1];
	stack[stacksize - 1] = stack[stacksize - 2];
	stack[stacksize - 2] = buf;
	if (both_flag)
		ft_swap(stacks, OPP_SB);
}

static void	ft_reverse_rotate(t_stacks *stacks, int operation)
{
	int n;
	int buf;
	int *stack;
	int stacksize;
	int both_flag;

	both_flag = (operation == OPP_RRR) ? 1 : 0;
	if (operation == OPP_RRR)
		operation = OPP_RRA;
	stack = (operation == OPP_RRA) ? stacks->stack_a : stacks->stack_b;
	stacksize = (operation == OPP_RRA) ? stacks->counter_a : stacks->counter_b;
	stacksize--;
	if (stacksize <= 0)
		return ;
	n = 0;
	buf = stack[0];
	while (n < stacksize)
	{
		stack[n] = stack[n + 1];
		n++;
	}
	stack[n] = buf;
	if (both_flag)
		ft_reverse_rotate(stacks, OPP_RRB);
}

static void	ft_rotate(t_stacks *stacks, int operation)
{
	int n;
	int buf;
	int *stack;
	int stacksize;
	int both_flag;

	both_flag = (operation == OPP_RR) ? 1 : 0;
	if (operation == OPP_RR)
		operation = OPP_RA;
	stack = (operation == OPP_RA) ? stacks->stack_a : stacks->stack_b;
	stacksize = (operation == OPP_RA) ? stacks->counter_a : stacks->counter_b;
	stacksize--;
	if (stacksize <= 0)
		return ;
	n = stacksize;
	buf = stack[n];
	while (n > 0)
	{
		stack[n] = stack[n - 1];
		n--;
	}
	stack[0] = buf;
	if (both_flag)
		ft_rotate(stacks, OPP_RB);
}

static void	ft_push(t_stacks *stacks, int operation)
{
	int *s_a;
	int *s_b;
	int *c_a;
	int *c_b;

	s_a = (operation == OPP_PA) ? stacks->stack_b : stacks->stack_a;
	s_b = (operation == OPP_PA) ? stacks->stack_a : stacks->stack_b;
	c_a = (operation == OPP_PA) ? &(stacks->counter_b) : &(stacks->counter_a);
	c_b = (operation == OPP_PA) ? &(stacks->counter_a) : &(stacks->counter_b);
	if (!(*c_a))
		return ;
	s_b[*c_b] = s_a[*c_a - 1];
	(*c_b)++;
	(*c_a)--;
}

void		operations(t_stacks *stacks, int operation)
{
	if (operation < 3)
		ft_swap(stacks, operation);
	else if (operation < 5)
		ft_push(stacks, operation);
	else if (operation < 8)
		ft_rotate(stacks, operation);
	else if (operation < 11)
		ft_reverse_rotate(stacks, operation);
}
