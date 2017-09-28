/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/28 14:51:41 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		ft_lstcount(t_zone *lst)
{
	int		i;
	t_zone	*elem;

	i = 0;
	elem = lst;
	if (elem)
	{
		while (elem)
		{
			i++;
			elem = elem->next;
		}
	}
	return (i);
}

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
	(void)ptr;
	z->nb_blocks--;
	ft_lstdel_at(get_zones());
}

void		copy_blocks(void *old, size_t old_size, void *new, size_t new_size)
{
	size_t	count;
	size_t	i;

	count = (old_size <= new_size) ? old_size : new_size;
	i = 0;
	while (++i <= count)
	{
		new++;
		old++;
		VAL(new) = VAL(old);
	}
}
