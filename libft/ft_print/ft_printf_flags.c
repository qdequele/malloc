/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdequele <qdequele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:12:26 by qdequele          #+#    #+#             */
/*   Updated: 2017/10/03 11:44:24 by qdequele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int			printf_flag_s(va_list ap)
{
	char	*s;

	s = va_arg(ap, char *);
	ft_putstr(s);
	return (ft_strlen(s));
}

int			printf_flag_c(va_list ap)
{
	char	c;

	c = (char)va_arg(ap, int);
	ft_putchar(c);
	return (1);
}

int			printf_flag_d(va_list ap)
{
	char	*d;

	d = ft_itoa(va_arg(ap, int));
	ft_putstr(d);
	return (ft_strlen(d));
}

int			printf_flag_p(va_list ap)
{
	char	*d;

	d = ft_itoa_base(va_arg(ap, int), 16);
	ft_putstr("0x");
	ft_putstr(d);
	return (ft_strlen(d) + 2);
}

int			printf_flag_z(va_list ap)
{
	char	*d;

	d = ft_itoa(va_arg(ap, int));
	ft_putstr(d);
	return (ft_strlen(d));
}
