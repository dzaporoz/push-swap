/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:09:52 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 17:22:22 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static int	get_pivot(int *stack, int count, int big_pivot, t_stacks *stacks)
{
	int counter;
	int	n;
	int avr;
	int delta;

	avr = 0;
	n = 0;
	counter = count;
	while (--counter >= 0 && stack[counter] <= big_pivot && !(A_LIMIT &&
				A_LIM_VAL == stack[counter]))
	{
		avr += stack[counter];
		n++;
	}
	avr /= n;
	if ((delta = -1) == -1 && n <= TO_ARRANGE_COUNT)
		return (2147483647);
	while (++delta >= 0)
	{
		n = count;
		while (--n > counter)
			if (avr + delta == stack[n] || avr - delta == stack[n])
				return (stack[n]);
	}
	return (2147483647);
}

static void	put_limit(t_stacks *stacks)
{
	A_LIMIT = 1;
	A_LIM_VAL = A_LAST;
	if (A_COUNT > 1)
		write_and_operate(stacks, OPP_RA);
}

static void	pick_from_a(t_stacks *stacks, int big_pivot, int pivot)
{
	int				counter;
	t_limits_data	lims;

	counter = (big_pivot == 2147483647) ? A_COUNT : 0;
	get_min_max(stacks->stack_a, A_COUNT, &lims);
	if (big_pivot != 2147483647)
		while (stacks->stack_a[A_COUNT - 1 - counter] <= big_pivot && !(A_LIMIT
					&& A_LIM_VAL == stacks->stack_a[A_COUNT - 1 - counter]))
			counter++;
	if (counter <= TO_ARRANGE_COUNT)
		while (--counter >= 0)
			(A_LAST == lims.min) ? put_limit(stacks) :
				write_and_operate(stacks, OPP_PB);
	else
	{
		counter = 0;
		while (counter != A_COUNT && A_LAST <= big_pivot && A_COUNT &&
				!(A_LIMIT && A_LAST == A_LIM_VAL))
		{
			counter += (A_LAST > pivot) ? 1 : 0;
			write_and_operate(stacks, (A_LAST <= pivot) ? OPP_PB : OPP_RA);
		}
		while (A_LIMIT && counter != A_COUNT && --counter >= 0)
			write_and_operate(stacks, OPP_RRA);
	}
}

void		quick_sort(t_stacks *stacks, int big_pivot, int same_pivot)
{
	int pivot;

	if (sort_check(stacks))
		return ;
	pivot = (same_pivot) ? big_pivot : get_pivot(stacks->stack_a, A_COUNT,
			big_pivot, stacks);
	pick_from_a(stacks, big_pivot, pivot);
	clear_b_stack(stacks, (B_COUNT <= TO_ARRANGE_COUNT) ? 0 :
			get_pivot(stacks->stack_b, B_COUNT, pivot, stacks));
	if (!(A_LIMIT && A_FIRST >= pivot))
		quick_sort(stacks, pivot, 1);
	if (!(sort_check(stacks) || (stacks->limit && A_FIRST >= big_pivot)))
		quick_sort(stacks, big_pivot, 0);
}
