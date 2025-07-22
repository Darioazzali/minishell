/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 history_utils.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: aluque-v <aluque-v@student.42barcelon		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/20 08:58:29 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/20 08:58:44 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

/** @brief Add line to history structure
 * Add line to history structure and add it to the history list
 * @param line line to add
 * @param hist history structure
 *
 * @note if line is NULL or empty, return
 * @note Can fail if malloc fails
 * */
void	add_to_history_struct(char *line, t_history *hist)
{
	char	*hist_line;
	t_list	*node;

	if (!line || !hist || is_empty_line(line))
		return ;
	add_history(line);
	hist_line = ft_strdup(line);
	if (!hist_line)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		return ;
	}
	node = ft_lstnew(hist_line);
	if (!node)
	{
		print_shell_error(MALLOC_ERROR_MSG);
		free(hist_line);
		return ;
	}
	ft_lstadd_or_assign(&hist->head, node);
}

void	free_history_struct(t_history *hist)
{
	if (!hist)
		return ;
	if (hist->head)
		ft_lstclear(&hist->head, free);
	free(hist);
}
