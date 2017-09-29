/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/29 14:48:18 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_lstdel_at(t_zone **list)
{
	t_zone	*tmp;
	t_zone	*prev;

	if (!list || !(*list))
		return ;
	tmp = *list;
	prev = NULL;
	while (tmp->nb_blocks != 0 && tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev)
		prev->next = tmp->next;
	else
		*list = tmp->next;
	munmap(tmp, tmp->zone_length);
}

void		*smmap(size_t len)
{
	size_t	mult;
	size_t	f_len;

	mult = (len / PAGE_SIZE) + 1;
	f_len = mult * PAGE_SIZE;
	return (mmap(NULL, f_len, PROT, MAP, -1, 0));
}

t_zone		**get_zones(void)
{
	static t_zone	*zone;

	return (&zone);
}

void		free_block(t_zone **zone, void *ptr)
{
	t_zone	*z;

	z = *zone;
	VAL(ptr) = 0;
	z->nb_blocks--;
	if (z->nb_blocks <= 0)
		ft_lstdel_at(get_zones());
}


