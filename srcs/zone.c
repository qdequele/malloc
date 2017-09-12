/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/12 17:30:29 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <malloc.h>


t_zone		*get_zones(void)
{
	static t_zone	zone;

	return (&t_zone);
}

t_zone_type	get_zone_type(size_t size)
{
	if (size <= TINY_SIZE)
		return TINY
	else if (size <= SMALL)
		return SMALL
	else
		return LARGE
}

size_t		get_zone_size(size_t size)
{
	t_zone_type type;

	type = get_zone_type(size)
	if (size <= TINY_SIZE)
		return TINY
	else if (size <= SMALL)
		return SMALL
	else
		return LARGE
}

t_block		*create_block(t_zone_type type)
{
	t_zone	*block;

	block = (t_block*)smmap(sizeof(t_block));
	block->ptr = NULL;
	block->size = 0;
	block->is_free = 0;
	block->next = NULL;
}

t_zone		*create_zone(t_zone_type type)
{
	t_zone	*zone;

	zone = (t_zone*)smmap(sizeof(t_zone));
	zone->size = 0;
	zone->nb_blocks = 0;
	zone->next = NULL;
	zone->blocks = NULL;
}

void		add_zone(t_zone_type type)
{
	t_zone	*init;

	init = get_zones();
	if (init != NULL)
		while (init->next)
			init = init->next;
	init = create_zone();
	init->type = type;
}