/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/24 15:35:14 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex_stock);
	ptr = do_malloc(size);
	pthread_mutex_unlock(&g_mutex_stock);
	return (ptr);
}

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex_stock);
	do_free(ptr);
	pthread_mutex_unlock(&g_mutex_stock);
}

void		*realloc(void *ptr, size_t size)
{
	void	*ptr2;

	pthread_mutex_lock(&g_mutex_stock);
	ptr2 = do_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex_stock);
	return (ptr2);
}

void		show_alloc_mem(void)
{
	size_t		sum;

	pthread_mutex_lock(&g_mutex_stock);
	sum = show_alloc_zone(get_zones());
	ft_putstr("Total ");
	ft_putuint(sum);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_mutex_stock);
}
