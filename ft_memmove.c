/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 20:50:51 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/26 21:40:47 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ndest;
	unsigned char	*nsrc;
	size_t			i;

	ndest = (unsigned char *)dest;
	nsrc = (unsigned char *)src;
	i = 0;
	if (ndest == nsrc || n == 0)
		return (dest);
	if (ndest < nsrc)
	{
		while (i < n)
		{
			ndest[i] = nsrc[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			ndest[n] = nsrc[n];
	}
	return (dest);
}
