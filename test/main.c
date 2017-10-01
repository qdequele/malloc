/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/01 13:57:29 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	test_malloc(void)
{
	int		err;
	char	*str;
	int		i;
	
	err = 0;
	i = 290;
	while (i < 310)
	{
		printf("malloc de %d\n", i);
		str = (char*)malloc(i);
		str[0] = 42;
		i += 1;
	}
	show_alloc_mem();
	printf("\t 1) ok\n");
	return err;
}

int	test_free(void)
{
	int		err;
	char	*str;
	int		i;
	
	err = 0;
	i = 290;
	while (i < 310)
	{
		printf("malloc de %d\n", i);
		str = (char*)malloc(i);
		str[0] = 42;
		free(str);
		str = (char*)malloc(i);
		str[0] = 42;
		i++;
	}
	show_alloc_mem();
	printf("\t 1) ok\n");
	return err;
}

int	test_realloc(void)
{
	int err;

	err = 0;
	printf("\t 1) ok\n");
	return err;
}

int main(void)
{
	int err;

	err = 0;
	printf("-- Test - Malloc\n");
	err += test_malloc();
	printf("-- Test - Free\n");
	// err += test_free();
	printf("-- Test - Realloc\n");
	err += test_realloc();
	return err;
}
