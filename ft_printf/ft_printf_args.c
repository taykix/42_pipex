/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:16:15 by tayki             #+#    #+#             */
/*   Updated: 2024/08/20 13:14:49 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_char_arg(va_list args, int *p_len)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar(c);
	(*p_len)++;
}

void	ft_print_str_arg(va_list args, int *p_len)
{
	char	*s;

	s = (char *)va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	ft_putstr(s);
	(*p_len) = (*p_len) + ft_strlen(s);
}

void	ft_print_int_arg(va_list args, int *p_len)
{
	int	d;

	d = (int)va_arg(args, int);
	ft_putnbr(d);
	if (d == 0)
		(*p_len)++;
	if (d < 0)
		(*p_len)++;
	while (d != 0)
	{
		(*p_len)++;
		d /= 10;
	}
}

void	ft_print_u_arg(va_list args, int *p_len)
{
	unsigned int	d;

	d = va_arg(args, int);
	ft_putnbr_u(d);
	if (d == 0)
		(*p_len)++;
	while (d != 0)
	{
		(*p_len)++;
		d /= 10;
	}
}

void	ft_print_delim_arg(const char *p, int *p_len)
{
	ft_putchar('%');
	ft_putchar(*p);
	(*p_len) = *p_len + 2;
}
