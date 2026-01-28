/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:54:47 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/28 18:08:50 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static void	*free_all(char **result, size_t k)
{
	size_t	i;

	i = 0;
	while (i < k)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**malloc_all(char const *s, char c, size_t *i, size_t *k)
{
	char	**result;
	size_t	words;

	words = split_count(s, c);
	result = (char **)malloc((words + 1) * sizeof(char *));
	*i = 0;
	*k = 0;
	if (result)
		result[words] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	k;

	if (s == NULL)
		return (NULL);
	result = malloc_all(s, c, &i, &k);
	if (!result)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		result[k++] = ft_substr(s, i, j);
		if (!result[k - 1])
			return (free_all(result, k - 1));
		i += j;
	}
	return (result);
}
