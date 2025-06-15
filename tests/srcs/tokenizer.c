/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 tokenizer.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 12:34:01 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/14 12:40:00 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "test.h"
#include "parser.h"

static void	print_tokens(t_list *tok_lst);

int	main(int ac, char **av)
{
	t_ctx	*ctx;
	FILE	*fp;
	char	*line;
	size_t	len;

	if (ac < 2)
		return (-1);
	ctx = init_ctx();
	fp = fopen(av[1], "r");
	if (!fp)
		exit(1);
	while ((getline(&line, &len, fp)) != -1)
	{
		tokenize_line(ctx, strip_newline(line));
		print_tokens(ctx->tokenizer->tokens);
	}
	fclose(fp);
}

static void	print_tokens(t_list *tok_lst)
{
	t_list	*current;

	current = tok_lst;
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}
