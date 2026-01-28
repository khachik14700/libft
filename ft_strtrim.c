/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:22:05 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/28 18:08:21 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(const char c, char const *set)
{
	size_t	i;
	size_t	len_set;

	i = 0;
	len_set = ft_strlen(set);
	while (i < len_set)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	len_s;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len_s = ft_strlen(s1);
	if (len_s == 0)
		return (ft_strdup(""));
	start = 0;
	while (s1[start] && in_set(s1[start], set))
		start++;
	end = len_s - 1;
	while (end > start && in_set(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	result = ft_substr(s1, start, end - start + 1);
	return (result);
}
