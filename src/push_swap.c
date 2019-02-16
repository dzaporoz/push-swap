/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:53:42 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/11 17:33:31 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static void	put_opp_list(t_list *list)
{
	if (list)
		write(1, (char*)list->content, list->content_size);
}

int			main(int argc, char **argv)
{
	t_stacks	stacks;

	if (argc == 1)
		error(&stacks);
	ft_bzero(&stacks, sizeof(t_stacks));
	arg_to_stack(&stacks, &argv[1]);
	check_dublicates(&stacks);
	if (stacks.counter_a > 1 && !sort_check(&stacks))
	{
		if (stacks.counter_a <= 5)
			regular_sort(&stacks);
		else
			quick_sort(&stacks, 2147483647, 0);
	}
	if (sort_check(&stacks))
		while (to_min_rotations(&stacks))
			write_and_operate(&stacks, stacks.operation);
	ft_lstiter(stacks.op_list, put_opp_list);
	if (stacks.stack_a)
		free(stacks.stack_a);
	if (stacks.stack_b)
		free(stacks.stack_b);
	if (stacks.op_list)
		ft_lstdel(&stacks.op_list, ft_lstcontdel);
	return (EXIT_SUCCESS);
}
