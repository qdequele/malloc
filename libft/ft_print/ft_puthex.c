/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:12:26 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 16:05:34 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void			ft_puthex(void *ptr)
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
