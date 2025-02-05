/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:17:24 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/13 19:22:59 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	parity;
	int	result;
	int	sign_count;

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
