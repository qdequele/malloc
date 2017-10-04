/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/04 18:22:32 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

#define M1 (1024 * 1024)

int	g_ttx;

typedef void		(*t_func)(void);

typedef struct		s_functions
{
	char			*num;
	int				size;
	t_func			f;
}					t_functions;

void	test_malloc_0(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		i++;
	}
}

void	test_malloc_1(void)
{
	char	*str;
	int		i;

	str = malloc(42);
	str = malloc(420);
	str = malloc(4200);
}

void	test_malloc_2(void)
{
	char	*str;
	int		i;

	i = 1;
	while (i < 200)
	{
		str = malloc(i);
		str[0] = 42;
		i++;
	}
}

void	test_free_1(void)
{
	char	*str;
	int		i;

	i = 290;
	while (i < 310)
	{
		str = malloc(i);
		str[0] = 42;
		free(str);
		str = malloc(i);
		str[0] = 42;
		i++;
	}
}

void	test_realloc_1(void)
{
	char	*addr;
	char	*test;

	addr = malloc(90);
	test = realloc(addr, 10);
}

void	test_realloc_2(void)
{
	char	*str;

	str = malloc(1024);
	str = realloc(str, 1024 * 3);
	str = realloc(str, 1024 / 2);
	str = realloc(str, 1024 * 10);
	str = realloc(str, 1024 / 10);
}

void	test_realloc_3(void)
{
	char	*str;
	int		i;

	str = malloc(10);
	i = 0;
	while (i < 10)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';
	str = realloc(str, 15);
}

void	test_realloc_4(void)
{
	char	*str;
	int		i;

	str = malloc(1000);
	i = 0;
	while (i < 1000)
	{
		str[i] = i + 'a';
		i++;
	}
	str[i] = '\0';
	str = realloc(str, 5);
}

void	test_speed_1(void)
{
	char	*str;
	int		i;

	i = 1;
	while (i < 10000)
	{
		str = malloc(i);
		str[0] = 42;
		i += 1;
	}
}

int	test(char *num, t_func f, int size)
{
	int		ttx;
	f();

	ttx = show_alloc_mem_test();
	if (ttx - g_ttx != size)
	{
		
		ft_putstr(num);
		ft_putstr(") Error | ");
		ft_putnbr(ttx - g_ttx);
		ft_putstr(" != ");
		ft_putnbr(size);
		ft_putstr("\n");
		g_ttx = ttx;
		return (1);
	}
	else
	{
		g_ttx = ttx;
		ft_putstr(num);
		ft_putstr(") OK\n");
		return (0);
	}
}

int	main(void)
{
	int err;
	int i;
	t_functions	f[] = {
		{"1.0", 0, test_malloc_0},
		{"1.1", 4662, test_malloc_1},
		{"1.2", 19900, test_malloc_2},
		{"2.1", 5990, test_free_1},
		{"3.1", 10, test_realloc_1},
		{"3.2", 102, test_realloc_2},
		{"3.3", 15, test_realloc_3},
		{"3.4", 5, test_realloc_4},
		{"4.1", 49995000, test_speed_1},
		{NULL, 0,  NULL}
	};
	i = 0;
	while (f[i].num)
	{
		err += test(f[i].num, f[i].f, f[i].size);
		i++;
	}
	return err;
}
