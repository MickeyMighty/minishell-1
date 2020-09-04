/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_one_if.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:07:37 by lenox             #+#    #+#             */
/*   Updated: 2020/09/04 11:49:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_list_remove_one_if(t_list **begin_list, void *data_ref,
		int (*cmp)(), void (*free_fct)(void *))
{
		t_list	*tmp;

	if (begin_list && *begin_list)
	{
		if (!(*cmp)((*begin_list)->content, data_ref))
		{
			tmp = (*begin_list);
			(*begin_list) = tmp->next;
			(*free_fct)(tmp->content);
			free(tmp);
			return ;			
		}
		else
			ft_list_remove_if(&(*begin_list)->next, data_ref, cmp, free_fct);
	}
}