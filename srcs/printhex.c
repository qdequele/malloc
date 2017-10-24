/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 15:21:13 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/24 14:51:03 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		ft_nbrlen_base(int nb, int base)
{
	int		len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / base;
	}
	return (len);
}


void	ft_puthex(void *ptr)
{
	char			str[50];
	size_t			len;
	long long int	n;

	ft_putstr("0x");
	n = (long long int)ptr;
	len = ft_nbrlen_base(n, 16);
	str[len] = '\0';
	while ((len--) > 0)
	{
		str[len] = (n % 16) + ((n % 16) > 9 ? 'a' - 10 : '0');
		n = n / 16;
	}
	ft_putstr(str);
}
