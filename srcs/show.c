/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 16:06:47 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

char	*print_type(t_zone_type type)
{
	if (type == TINY)
		return ("TINY ");
	else if (type == SMALL)
		return ("SMALL ");
	else
		return ("LARGE ");
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
		ft_putstr(print_type(z->type));
		ft_putstr(" : ");
		ft_puthex(z);
		ft_putstr(" | ");
		ft_putnbr(z->nb_blocks);
		ft_putstr("/");
		ft_putnbr(z->nb_max_blocks);
		ft_putstr(" blocks\n");
		ptr = (void *)z + T_ZONE_SIZE;
		while (++i < z->nb_max_blocks)
		{
			if (VAL(ptr) != 0)
			{
				ft_puthex(ptr + T_BLOCK_SIZE);
				ft_putstr(" - ");
				ft_puthex(ptr + T_BLOCK_SIZE + VAL(ptr));
				ft_putstr(" : ");
				ft_putuint(VAL(ptr));
				ft_putstr(" octets\n");
			}
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

	ft_putstr("PUUTE\n");
	sum = show_alloc_zone(get_zones());
	ft_putstr("Total ");
	ft_putuint(sum);
	ft_putstr(" octets\n");
}

int		show_alloc_mem_test(void)
{
	size_t		sum;

	sum = show_alloc_zone(get_zones());
	ft_putstr("Total ");
	ft_putuint(sum);
	ft_putstr(" octets\n");
	return (sum);
}
