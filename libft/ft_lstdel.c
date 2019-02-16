/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:38:32 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/26 13:24:37 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;

	if (alst && del)
		while (*alst)
		{
			del((*alst)->content, (*alst)->content_size);
			temp = (*alst)->next;
			free(*alst);
			*alst = temp;
		}
	*alst = NULL;
}
