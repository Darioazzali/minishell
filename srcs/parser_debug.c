/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_debug.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 17:12:36 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 17:13:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"

char	*deb_format_tokens(t_list *lst)
{
	t_list	*tmp;
	char	*str;
	char	*fmt;
	char	*old_fmt;

	if (!DEBUG)
		return (NULL);
	tmp = lst;
	fmt = ft_strdup("Tokens:");
	while (tmp)
	{
		old_fmt = fmt;
		fmt = ft_strjoin(fmt, "\n");
		free(old_fmt);
		str = (char *)tmp->content;
		old_fmt = fmt;
		fmt = ft_strjoin(fmt, str);
		free(old_fmt);
		tmp = tmp->next;
	}
	return (fmt);
}
