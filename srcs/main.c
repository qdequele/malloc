/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/26 10:08:55 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		main(int argc, char **argv)
{
	char	*str;
	void	*ptr;
	int		i;

	i = 290;
	(void)argc;
	(void)argv;
	while (i < 310)
	{
		str = malloc(i);
		if (i == 294)
			ptr = (void *)str;
		i++;
	}
	show_alloc_mem();
	free(ptr);
	return (0);
}
