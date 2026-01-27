/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:23:43 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/27 17:32:34 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ns1;
	const unsigned char	*ns2;
	size_t				i;

	ns1 = (const unsigned char *)s1;
	ns2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && ns1[i] == ns2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (ns1[i] - ns2[i]);
}
