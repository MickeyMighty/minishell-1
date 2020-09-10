/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 22:07:43 by mkayumba          #+#    #+#             */
/*   Updated: 2020/09/05 12:28:46 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void        ft_free_double_array(void *ptr)
{
    int     line;
    char    **array;

    array = (char **)ptr;
    line = 0;
    if (!array)
        return ;
    while (array[line])
    {
        free(array[line]);
        array[line] = 0;
        line++;
    }
    free(array);
    array = 0;
}