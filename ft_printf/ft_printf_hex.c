/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:43:52 by tayki             #+#    #+#             */
/*   Updated: 2024/08/20 13:14:45 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_ptr_arg(va_list args, int *p_len)
{
	unsigned long long	d;

	d = (unsigned long long)va_arg(args, unsigned long long);
	if (d == 0)
	{
		ft_putstr("(nil)");
		(*p_len) += 5;
	}
	else
	{
		ft_putstr("0x");
		(*p_len) += 2;
		ft_puthexnbr(d);
		while (d != 0)
		{
			(*p_len)++;
			d /= 16;
		}
	}
}

void	ft_print_hexl_arg(va_list args, int *p_len)
{
	unsigned int	d;

	d = (unsigned int)va_arg(args, unsigned int);
	ft_puthexnbr(d);
	if (d == 0)
		(*p_len)++;
	while (d != 0)
	{
		(*p_len)++;
		d /= 16;
	}
}

void	ft_print_hexb_arg(va_list args, int *p_len)
{
	unsigned int	d;

	d = (unsigned int)va_arg(args, unsigned int);
	ft_puthexnbrbig(d);
	if (d == 0)
		(*p_len)++;
	while (d != 0)
	{
		(*p_len)++;
		d /= 16;
	}
}
