/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/26 10:13:54 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*check_realloc_zone(t_zone **zone, void *ptr, size_t size)
{
	t_zone	*z;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			ptr -= T_BLOCK_SIZE;
			if (zone_type(VAL(ptr)) - zone_type(size) != 0)
			{
				VAL(ptr) = 0;
				return (NULL);
			}
			VAL(ptr) = size;
			return (ptr += T_BLOCK_SIZE);
		}
		z = z->next;
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if ((new_ptr = check_realloc_zone(get_zones(TINY), ptr, size))
		== NULL)
		if ((new_ptr = check_realloc_zone(get_zones(SMALL), ptr, size))
			== NULL)
			if ((new_ptr = check_realloc_zone(get_zones(SMALL + 10), ptr, size))
				== NULL)
				return (malloc(size));
	return (new_ptr);
}
