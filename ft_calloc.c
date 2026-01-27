/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 19:03:28 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/27 19:31:13 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			mall_size;
	unsigned char	*result;
	size_t			i;

	if (nmemb == 0 || size == 0)
	{
		result = malloc(1);
		return ((void *)result);
	}
	else
	{
		mall_size = nmemb * size;
		result = malloc(mall_size);
		if (!result)
			return (NULL);
		i = 0;
		while (i < mall_size)
			result[i++] = 0;
		return ((void *)result);
	}
}
