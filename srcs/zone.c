/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/19 17:39:50 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_zone		*create_zone(size_t size)
{
	t_zone	*zone;
	size_t	nb_blocks;

	if (ZONE_TYPE(size) == TINY)
	{
		nb_blocks = optim_nb_block(TINY_SIZE);
		printf("create_zone - TINY | nb_blocks = %zu total size : %zu = %zu + %zu * (%zu + %d)\n", nb_blocks, TINY_ZONE_SIZE(nb_blocks), T_ZONE_SIZE, nb_blocks, T_BLOCK_SIZE, TINY_SIZE);
		zone = (t_zone*)smmap(TINY_ZONE_SIZE(nb_blocks));
	}
	else if (ZONE_TYPE(size) == SMALL)
	{
		nb_blocks = optim_nb_block(SMALL_SIZE);
		printf("create_zone - SMALL | nb_blocks = %zu total size : %zu = %zu + %zu * (%zu + %d)\n", nb_blocks, SMALL_ZONE_SIZE(nb_blocks), T_ZONE_SIZE, nb_blocks, T_BLOCK_SIZE, SMALL_SIZE);
		zone = (t_zone*)smmap(SMALL_ZONE_SIZE(nb_blocks));
	}
	else
	{
		nb_blocks = 1;
		zone = (t_zone*)smmap(sizeof(t_zone) + sizeof(int) + size);
	}
	zone->type = ZONE_TYPE(size);
	zone->nb_blocks = 0;
	zone->nb_max_blocks = nb_blocks;
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
	foreach_blocks(&new, init_all_blocks);
	zone_addend(get_zones(size), new);
	return new;
}

t_zone		**get_zones(size_t size)
{
	t_mem	*mem;

	mem = get_mem();
	if (ZONE_TYPE(size) == TINY)
	{
		// printf("return TINY zone at %p\n", &mem->tiny);
		return (&mem->tiny);
	}
	else if (ZONE_TYPE(size) == SMALL)
	{
		// printf("return SMALL zone at %p\n", &mem->tiny);
		return (&mem->small);
	}
	else
	{
		// printf("return LARGE zone at %p\n", &mem->tiny);
		return (&mem->large);
	}
}