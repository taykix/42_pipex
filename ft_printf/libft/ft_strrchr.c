/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:16:02 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/16 12:12:16 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_size;

	s_size = ft_strlen(s);
	while (s_size >= 0)
	{
		if (s[s_size] == (char)c)
		{
			return ((char *)s + s_size);
		}
		s_size--;
	}
	return (NULL);
}
