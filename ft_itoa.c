/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:11:22 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/28 20:33:02 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	size(long long nb, size_t *len)
{
	while (nb)
	{
		nb /= 10;
		(*len)++;
	}
}

static char	*for_zero(void)
{
	char	*result;

	result = (char *)malloc(2);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

static void	is_neg(long long *nb, int *sign, size_t *len)
{
	if (*nb < 0)
	{
		(*sign) *= -1;
		(*nb) *= -1;
		(*len)++;
	}
}

char	*ft_itoa(int n)
{
	long long	nb;
	int			sign;
	size_t		len;
	char		*result;

	nb = n;
	sign = 1;
	len = 0;
	if (nb == 0)
		return (for_zero());
	is_neg(&nb, &sign, &len);
	size(nb, &len);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len--] = '\0';
	while (nb)
	{
		result[len] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	if (sign == -1)
		result[0] = '-';
	return (result);
}
