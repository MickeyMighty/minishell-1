/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_all.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mkayumba <mkayumba@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2020/08/22 18:20:17 by mkayumba		  #+#	#+#			 */
/*   Updated: 2020/10/12 15:07:54 by mkayumba		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void				free_nothing(void *ptr)
{
	(void)ptr;
}

void	clear_token(void *content)
{
   t_token  *token;
   
	if (!content)
		return ;
	token = (t_token *)content;
	if (token && token->value)
	{
		ft_memdel(&token->value);
	}
	free(token);
	(void)token;
	(void)content;
}

void	free_btree(void *ptr)
{
	t_list *list;

	list = (t_list *)ptr;
	ft_lstclear(&list, clear_token);
}

int free_all(t_info *info, int code_return)
{
	// ft_btree_clear(info->root, &clear_token);
	ft_btree_clear(info->root, &free_btree);
	//ft_lstclear(&info->list_input, &clear_token);
	info->root = 0;
	info->list_input = 0;
	if (code_return == ERROR)
	{
		ft_lstclear(&info->list_env, &ft_free_string);
		info->list_env = 0;
	}
	ft_free_string(info->str_input);
	info->str_input = 0;
	ft_lstclear(&info->list_path, ft_free_string);
	info->list_path = 0;
	free(info->tab_var_env);
	info->tab_var_env = 0;
	ft_lstclear(&info->stack, free_nothing);
	info->stack = 0;
	return (code_return);
}