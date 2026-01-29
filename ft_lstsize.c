/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:22:42 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/29 15:29:01 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*current;

	if (lst == NULL)
		return (0);
	size = 1;
	current = lst;
	while (current->next)
	{
		size++;
		current = current->next;
	}
	return (size);
}
