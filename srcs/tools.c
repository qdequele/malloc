/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/26 10:20:17 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*smmap(size_t len)
{
	size_t	mult;
	size_t	f_len;

	mult = (len / PAGE_SIZE) + 1;
	f_len = mult * PAGE_SIZE;
	return (mmap(NULL, f_len, PROT, MAP, -1, 0));
}

t_mem		*get_mem(void)
{
	static t_mem	mem;

	return (&mem);
}

t_zone		**get_zones(t_zone_type type)
{
	t_mem	*mem;

	mem = get_mem();
	if (type == TINY)
		return (&mem->tiny);
	else if (type == SMALL)
		return (&mem->small);
	else
		return (&mem->large);
}
