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

static	void	print_tokens_type(t_list *tokens);

int	main(int ac, char **av)
{
	t_ctx	*ctx;
	t_list	*tok_lst;
	FILE	*fp;
	char	*line;
	size_t	len;

	if (ac < 2)
		return (-1);
	ctx = init_ctx();
	tok_lst = NULL;
	fp = fopen(av[1], "r");
	if (!fp)
		exit(1);
	while (getline(&line, &len, fp) != -1)
	{
		ft_lstadd_back(&tok_lst, ft_lstnew(ft_strdup(strip_newline(line))));
	}
	fclose(fp);
	ctx->lexer = malloc(sizeof(t_lexer));
	if (!ctx->lexer)
		return (-1);
	ctx->lexer->tokens = tok_lst;
	recognize_tokens(ctx);
	print_tokens_type(ctx->lexer->tokens);
}

// static int	_add_token(t_list *tok_lst, char *line)
// {
// 	t_list *new_node;
// 	t_token *tok;
//
//
// 	ft_lstadd_back(&tok_lst, ft_lstnew(ft_strdup(strip_newline(line))));
// }

static	void	print_tokens_type(t_list *tokens)
{
	t_list		*tmp;
	t_tok_type	tok_type;
	t_token		*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		tok_type = (token)->type;
		printf("%s\n", get_token_type_str(tok_type));
		tmp = tmp->next;
	}
}
