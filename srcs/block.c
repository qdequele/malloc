/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/19 17:24:30 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	init_all_blocks(void *ptr)
{
	VAL(ptr) = 0;
}

void	foreach_blocks(t_zone **zone, void (*f)(void *ptr))
{
	t_zone	*begin;
	void	*ptr;
	size_t	i;

	begin = *zone;
	ptr = (void *)begin + T_ZONE_SIZE;
	i = 0;
	while (i < begin->nb_max_blocks)
	{
		f(ptr);
		ptr += T_BLOCK_SIZE + ZONE_SIZE((*zone)->type);
		i++;
	}
}

void	*register_free_block(size_t size)
{
	t_zone	*zone;
	void	*ptr;
	size_t	i;

	zone = *get_zones(size);
	while (zone && zone->next && zone->nb_blocks == zone->nb_max_blocks)
		zone = zone->next;
	if (!zone || zone->nb_blocks == zone->nb_max_blocks)
		zone = add_zone(size);
	ptr = (void *)zone + T_ZONE_SIZE;
	i = 0;
	while (VAL(ptr) != 0 && i < zone->nb_max_blocks)
	{
		ptr += T_BLOCK_SIZE + ZONE_SIZE(zone->type);
		i++;
	}
	VAL(ptr) = size;
	// printf("val ptr : %zu - block : %zu/%zu\n", VAL(ptr), zone->nb_blocks, zone->nb_max_blocks);
	zone->nb_blocks++;
	return ptr + T_BLOCK_SIZE;
}
