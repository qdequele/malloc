/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 17:15:42 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		copy_blocks(void *old, size_t old_size, void *new, size_t new_size)
{
	size_t	count;
	size_t	i;

	count = (old_size <= new_size) ? old_size : new_size;
	i = 0;
	while (++i <= count)
	{
		new++;
		old++;
		VAL(new) = VAL(old);
	}
}

void	*check_realloc_zone(t_zone **zone, void *ptr, size_t size)
{
	t_zone	*z;
	void	*new_ptr;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			if (((void *)z - ptr - T_ZONE_SIZE) % (T_BLOCK_SIZE + z->type) != 0)
			{
				ft_putstr("MODULO !!!\n");
				return (NULL);
			}
				
			ptr -= T_BLOCK_SIZE;
			if (zone_type(VAL(ptr)) - zone_type(size) != 0)
			{
				new_ptr = malloc(size);
				copy_blocks(new_ptr, size, ptr, VAL(ptr));
				free_block(zone, ptr);
				return (new_ptr);
			}
			VAL(ptr) = size;
			return (ptr += T_BLOCK_SIZE);
		}
		z = z->next;
	}
	return (malloc(size));
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL && size != 0)
		return (malloc(size));
	if (ptr == NULL && size == 0)
		return (NULL);
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	return (check_realloc_zone(get_zones(), ptr, size));
}
