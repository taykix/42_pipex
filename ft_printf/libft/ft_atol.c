/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:25:24 by tkarakay          #+#    #+#             */
/*   Updated: 2025/01/26 17:32:39 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		parity;
	long	result;
	int		sign_count;

	result = 0;
	parity = 1;
	sign_count = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		++nptr;
	while (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			parity *= -1;
		++nptr;
		sign_count++;
	}
	if (sign_count > 1)
		return (0);
	while (ft_isdigit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		++nptr;
	}
	return (result * parity);
}
