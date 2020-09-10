/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_current_node.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 18:19:59 by mkayumba          #+#    #+#             */
/*   Updated: 2020/09/08 18:20:02 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>


void	ft_list_remove_current_node(t_list **begin_list, t_list *to_del, void (*free_fct)(void *))
{
		t_list	*tmp;

	if (begin_list && *begin_list)
	{
		if (*begin_list == to_del)
		{
			tmp = (*begin_list);
			(*begin_list) = tmp->next;
			(*free_fct)(tmp->content);
			free(tmp);
			return ;			
		}
		else
			ft_list_remove_current_node(&(*begin_list)->next, to_del, free_fct);
	}
}