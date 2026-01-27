/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 19:01:05 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/26 20:27:05 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	ch;
	size_t			i;
	unsigned char	*ns;

	ch = (unsigned char)c;
	i = 0;
	ns = (unsigned char *)s;
	while (i < n)
	{
		ns[i] = ch;
		i++;
	}
	return (s);
}
