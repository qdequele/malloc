/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/26 10:20:22 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int			optim_nb_block(size_t len)
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

int			zone_size_by_size(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	else
		return (size);
}

t_zone_type	zone_type(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	else
		return (LARGE);
}

size_t		calculate(size_t nb, size_t size)
{
	t_zone_type	type;

	type = zone_type(size);
	if (type > 0)
		return (T_ZONE_SIZE + (nb * T_BLOCK_SIZE) + (nb * type));
	else
		return (sizeof(t_zone) + sizeof(int) + size);
}
