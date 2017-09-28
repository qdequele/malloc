/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/28 14:34:06 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	print_type(t_zone_type type)
{
	if (type == TINY)
		write(1, "TINY ", 5);
	else if (type == SMALL)
		write(1, "SMALL ", 6);
	else
		write(1, "LARGE ", 6);
}

int		show_debug_zone(t_zone **zone)
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
		print_type(z->type);
		printf(": %p | %zu/%zu blocks\n", z, z->nb_blocks, 
			z->nb_max_blocks);
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

int		show_alloc_zone(t_zone **zone)
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
		print_type(z->type);
		printf(": %p \n", z);
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
		sum += show_debug_zone(get_zones());
	else
		sum += show_alloc_zone(get_zones());
	printf("Total %zu octets\n", sum);
}
