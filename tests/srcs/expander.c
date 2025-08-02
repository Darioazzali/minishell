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

int	main(int ac, char **av, char **env)
{
	t_ctx		*ctx;
	t_list		*tok_lst;
	FILE		*fp;
	char		*line;
	size_t		len;
	ssize_t		read;
	t_lexer	tokenizer={0};

	if (ac < 2)
		return (-1);
	ctx = NULL;
	ctx = init_ctx();
	ctx->envs = parse_envs(env);
	tok_lst = NULL;
	fp = fopen(av[1], "r");
	if (!fp)
	{
		fprintf(stderr, "cannot open file\n");
		exit(1);
	}
	while ((read = getline(&line, &len, fp)) != -1)
		ft_lstadd_back(&tok_lst, ft_lstnew(ft_strdup(strip_newline(line))));
	fclose(fp);
	ctx->lexer = &tokenizer;
	if (!ctx->lexer)
		return (-1);
	ctx->lexer->tokens = tok_lst;
	expand_tokens(ctx);
	print_tokens(tok_lst);
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
