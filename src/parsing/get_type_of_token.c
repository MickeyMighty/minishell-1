/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_of_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 12:01:22 by mkayumba          #+#    #+#             */
/*   Updated: 2020/09/14 10:00:37 by lenox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_type_of_token(t_list **current)
{
	t_token		*token;

	if (!current || !*current)
		return (ERROR);
	token = (*current)->content;
	return (token->type);
}
