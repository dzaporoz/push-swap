/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 17:21:42 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/01/12 15:56:21 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_PROJECT_H
# define PUSH_SWAP_PROJECT_H
# define OPP_SA 0
# define OPP_SB 1
# define OPP_SS 2
# define OPP_PA 3
# define OPP_PB 4
# define OPP_RA 5
# define OPP_RB 6
# define OPP_RR 7
# define OPP_RRA 8
# define OPP_RRB 9
# define OPP_RRR 10

# define TO_ARRANGE_COUNT 17

# define A_LAST (stacks->stack_a[stacks->counter_a - 1])
# define A_PENULT (stacks->stack_a[stacks->counter_a - 2])
# define A_FIRST (stacks->stack_a[0])
# define A_COUNT (stacks->counter_a)
# define A_LIMIT (stacks->limit)
# define A_LIM_VAL (stacks->limit_num)

# define B_LAST (stacks->stack_b[stacks->counter_b - 1])
# define B_PENULT (stacks->stack_b[stacks->counter_b - 2])
# define B_COUNT (stacks->counter_b)

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_limits_data
{
	int			min;
	int			pre_min;
	int			max;
	int			pre_max;
}				t_limits_data;

typedef struct	s_stacks
{
	int			*stack_a;
	int			*stack_b;
	int			counter_a;
	int			counter_b;
	int			operation;
	int			limit;
	int			limit_num;
	t_list		*op_list;
}				t_stacks;

void			arg_to_stack(t_stacks *stacks, char **argv);
void			check_dublicates(t_stacks *stacks);
void			error(t_stacks *stacks);
void			operations(t_stacks *stacks, int operation);
int				sort_check(t_stacks *stacks);
int				get_val_by_ind(t_stacks	*stacks, int index);
int				get_minval_pos(t_stacks *stacks);
void			write_and_operate(t_stacks *stacks, int op_num);
int				to_min_rotations(t_stacks *stacks);
void			regular_sort(t_stacks *stacks);
void			quick_sort(t_stacks *stacks, int big_pivot, int same_pivot);
void			clear_b_stack(t_stacks *stacks, int pivot);
void			get_min_max(int *stack, int count, t_limits_data *lims);

#endif
