/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:16:11 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/12 16:04:09 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i] && n > 0)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		n--;
		i++;
	}
	if (n != 0)
	{
		if ((unsigned char)s1[i])
			return ((unsigned char)s1[i]);
		else
			return (-(unsigned char)s2[i]);
	}
	return (0);
}
