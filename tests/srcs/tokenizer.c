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
static bool	confront_tokens(t_list *tok_lst, t_list *expected);

int	main(int ac, char **av)
{
	t_list			*expected;
	t_json_input_t	*input;
	int				ret_val;
	t_parser		tokenizer={0};

	if (ac < 2)
		return (-1);
	input = read_json_input(av[1]);
	if (!input)
		return (1);
	ret_val = 0;
	if (input)
	{
		if (tokenize_line(&tokenizer, input->input_line) != 0)
			return (1);
		expected = from_array_to_ll(input->input_array, input->array_size);
		if (!confront_tokens(tokenizer.tokens, expected))
			ret_val = 1;
		free_json_input(input);
	}
	return (ret_val);
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

static bool	confront_tokens(t_list *tok_lst, t_list *expected)
{
	char	*expected_str;
	char	*tok_str;

	print_tokens(tok_lst);
	while (tok_lst)
	{
		tok_str = (char *)tok_lst->content;
		expected_str = (char *)expected->content;
		if (strcmp(tok_str, expected_str))
		{
			printf("%s != %s\n", tok_str, expected_str);
			return (false);
		}
		tok_lst = tok_lst->next;
		expected = expected->next;
	}
	return (true);
}
