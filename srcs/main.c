/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/09/20 16:36:51 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *str;
	void *ptr;
	int i = 290;

	while (i < 310)
	{
		str = malloc(i);
		if (i == 294)
			ptr = (void *)str;
		i++;
	}
	show_alloc_mem();
	free(ptr);
	show_alloc_mem();
	return 0;
}
