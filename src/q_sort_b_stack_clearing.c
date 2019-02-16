/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_sort_b_stack_clearing.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 18:27:29 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 13:21:11 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

void		get_min_max(int *stack, int count, t_limits_data *lims)
{
	t_limits_data pos;

	lims->min = stack[0];
	lims->max = stack[0];
	pos.min = count;
	pos.max = count;
	while (--count >= 0)
	{
		if (stack[count] >= lims->max && (pos.max = count) == count)
		{
			lims->pre_max = lims->max;
			lims->max = stack[count];
		}
		if (stack[count] <= lims->min && (pos.min = count) == count)
		{
			lims->pre_min = lims->min;
			lims->min = stack[count];
		}
		if (stack[count] > lims->pre_max && stack[count] < lims->max)
			lims->pre_max = stack[count];
		if (stack[count] < lims->pre_min && stack[count] > lims->min)
			lims->pre_min = stack[count];
	}
}

static int	get_direction(t_stacks *stacks)
{
	int				steps;
	t_limits_data	limits;
	int				forward;
	int				backward;

	get_min_max(stacks->stack_b, B_COUNT, &limits);
	forward = B_COUNT - 1;
	steps = 0;
	while (stacks->stack_b[forward] != limits.min &&
			stacks->stack_b[forward] != limits.max)
	{
		forward--;
		steps++;
	}
	forward = steps;
	steps = 0;
	while (stacks->stack_b[steps] != limits.min &&
			stacks->stack_b[steps] != limits.max)
		steps++;
	backward = steps + 1;
	steps = (forward < backward) ? forward : backward;
	stacks->operation = (forward < backward) ? OPP_RB : OPP_RRB;
	return (steps);
}

static void	put_to_right(t_stacks *stacks, int operation, int data, int flag)
{
	if (operation == 1)
	{
		A_LIM_VAL = (A_LIMIT) ? A_LIM_VAL : data;
		A_LIMIT = 1;
		write_and_operate(stacks, OPP_PA);
		write_and_operate(stacks, OPP_RA);
	}
	else if (operation == 0)
	{
		A_LIM_VAL = (A_LIMIT) ? A_LIM_VAL : data;
		A_LIMIT = 1;
	}
	else
	{
		if (flag && B_LAST == data && stacks->operation == OPP_RRB)
			write_and_operate(stacks, OPP_PA);
		if (flag && B_LAST == data && stacks->operation == OPP_RB)
			write_and_operate(stacks, OPP_PA);
		else
			write_and_operate(stacks, stacks->operation);
	}
}

static void	push_from_max(t_stacks *stacks)
{
	int				steps;
	t_limits_data	lims;
	int				m;

	get_min_max(stacks->stack_b, B_COUNT, &lims);
	m = lims.max;
	put_to_right(stacks, 0, lims.min, 0);
	while (stacks->counter_b)
	{
		get_min_max(stacks->stack_b, B_COUNT, &lims);
		steps = get_direction(stacks);
		while (--steps >= 0)
			put_to_right(stacks, -1, lims.pre_max, A_LAST > lims.max);
		write_and_operate(stacks, OPP_PA);
		if (A_LAST == lims.min && (A_LAST < A_PENULT || A_PENULT == A_LIM_VAL))
			write_and_operate(stacks, OPP_RA);
		get_min_max(stacks->stack_b, B_COUNT, &lims);
		if (A_LAST > A_PENULT && A_PENULT != A_LIM_VAL)
			write_and_operate(stacks, (B_COUNT > 1 && (B_PENULT == lims.min ||
			B_PENULT == lims.max || (B_COUNT > 2 && B_PENULT == lims.pre_max)))
			? OPP_SS : OPP_SA);
	}
	while (A_FIRST != m)
		write_and_operate(stacks, OPP_RA);
}

void		clear_b_stack(t_stacks *stacks, int pivot)
{
	int				counter;
	t_limits_data	lims;
	int				n;

	if ((counter = 0) == 0 && B_COUNT <= TO_ARRANGE_COUNT && B_COUNT != 0)
		push_from_max(stacks);
	if ((n = B_COUNT) == 0)
		return ;
	while (--n >= 0)
		counter += (stacks->stack_b[n] > pivot) ? 1 : 0;
	get_min_max(stacks->stack_b, B_COUNT, &lims);
	while (counter > 0 || (lims.max <= pivot && B_COUNT))
	{
		if ((A_LIMIT && B_LAST == lims.min && B_LAST > A_FIRST) || (!A_LIMIT &&
		B_LAST == lims.min))
			put_to_right(stacks, 1, lims.min, 0);
		else if ((lims.max <= pivot || B_LAST > pivot) &&
				--counter < 2147483647)
			write_and_operate(stacks, OPP_PA);
		else
			write_and_operate(stacks, OPP_RB);
	}
	clear_b_stack(stacks, pivot);
	if (!(stacks->limit && A_FIRST >= pivot))
		quick_sort(stacks, pivot, 1);
}
