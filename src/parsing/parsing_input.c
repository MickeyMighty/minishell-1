/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkayumba <mkayumba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:26:53 by mkayumba          #+#    #+#             */
/*   Updated: 2020/10/24 14:37:53 by mkayumba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			parsing_input(char *str_input)
{
	t_list		*input;

	transform_input_in_list_token(str_input);
	input = g_info.list_input;
	interpret_input(&input);
	ft_lstiter(g_info.list_input, &print_token);
	// special_case_redirection(g_info.list_input);
	(void)input;
}