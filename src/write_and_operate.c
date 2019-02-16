/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_and_operate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:35:51 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/11 17:37:00 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "project.h"

static void	initialize_op(char *op[11])
{
	if (op[0])
		return ;
	op[0] = "sa\n";
	op[1] = "sb\n";
	op[2] = "ss\n";
	op[3] = "pa\n";
	op[4] = "pb\n";
	op[5] = "ra\n";
	op[6] = "rb\n";
	op[7] = "rr\n";
	op[8] = "rra\n";
	op[9] = "rrb\n";
	op[10] = "rrr\n";
}

static int	unite_opp(int op_num, t_list *last)
{
	if ((!ft_strcmp(last->content, "ra\n") && op_num == OPP_RB) ||
		(!ft_strcmp(last->content, "rb\n") && op_num == OPP_RA))
	{
		((char*)last->content)[1] = 'r';
		return (1);
	}
	else if ((!ft_strcmp(last->content, "rra\n") && op_num == OPP_RRB) ||
			(!ft_strcmp(last->content, "rrb\n") && op_num == OPP_RRA))
	{
		((char*)last->content)[2] = 'r';
		return (1);
	}
	else if ((!ft_strcmp(last->content, "sa\n") && op_num == OPP_SB) ||
			(!ft_strcmp(last->content, "sb\n") && op_num == OPP_SA))
	{
		((char*)last->content)[1] = 's';
		return (1);
	}
	return (0);
}

static int	remove_opp(int op_num, t_list *temp)
{
	t_list *last;

	if (!temp->next)
		return (0);
	while (temp->next->next)
		temp = temp->next;
	last = temp->next;
	if ((!ft_strcmp(last->content, "ra\n") && op_num == OPP_RRA) ||
		(!ft_strcmp(last->content, "rb\n") && op_num == OPP_RRB) ||
		(!ft_strcmp(last->content, "rra\n") && op_num == OPP_RA) ||
		(!ft_strcmp(last->content, "rrb\n") && op_num == OPP_RB) ||
		(!ft_strcmp(last->content, "pa\n") && op_num == OPP_PB) ||
		(!ft_strcmp(last->content, "pb\n") && op_num == OPP_PA))
	{
		ft_lstdelone(&last, ft_lstcontdel);
		temp->next = NULL;
		return (1);
	}
	return (0);
}

void		write_and_operate(t_stacks *stacks, int op_num)
{
	t_list		*temp;
	static char	*op[11];

	if (op_num < 0 || op_num > 10)
		return ;
	initialize_op(op);
	operations(stacks, op_num);
	if (!((temp = stacks->op_list) && stacks->op_list))
		stacks->op_list = ft_lstnew(&op[op_num][0], ft_strlen(op[op_num]));
	else
	{
		while (temp->next)
			temp = temp->next;
		if (!unite_opp(op_num, temp) && !remove_opp(op_num, stacks->op_list))
			temp->next = ft_lstnew(&op[op_num][0], ft_strlen(op[op_num]));
	}
}
