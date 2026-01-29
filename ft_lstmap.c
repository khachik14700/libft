/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:51:12 by kkhachat          #+#    #+#             */
/*   Updated: 2026/01/29 17:14:29 by kkhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_list;
	void	*new_content;
	t_list	*node;

	if (lst == NULL || f == NULL)
		return (NULL);
	current = lst;
	new_list = NULL;
	while (current)
	{
		new_content = f(current->content);
		node = ft_lstnew(new_content);
		if (!node)
		{
			if (del != NULL)
				del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, node);
		current = current->next;
	}
	return (new_list);
}
