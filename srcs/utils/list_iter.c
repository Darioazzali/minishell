/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 list_iter.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/24 13:19:42 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/24 13:22:48 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast.h"

void	build_lst_iter(t_lst_iter *iter, t_list *lst)
{
	iter->lst = lst;
}

bool	lst_iter_is_valid(t_lst_iter *iter)
{
	return (iter && iter->lst != NULL);
}

t_token	*lst_iter_current(t_lst_iter *iter)
{
	if (!lst_iter_is_valid(iter))
		return (NULL);
	return ((t_token *)iter->lst->content);
}

void	lst_iter_advance(t_lst_iter *iter)
{
	if (lst_iter_is_valid(iter))
		iter->lst = iter->lst->next;
}
