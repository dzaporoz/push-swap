/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:19:06 by dzaporoz          #+#    #+#             */
/*   Updated: 2018/10/25 11:24:49 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			m;
	unsigned char	*p;

	m = 0;
	p = (unsigned char*)s;
	while (m < n)
	{
		if (*p == (unsigned char)c)
			return (p);
		m++;
		p++;
	}
	return (NULL);
}
