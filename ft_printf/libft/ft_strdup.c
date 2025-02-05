/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:16:35 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/12 16:05:44 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len_s;
	char	*arr;
	char	*ptr;

	len_s = ft_strlen(s);
	arr = malloc((len_s + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ptr = arr;
	while (*s)
	{
		*arr++ = *s++;
	}
	*arr = '\0';
	return (ptr);
}
