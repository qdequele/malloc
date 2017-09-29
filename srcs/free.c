/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/29 11:21:43 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		check_free_zone(t_zone **zone, void *ptr)
{
	t_zone	*z;

	z = *zone;
	while (z)
	{
		if (ptr > (void *)z && ptr < (void *)z + z->zone_length)
		{
			ptr -= T_BLOCK_SIZE;
			free_block(&z, ptr);
			return (1);
		}
		z = z->next;
	}
	return (0);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	check_free_zone(get_zones(), ptr);
}
