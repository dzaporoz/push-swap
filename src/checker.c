/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 19:13:27 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 16:38:22 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static void	check_sort(t_stacks stacks)
{
	int n;

	if (stacks.counter_b != 0 || stacks.counter_a == 0)
	{
		write(1, "KO\n", 3);
		return ;
	}
	n = stacks.counter_a;
	while (--n > 0)
		if (stacks.stack_a[n] > stacks.stack_a[n - 1])
		{
			write(1, "KO\n", 3);
			return ;
		}
	write(1, "OK\n", 3);
}

static int	get_operation(char *str, t_stacks *stacks)
{
	int			n;
	static char	*operations[11];

	if (!operations[0])
	{
		operations[0] = "sa";
		operations[1] = "sb";
		operations[2] = "ss";
		operations[3] = "pa";
		operations[4] = "pb";
		operations[5] = "ra";
		operations[6] = "rb";
		operations[7] = "rr";
		operations[8] = "rra";
		operations[9] = "rrb";
		operations[10] = "rrr";
	}
	n = -1;
	while (++n < 11)
		if (!(ft_strcmp(str, operations[n])))
			return (n);
	error(stacks);
	return (0);
}

int			main(int argc, char **argv)
{
	t_stacks	stacks;
	char		*operation;
	int			ret;

	if (argc == 1)
		return (EXIT_SUCCESS);
	ft_bzero(&stacks, sizeof(t_stacks));
	arg_to_stack(&stacks, &argv[1]);
	check_dublicates(&stacks);
	while ((ret = get_next_line(0, &operation)) > 0 && ft_strcmp(operation, ""))
	{
		if (ret < 0)
			error(&stacks);
		operations(&stacks, get_operation(operation, &stacks));
		free(operation);
	}
	check_sort(stacks);
	free(stacks.stack_a);
	free(stacks.stack_b);
	return (EXIT_SUCCESS);
}
