/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 expander.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 09:25:17 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/14 09:40:36 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include "test.h"

static	void	print_tokens(t_list *tokens);

int	main(int ac, char **av)
{
	t_ctx		*ctx;
	t_list		*tok_lst;
	FILE		*fp;
	char		*line;
	size_t		len;
	t_list		*node;
	char		*cloned;
	t_lexer	parser = {0};

	if (ac < 2)
		return (-1);
	ctx = init_ctx();
	tok_lst = NULL;
	fp = fopen(av[1], "r");
	if (!fp)
		exit(1);
	line = NULL;
	while (getline(&line, &len, fp) != -1)
	{
		cloned = ft_strdup(strip_newline(line));
		node = ft_lstnew(cloned);
		ft_lstadd_back(&tok_lst, node);
		free(line);
		line = NULL;
	}
	free(line);
	fclose(fp);
	ctx->lexer = &parser;
	if (!ctx->lexer)
		return (-1);
	parser.tokens = tok_lst;
	remove_quotes(ctx);
	print_tokens(tok_lst);
	ft_lstclear(&tok_lst, free);
	free_ctx(ctx);
}

static	void	print_tokens(t_list *tokens)
{
	t_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
