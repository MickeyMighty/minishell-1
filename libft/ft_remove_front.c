/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 11:21:13 by user42            #+#    #+#             */
/*   Updated: 2020/09/06 18:05:29 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void        ft_remove_front(t_list **begin, void (*free_fct)(void *))
{
    t_list  *to_free;

    if (begin && *begin)
    {
        to_free = *begin;
        (*begin) = to_free->next;
        (*free_fct)(to_free->content);
        free(to_free);
    }
}