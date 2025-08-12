/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_build_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:41:29 by dazzali           #+#    #+#             */
/*   Updated: 2025/08/07 11:04:42 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_test.h"

static char	*extract_test_value(char *line);
static void	append_new_test(t_list **lst,
				char	*line,
				char	*name,
				char	*expected);

t_list	*parse_test_file(char *path)
{
	int		fd;
	t_list	*lst;
	char	*line;
	char	*test_name;
	char	*expected;
	char	*input;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Failed to open file %s\n", path);
		return (NULL);
	}
	line = get_next_line(fd);
	test_name = NULL;
	expected = NULL;
	lst = NULL;
	while (line)
	{
		if (strncmp(line, "TEST:", strlen("TEST:")) == 0)
			test_name = extract_test_value(line);
		else if (strncmp(line, "INPUT:", strlen("INPUT:")) == 0)
			input = extract_test_value(line);
		else if (strncmp(line, "EXPECTED:", strlen("EXPECTED:")) == 0)
			expected = extract_test_value(line);
		else if (line[0] == '-')
			append_new_test(&lst, input, test_name, expected);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lst);
}

static char	*extract_test_value(char *line)
{
	char	*firs_dp;
	char	*ret;

	firs_dp = ft_strchr(line, ':');
	ret = strip_newline(ft_substr(line, (firs_dp + 2)
				- line, 100));
	return (ret);
}

static void	append_new_test(t_list **lst,
				char	*line,
				char	*name,
				char	*expected)
{
	t_test	*test;

	assert(lst);
	assert(line);
	assert(name);
	assert(expected);
	test = calloc(sizeof(t_test), 1);
	if (!test)
	{
		log_error("Failed to allocate memory for test");
		return ;
	}
	test->line = line;
	test->name = name;
	test->expected = expected;
	ft_lstadd_back(lst, ft_lstnew(test));
}
