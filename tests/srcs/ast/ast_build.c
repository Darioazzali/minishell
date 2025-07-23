/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ast_build.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/25 09:28:27 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/25 09:29:39 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "ast_test.h"

extern char	**environ;
static void	_free_test(void *content);
static int	make_test(char *line, char *expected);
char		g_buff[1024] = {0};

int	main(int argc, char **argv)
{
	char	*file_path;
	t_list	*test_lst;
	t_test	*test;
	t_cd_t	test_res;
	int		status;

	if (argc != 2)
		exit(1);
	file_path = *(argv + 1);
	test_lst = parse_test_file(file_path);
	if (!test_lst)
		return (1);
	init_test_result(&test_res);
	status = 0;
	while (test_lst)
	{
		test = test_lst->content;
		status = make_test(test->line, test->expected);
		test_res.t_total++;
		test_res.status |= status;
		if (status == 1)
			test_res.t_fail++;
		else
			test_res.t_succ++;
		test_lst = test_lst->next;
	}
	ft_lstclear(&test_lst, _free_test);
	_print_test_result(&test_res);
	return (test_res.status);
}

static void	_reset_buf(void)
{
	ft_memset(g_buff, 0, 1024);
}

static t_test	*_setup(void)
{
	t_ctx	*ctx;
	t_test	*test;
	char	**env;

	ctx = NULL;
	_reset_buf();
	env = environ;
	test = malloc(sizeof(t_test));
	if (!test)
	{
		log_error("Failed to allocate memory for test");
		return (NULL);
	}
	init_program(&ctx, env);
	test->line = NULL;
	test->expected = NULL;
	test->ctx = ctx;
	return (test);
}

static int	make_test(char *line, char *expected)
{
	static t_parser	parser = {0};
	t_ast_node		*node;
	t_test			*test;
	int				status;

	status = 0;
	test = _setup();
	assert(test);
	test->line = line;
	test->expected = expected;
	node = parse_new_line(test->line, &parser, test->ctx);
	if (!node) {
		log_error("Failed to build AST");
		return (1);
	}
	traverse_ast(node, test_visit, NULL);
	if (strcmp(g_buff, test->expected))
	{
		test_fail(test->line, NULL);
		printf("Test failed\n");
		printf("%12s %s\n", "Line: ", test->line);
		printf("%12s %s\n", "Expected: ", test->expected);
		printf("%12s %s\n", "Got: ", g_buff);
		status = 1;
	}
	else
		test_success(test->line, NULL);
	free_ast_node(node);
	free_ctx(test->ctx);
	free(test);
	return (status);
}

static void	_free_test(void *content)
{
	t_test	*test;

	if (!content)
		return ;
	test = content;
	if (test->line)
		free(test->line);
	if (test->expected)
		free(test->expected);
	if (test->ctx)
		free_ctx(test->ctx);
	free(test);
	return ;
}
