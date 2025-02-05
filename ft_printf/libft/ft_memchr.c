/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:16:57 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/13 18:08:16 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*target;
	size_t				i;

	target = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (target[i] == (unsigned char)c)
		{
			return ((void *)(target + i));
		}
		i++;
	}
	return (NULL);
}
