/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 19:14:41 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/11 17:35:39 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static void	check_and_push(t_stacks *stacks)
{
	int counter;

	counter = -1;
	while (++counter < stacks->counter_b)
	{
		if ((stacks->stack_b[counter] > stacks->stack_a[0] ||
			get_minval_pos(stacks) == stacks->counter_a - 1) &&
			(stacks->stack_b[counter] < stacks->stack_a[stacks->counter_a - 1]
			|| get_minval_pos(stacks) == stacks->counter_a - 2))
		{
			stacks->operation = OPP_RB;
			if (stacks->counter_b - counter <= stacks->counter_b / 2)
				counter = stacks->counter_b - counter - 1;
			else if (stacks->counter_b != 1)
			{
				stacks->operation = OPP_RRB;
				counter++;
			}
			while (counter--)
				write_and_operate(stacks, stacks->operation);
			write_and_operate(stacks, OPP_PA);
		}
	}
}

static int	go_to_right(t_stacks *stacks)
{
	int counter_a;
	int counter_b;
	int n;
	int c_a;
	int c_b;

	counter_a = stacks->counter_a;
	while (--counter_a && (n = -1) == -1)
		while (++n < stacks->counter_b)
			if (stacks->stack_b[n] > stacks->stack_a[counter_a] &&
				(stacks->stack_b[n] < stacks->stack_a[counter_a - 1]
				|| counter_a - 1 == get_minval_pos(stacks)))
				c_a = counter_a - 1;
	counter_b = 0;
	while (++counter_b < stacks->counter_a && (n = -1) == -1)
		while (++n < stacks->counter_b)
			if ((stacks->stack_a[counter_b - 1] > stacks->stack_b[n] ||
				counter_b - 1 == get_minval_pos(stacks)) &&
				stacks->stack_a[counter_b] < stacks->stack_b[n])
				c_b = counter_b - 1;
	if (c_b < c_a)
		stacks->operation = OPP_RA;
	else
		stacks->operation = OPP_RRA;
	return (1);
}

static int	check_swap(t_stacks *stacks)
{
	int buf;
	int last;
	int ret;

	last = stacks->counter_a - 1;
	buf = stacks->stack_a[last];
	stacks->stack_a[last] = stacks->stack_a[last - 1];
	stacks->stack_a[last - 1] = buf;
	if (sort_check(stacks))
		ret = 1;
	else
		ret = 0;
	buf = stacks->stack_a[last];
	stacks->stack_a[last] = stacks->stack_a[last - 1];
	stacks->stack_a[last - 1] = buf;
	return (ret);
}

static void	clear_bstack(t_stacks *stacks)
{
	while (stacks->counter_b)
	{
		check_and_push(stacks);
		go_to_right(stacks);
		if (stacks->counter_b)
			write_and_operate(stacks, stacks->operation);
	}
}

void		regular_sort(t_stacks *stacks)
{
	while (!sort_check(stacks))
	{
		while (!sort_check(stacks) && ((stacks->stack_a[stacks->counter_a - 1]
			> stacks->stack_a[stacks->counter_a - 2] &&
			stacks->stack_a[stacks->counter_a - 2] > stacks->stack_a[0])
			|| check_swap(stacks)))
		{
			write_and_operate(stacks, OPP_SA);
			if (!sort_check(stacks))
				write_and_operate(stacks, OPP_RA);
		}
		if (((stacks->stack_a[stacks->counter_a - 1] >
			stacks->stack_a[stacks->counter_a - 2] &&
			stacks->stack_a[stacks->counter_a - 1] < stacks->stack_a[0]) ||
			(stacks->stack_a[stacks->counter_a - 1] < stacks->stack_a[0]) ||
			get_minval_pos(stacks) == stacks->counter_a - 1) &&
			!sort_check(stacks))
			write_and_operate(stacks, OPP_PB);
		else if (!sort_check(stacks))
			write_and_operate(stacks, OPP_RA);
		if (sort_check(stacks))
			break ;
	}
	clear_bstack(stacks);
}
