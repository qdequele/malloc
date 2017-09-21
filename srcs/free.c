/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/21 10:07:32 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		check_zone(t_zone **zone, void *ptr)
{
	t_zone	*z;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			ptr -= T_BLOCK_SIZE;
			VAL(ptr) = 0;
			return 1;
		}
		z = z->next;
	}
	return 0;
}

void			free(void *ptr)
{
	if (ptr == NULL)
		return ;

	if (!check_zone(get_zones(TINY_SIZE), ptr))
		if(!check_zone(get_zones(SMALL_SIZE), ptr))
			check_zone(get_zones(SMALL_SIZE + 10), ptr);
}
