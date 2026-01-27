/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:14:53 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/27 20:17:47 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ns;
	unsigned char	nc;

	i = 0;
	ns = (unsigned char *)s;
	nc = (unsigned char)c;
	while (i < n && ns[i] != nc)
		i++;
	if (i == n)
		return (0);
	else
		return ((void *)(ns + i));
}
