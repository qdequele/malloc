/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/20 15:46:05 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	init_all_blocks(t_zone **zone)
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
		ptr += T_BLOCK_SIZE + zone_size_by_type((*zone)->type);
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
	return zone;
}

void	zone_addend(t_zone **alst, t_zone *new)
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
	zone_addend(get_zones(size), new);
	return new;
}

void	*malloc(size_t size)
{
	t_zone	*zone;
	void	*ptr;
	size_t	i;

	if (size == 0)
		return (NULL);
	zone = *get_zones(size);
	while (zone && zone->next && zone->nb_blocks == zone->nb_max_blocks)
		zone = zone->next;
	if (!zone || zone->nb_blocks == zone->nb_max_blocks)
		zone = add_zone(size);
	ptr = (void *)zone + T_ZONE_SIZE;
	i = 0;
	while (VAL(ptr) != 0 && i < zone->nb_max_blocks)
	{
		ptr += T_BLOCK_SIZE + zone_size_by_type(zone->type);
		i++;
	}
	VAL(ptr) = size;
	zone->nb_blocks++;
	return ptr + T_BLOCK_SIZE;
}
