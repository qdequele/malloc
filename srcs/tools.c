/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/21 13:46:31 by qdequele         ###   ########.fr       */
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
	type = zone_type(len);
	if (type > 0)
		return ((f_len - T_ZONE_SIZE) / (T_BLOCK_SIZE + type));
	else
		return (1);
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

int			zone_size_by_size(size_t size)
{
	return ((size <= TINY) ? TINY : (size <= SMALL) ? SMALL : size);
}

t_zone_type	zone_type(size_t size)
{
	return ((size <= TINY) ? TINY : (size <= SMALL) ? SMALL : LARGE);
}

size_t	calculate(size_t nb, size_t size)
{
	t_zone_type	type;

	type = zone_type(size);
	if (type > 0)
		return (T_ZONE_SIZE + (nb * T_BLOCK_SIZE) + (nb * type));
	else
		return (sizeof(t_zone) + sizeof(int) + size);
}