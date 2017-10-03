/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 10:51:35 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int	test_malloc(void)
{
	char	*str;
	int		i;

	i = 290;
	while (i < 310)
	{
		str = (char*)malloc(i);
		str[0] = 42;
		i += 1;
	}
	if (show_alloc_mem_test() != 5990)
		return (1);
	return (0);
}

int	test_free(void)
{
	char	*str;
	int		i;
	
	i = 290;
	while (i < 310)
	{
		str = (char*)malloc(i);
		str[0] = 42;
		free(str);
		str = (char*)malloc(i);
		str[0] = 42;
		i++;
	}
	if (show_alloc_mem_test() != 5990 * 2)
		return (1);
	return (0);
}

int	test_realloc(void)
{
	char	*addr;
	char	*test;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	test = realloc((void *)addr + 5, 10);
	if (test == NULL)
	{
		printf("Bonjours\n");
		return (1);
	}
	return (0);
}

int main(void)
{
	int err;

	err = 0;
	printf("-- Test - Malloc\n");
	err += test_malloc();
	printf("-- Test - Free\n");
	err += test_free();
	printf("-- Test - Realloc\n");
	err += test_realloc();
	return err;
}
