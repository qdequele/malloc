/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/29 11:22:19 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		init_all_blocks(t_zone **zone)
{
	t_zone	*begin;
	void	*ptr;
	size_t	i;

	begin = *zone;
	ptr = (void *)begin + T_ZONE_SIZE;
	i = 0;
	while (i < begin->nb_max_blocks)
	{
		VAL(ptr) = 0;
		ptr += T_BLOCK_SIZE + (*zone)->type;
		i++;
	}
}

t_zone		*create_zone(size_t size)
{
	t_zone	*zone;
	size_t	nb_blocks;
	size_t	zone_length;

	nb_blocks = optim_nb_block(zone_size_by_size(size));
	zone_length = calculate(nb_blocks, size);
	zone = (t_zone*)smmap(zone_length);
	zone->type = zone_type(size);
	zone->nb_blocks = 0;
	zone->nb_max_blocks = nb_blocks;
	zone->zone_length = zone_length;
	zone->next = NULL;
	return (zone);
}

void		zone_insert(t_zone **alst, t_zone *new)
{
	t_zone	*list;

	list = *alst;
	if (*alst == NULL && new)
		*alst = new;
	else
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

t_zone		*add_zone(size_t size)
{
	t_zone		*new;

	new = create_zone(size);
	init_all_blocks(&new);
	zone_insert(get_zones(), new);
	return (new);
}

void		*malloc(size_t size)
{
	t_zone	*z;
	void	*ptr;
	size_t	i;

	if (size == 0)
		return (NULL);
	z = *get_zones();
	while (z && z->next && (z->nb_blocks == z->nb_max_blocks 
	|| z->type != zone_type(size)))
		z = z->next;
	if (!z || z->nb_blocks == z->nb_max_blocks || z->type != zone_type(size))
		z = add_zone(size);
	ptr = (void *)z + T_ZONE_SIZE;
	i = 0;
	while (VAL(ptr) != 0 && i < z->nb_max_blocks && z->type != LARGE)
	{
		ptr += T_BLOCK_SIZE + z->type;
		i++;
	}
	VAL(ptr) = size;
	// printf("1 - %zu | placed in block %p complete at %zu/%zu\n", size, z, z->nb_blocks, z->nb_max_blocks);
	z->nb_blocks++;
	// printf("2 - %zu | placed in block %p complete at %zu/%zu\n", size, z, z->nb_blocks, z->nb_max_blocks);
	return (ptr + T_BLOCK_SIZE);
}
