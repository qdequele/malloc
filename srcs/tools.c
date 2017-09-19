/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/19 19:02:10 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*smmap(size_t len)
{
	size_t	mult;
	size_t	f_len;

	mult = (len / PAGE_SIZE) + 1;
	f_len = mult * PAGE_SIZE;
	return (mmap(NULL, f_len, PROT , MAP, -1, 0));
}

int		optim_nb_block(size_t len)
{
	size_t		c_len;
	size_t		f_len;
	t_zone_type	type;

	c_len = 100 * (len + T_BLOCK_SIZE) + T_ZONE_SIZE;
	f_len = ((c_len / PAGE_SIZE) + 1) * PAGE_SIZE;
	type = ZONE_TYPE(len);
	if (type == TINY)
		return ((f_len - T_ZONE_SIZE) / (T_BLOCK_SIZE + TINY_SIZE));
	else if (type == SMALL)
		return ((f_len - T_ZONE_SIZE) / (T_BLOCK_SIZE + SMALL_SIZE));
	else
		return (1);
}

t_mem		*get_mem(void)
{
	static t_mem	mem;

	return (&mem);
}

t_zone		**get_zones(size_t size)
{
	t_mem	*mem;

	mem = get_mem();
	if (ZONE_TYPE(size) == TINY)
		return (&mem->tiny);
	else if (ZONE_TYPE(size) == SMALL)
		return (&mem->small);
	else
		return (&mem->large);
}