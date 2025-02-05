/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:12:39 by tkarakay          #+#    #+#             */
/*   Updated: 2024/08/20 11:23:36 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr("-2147483648");
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	ft_putnbr_u(unsigned int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	else
		ft_putchar(n + '0');
}

void	ft_puthexnbr(unsigned long long n)
{
	if (n >= 16)
		ft_puthexnbr(n / 16);
	ft_putchar("0123456789abcdef"[n % 16]);
}

void	ft_puthexnbrbig(unsigned long long n)
{
	if (n >= 16)
		ft_puthexnbrbig(n / 16);
	ft_putchar("0123456789ABCDEF"[n % 16]);
}
