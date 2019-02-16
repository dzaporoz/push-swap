/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxilliary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:23:59 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 16:36:38 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

void		error(t_stacks *stacks)
{
	if (A_COUNT)
	{
		free(stacks->stack_a);
		free(stacks->stack_b);
	}
	if (stacks->op_list)
		ft_lstdel(&stacks->op_list, ft_lstcontdel);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int			ft_is_number(char c)
{
	if (c == '-' || c == '+' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static int	ps_atoi(const char *str, t_stacks *stacks)
{
	unsigned long int	nb;
	int					digit;
	int					n;

	n = 0;
	nb = 0;
	digit = 1;
	while (ft_isspace(str[n]))
		n++;
	if (str[n] == '-')
		digit = -1;
	if (str[n] == '-' || str[n] == '+')
		n++;
	while (ft_isdigit(str[n]))
	{
		if (nb > 2147483648 || (nb > 2147483647 && digit == 1))
			error(stacks);
		nb = nb * 10 + (str[n] - '0');
		n++;
	}
	if (nb > 2147483648 || (nb > 2147483647 && digit == 1))
		error(stacks);
	if (!ft_is_number(str[n]) && !ft_isspace(str[n]) && str[n] != '\0')
		error(stacks);
	return ((int)nb * digit);
}

void		arg_to_stack(t_stacks *stacks, char **argv)
{
	int	n;
	int	numbers;

	numbers = 0;
	n = -1;
	while (argv[++n])
		if (!(argv[n][0] == '-' && !ft_isdigit(argv[n][1])))
			numbers += ft_count_words(argv[n], ' ');
	if (!(stacks->stack_a = (int*)malloc(sizeof(int) * numbers)) ||
			!(stacks->stack_b = (int*)malloc(sizeof(int) * numbers)))
		error(stacks);
	stacks->counter_a = numbers--;
	while (argv[0] && ((n = -1) == -1))
	{
		while (argv[0][++n])
		{
			stacks->stack_a[numbers] = ps_atoi(&argv[0][n], stacks);
			while (ft_is_number(argv[0][n + 1]))
				n++;
			numbers--;
		}
		argv++;
	}
}

void		check_dublicates(t_stacks *stacks)
{
	int a;
	int b;

	a = 0;
	while (++a <= stacks->counter_a - 1)
	{
		b = -1;
		while (++b < a)
			if (stacks->stack_a[a] == stacks->stack_a[b])
				error(stacks);
	}
}
