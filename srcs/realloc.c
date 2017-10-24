/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/24 15:09:28 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		copy_blocks(void *old, size_t old_size, void *new, size_t new_size)
{
	size_t	count;
	size_t	i;

	count = (old_size <= new_size) ? old_size : new_size;
	i = 0;
	while (i < count)
	{
		*(char *)new = *(char *)old;
		new++;
		old++;
		i++;
	}
}

void		*do_reallocation(t_zone **zone, void *ptr, size_t size)
{
	void	*new_ptr;
	t_zone	*z;

	z = *zone;
	new_ptr = do_malloc(size);
	copy_blocks(ptr + T_BLOCK_SIZE, VAL(ptr), new_ptr, size);
	free_block(&z, ptr);
	return (new_ptr);
}

void		*check_realloc_zone(t_zone **zone, void *ptr, size_t size)
{
	t_zone	*z;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			if (((ptr - (void *)z - T_ZONE_SIZE - T_BLOCK_SIZE) %
				(T_BLOCK_SIZE + z->type)) != 0)
				return (NULL);
			ptr -= T_BLOCK_SIZE;
			if (zone_type(VAL(ptr)) - zone_type(size) != 0
				|| zone_type(size) == LARGE)
				return (do_reallocation(&z, ptr, size));
			VAL(ptr) = size;
			return (ptr += T_BLOCK_SIZE);
		}
		z = z->next;
	}
	return (do_malloc(size));
}

void		*do_realloc(void *ptr, size_t size)
{
	if (ptr == NULL && size != 0)
		return (do_malloc(size));
	if (ptr == NULL && size == 0)
		return (NULL);
	if (size == 0)
	{
		do_free(ptr);
		return (NULL);
	}
	return (check_realloc_zone(get_zones(), ptr, size));
}
