/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:59:34 by tayki             #+#    #+#             */
/*   Updated: 2024/07/16 11:27:21 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digit(long long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			count;
	char		*str;
	long int	num;

	count = count_digit(n);
	num = n;
	if (n < 0)
	{
		num *= -1;
		count++;
	}
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!(str))
		return (NULL);
	*(str + count) = 0;
	while (count--)
	{
		*(str + count) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
	{
		*(str + 0) = '-';
	}
	return (str);
}
