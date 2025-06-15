/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 prompt.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/12 11:37:16 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/12 11:40:58 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"
#include "log.h"

int	main(void)
{
	char	*line;
	t_ctx	*ctx;

	ctx = init_ctx();
	if (!ctx)
		return (1);
	while (1)
	{
		line = readline("> ");
		if (line)
		{
			if (tokenize_line(ctx, line) == -1)
			{
				print_shell_error("error while parsing line");
				free_parser(ctx);
			}
			else
				if (expand_tokens(ctx) == -1)
					continue ;
			free(line);
		}
	}
	free_ctx(ctx);
	return (0);
}
