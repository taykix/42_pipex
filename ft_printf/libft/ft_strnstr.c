/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:57:29 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/13 18:09:35 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	size_t	big_len;

	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (little_len == 0)
		return ((char *)big);
	if (big_len < little_len || len < little_len)
		return (NULL);
	i = 0;
	while (i <= len - little_len && i <= big_len - little_len)
	{
		j = 0;
		while (j < little_len && big[i + j] == little[j])
		{
			j++;
		}
		if (j == little_len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
