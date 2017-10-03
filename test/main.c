/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 16:59:49 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include "../libft/libft.h"

int	g_ttx;

int	test_malloc_1(void)
{
	char	*str;
	int		i;
	int		ttx;

	str = (char*)malloc(42);
	str = (char*)malloc(420);
	str = (char*)malloc(4200);
	ttx = show_alloc_mem_test();
	if (ttx - g_ttx != 4662)
	{
		g_ttx = ttx;
		ft_putstr("\t 1) Error\n");
		return (1);
	}
	else
	{
		g_ttx = ttx;
		ft_putstr("\t 1) OK\n");
		return (0);
	}
	return (0);
}

int	test_malloc_2(void)
{
	char	*str;
	int		i;
	int		ttx;

	i = 290;
	while (i < 310)
	{
		str = (char*)malloc(i);
		str[0] = 42;
		i += 1;
	}
	ttx = show_alloc_mem_test();
	if (ttx - g_ttx != 5990)
	{
		g_ttx = ttx;
		ft_putstr("\t 2) Error\n");
		return (1);
	}
	else
	{
		g_ttx = ttx;
		ft_putstr("\t 2) OK\n");
		return (0);
	}
	return (0);
}

int	test_free(void)
{
	char	*str;
	int		i;
	int		ttx;
	
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
	ttx = show_alloc_mem_test();
	
	if (ttx - g_ttx  != 5990)
	{
		g_ttx = ttx;
		ft_putstr("\t 1) Error\n");
		return (1);
	}
	else
	{
		g_ttx = ttx;
		ft_putstr("\t 1) OK\n");
		return (0);
	}
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
	if (test != NULL)
	{
		ft_putstr("\t 1) Err\n");
		return (1);
	}
	else
	{
		ft_putstr("\t 1) OK\n");
		return (0);
	}
}

int main(void)
{
	int err;

	err = 0;
	g_ttx = 0;
	ft_putstr("-- Test - Malloc\n");
	err += test_malloc_1();
	err += test_malloc_2();
	ft_putstr("-- Test - Free\n");
	err += test_free();
	ft_putstr("-- Test - Realloc\n");
	err += test_realloc();
	ft_putstr("err: ");
	ft_putnbr(err);
	ft_putchar('\n');
	return err;
}
