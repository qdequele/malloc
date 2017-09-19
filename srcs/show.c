/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/19 19:05:19 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"


int		show_debug_zone(t_zone **zone, char *type)
{
	size_t	sum;
	size_t	i;
	void	*ptr;

	sum = 0;
	if ((*zone) == NULL)
		return 0;
	while (*zone)
	{
		i = 0;
		printf("%s : %p | %zu blocks\n", type, (*zone), (*zone)->nb_max_blocks);
		ptr = (void *)(*zone) + T_ZONE_SIZE;
		while (i < (*zone)->nb_max_blocks)
		{
			if (VAL(ptr) != 0)
				printf("n°%zu : %p - %p : %zu octets\n",i, ptr + T_BLOCK_SIZE, ptr + T_BLOCK_SIZE + VAL(ptr), VAL(ptr));
			i++;
			sum += VAL(ptr);
			ptr += T_BLOCK_SIZE + ZONE_SIZE((*zone)->type);
		}
		(*zone) = (*zone)->next;

	}
	return sum;
}

int		show_alloc_zone(t_zone **zone, char *type)
{
	size_t	sum;
	size_t	i;
	void	*ptr;

	sum = 0;
	if ((*zone) == NULL)
		return 0;
	while (*zone)
	{
		i = 0;
		printf("%s : %p \n", type, (*zone));
		ptr = (void *)(*zone) + T_ZONE_SIZE;
		while (i < (*zone)->nb_max_blocks)
		{
			if (VAL(ptr) != 0)
				printf("%p - %p : %zu octets\n", ptr + T_BLOCK_SIZE, ptr + T_BLOCK_SIZE + VAL(ptr), VAL(ptr));
			i++;
			sum += VAL(ptr);
			ptr += T_BLOCK_SIZE + ZONE_SIZE((*zone)->type);
		}
		(*zone) = (*zone)->next;

	}
	return sum;
}

void			show_alloc_mem(void)
{
	size_t		sum;

	sum = 0;
	if (DEBUG)
	{
		sum += show_debug_zone(get_zones(TINY_SIZE), "TINY");
		sum += show_debug_zone(get_zones(SMALL_SIZE), "SMALL");
		sum += show_debug_zone(get_zones(SMALL_SIZE + 10), "LARGE");
	}
	else
	{
		sum += show_alloc_zone(get_zones(TINY_SIZE), "TINY");
		sum += show_alloc_zone(get_zones(SMALL_SIZE), "SMALL");
		sum += show_alloc_zone(get_zones(SMALL_SIZE + 10), "LARGE");
	}
	
	printf("Total %zu octets\n", sum);
}