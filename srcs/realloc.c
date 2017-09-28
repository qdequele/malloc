/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/28 14:29:08 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*check_realloc_zone(t_zone **zone, void *ptr, size_t size)
{
	t_zone	*z;
	void	*new_ptr;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			ptr -= T_BLOCK_SIZE;
			if (zone_type(VAL(ptr)) - zone_type(size) != 0)
			{
				new_ptr = malloc(size);
				copy_blocks(new_ptr, size, ptr, VAL(ptr));
				free_block(zone, ptr);
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
	if ((new_ptr = check_realloc_zone(get_zones(), ptr, size)) == NULL)
		return (malloc(size));
	return (new_ptr);
}
