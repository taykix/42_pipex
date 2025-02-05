/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:16:43 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/12 16:06:35 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t n)
{
	size_t			i;
	unsigned char	*d;

	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = (unsigned char)c;
		i++;
	}
	return (dest);
}
