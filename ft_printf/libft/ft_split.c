/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:48:55 by tkarakay          #+#    #+#             */
/*   Updated: 2024/07/16 15:08:54 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

int	safe_malloc(char **token_s, int pos, size_t buffer)
{
	int	i;

	i = 0;
	token_s[pos] = (char *)malloc(buffer);
	if (token_s[pos] == NULL)
	{
		while (i < pos)
		{
			free(token_s[i++]);
		}
		free(token_s);
		return (1);
	}
	return (0);
}

int	ft_fill(char **lst, char const *s, char delimiter)
{
	size_t	len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimiter && *s)
			++s;
		while (*s != delimiter && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(lst, i, len + 1))
				return (1);
			ft_strlcpy(lst[i], s - len, len + 1);
		}
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**lst;
	size_t	token_count;

	if (NULL == s)
		return (NULL);
	token_count = ft_countword(s, c);
	lst = (char **)malloc((token_count + 1) * sizeof(char *));
	if (lst == NULL)
		return (NULL);
	lst[token_count] = NULL;
	if (ft_fill(lst, s, c))
		return (NULL);
	return (lst);
}
