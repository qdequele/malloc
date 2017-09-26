/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/26 10:31:32 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		show_debug_zone(t_zone **zone, char *type)
{
	size_t	sum;
	size_t	i;
	void	*ptr;
	t_zone	*z;

	sum = 0;
	z = *zone;
	if (z == NULL)
		return (0);
	while (z)
	{
		i = -1;
		printf("%s : %p | %zu blocks\n", type, z, z->nb_max_blocks);
		ptr = (void *)z + T_ZONE_SIZE;
		while (++i < z->nb_max_blocks)
		{
			if (VAL(ptr) != 0)
				printf("n°%zu : %p - %p : %zu octets\n", i, ptr + T_BLOCK_SIZE,
					ptr + T_BLOCK_SIZE + VAL(ptr), VAL(ptr));
			sum += VAL(ptr);
			ptr += T_BLOCK_SIZE + z->type;
		}
		z = z->next;
	}
	return (sum);
}

int		show_alloc_zone(t_zone **zone, char *type)
{
	size_t	sum;
	size_t	i;
	void	*ptr;
	t_zone	*z;

	sum = 0;
	z = *zone;
	if (z == NULL)
		return (0);
	while (z)
	{
		i = -1;
		printf("%s : %p \n", type, z);
		ptr = (void *)z + T_ZONE_SIZE;
		while (++i < z->nb_max_blocks)
		{
			if (VAL(ptr) != 0)
				printf("%p - %p : %zu octets\n", ptr + T_BLOCK_SIZE,
					ptr + T_BLOCK_SIZE + VAL(ptr), VAL(ptr));
			sum += VAL(ptr);
			ptr += T_BLOCK_SIZE + z->type;
		}
		z = z->next;
	}
	return (sum);
}

void	show_alloc_mem(void)
{
	size_t		sum;

	sum = 0;
	if (DEBUG)
	{
		sum += show_debug_zone(get_zones(TINY), "TINY");
		sum += show_debug_zone(get_zones(SMALL), "SMALL");
		sum += show_debug_zone(get_zones(SMALL + 10), "LARGE");
	}
	else
	{
		sum += show_alloc_zone(get_zones(TINY), "TINY");
		sum += show_alloc_zone(get_zones(SMALL), "SMALL");
		sum += show_alloc_zone(get_zones(SMALL + 10), "LARGE");
	}
	printf("Total %zu octets\n", sum);
}
