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
#include "parser.h"

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
				print_error("minishell: Error while parsing line\n");
				free_parser(ctx);
			}
			else
			{
				log_debug(ctx->logger, deb_format_tokens(ctx->parser->tokens));
			}
			free(line);
		}
	}
	free_ctx(ctx);
	return (0);
}
