/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:32:29 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/27 17:02:16 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	if (i > 0)
	{
		while (i > 0 && (unsigned char)s[i] != (unsigned char)c)
			i--;
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)(s + i));
		else
			return (0);
	}
	else
		return (0);
}
