/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:36:09 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/11 17:32:39 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

int		sort_check(t_stacks *stacks)
{
	int min_pos;
	int counter;

	min_pos = get_minval_pos(stacks);
	counter = min_pos;
	while (++counter < stacks->counter_a)
		if (stacks->stack_a[counter] < get_val_by_ind(stacks, counter + 1))
			return (0);
	counter = 0;
	while (++counter <= min_pos)
		if (stacks->stack_a[counter - 1] < stacks->stack_a[counter])
			return (0);
	return (1);
}

int		get_val_by_ind(t_stacks *stacks, int index)
{
	while (index < 0)
		index += stacks->counter_a;
	while (index >= stacks->counter_a)
		index -= stacks->counter_a;
	return (stacks->stack_a[index]);
}

int		to_min_rotations(t_stacks *stacks)
{
	int min_pos;

	min_pos = get_minval_pos(stacks);
	stacks->operation = OPP_RA;
	if (stacks->counter_a - min_pos - 1 <= stacks->counter_a / 2)
		min_pos = stacks->counter_a - min_pos - 1;
	else if (stacks->counter_a != 1)
	{
		stacks->operation = OPP_RRA;
		min_pos++;
	}
	return (min_pos);
}

int		get_minval_pos(t_stacks *stacks)
{
	int n;
	int min;
	int min_pos;

	min = stacks->stack_a[0];
	min_pos = 0;
	n = -1;
	while (++n <= stacks->counter_a - 1)
		if (stacks->stack_a[n] < min)
		{
			min = stacks->stack_a[n];
			min_pos = n;
		}
	return (min_pos);
}
