/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:16:16 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/26 08:21:08 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "minishell.h"

int			test_1(t_envs *envs);
static int	test_2(t_envs *envs);
static void	_make_test(int *test_ret,
				int (*test_fct)(t_envs *), char *test_name, t_envs *envs);
static int	test_unset(t_envs *envs);
static int	test_edit(t_envs *envs);

int	main(int argc, char **argv, char **env)
{
	t_envs	*envs;
	int		test_ret;

	(void)argc;
	(void)argv;
	test_ret = 0;
	envs = parse_envs(env);
	_make_test(&test_ret, test_1, "test_1", envs);
	_make_test(&test_ret, test_2, "test_2", envs);
	_make_test(&test_ret, test_unset, "test_unset", envs);
	_make_test(&test_ret, test_edit, "test_edit", envs);
	free_envs(envs);
	return (test_ret);
}

int	test_1(t_envs *envs)
{
	char	*list[2]={"allora=ciao", NULL};
	char	*key = "allora";
	char	*expected = "ciao";
	t_sh_var	*val;

	export_btin(list, envs);
	val = get_shell_var(envs, key);
	if (!val)
	{
		printf("ERROR: Variable '%s' not found\n", key);
		return (1);
	}
	if (strcmp(val->value, expected))
		return (1);
	return (0);
}

static int	test_2(t_envs *envs)
{
	char	*key = "variable";
	char	*list[2]={key, NULL};
	char	*expected = "ciao";
	t_sh_var	*val;

	set_shell_var(envs, key, "ciao");
	export_btin(list, envs);
	val = get_shell_var(envs, key);
	if (!val)
	{
		printf("ERROR: Variable '%s' not found\n", key);
		return (1);
	}
	if (strcmp(val->value, expected))
		return (1);
	return (0);
}

static int	test_edit(t_envs *envs)
{
	char	*key = "PWD";
	char	*list[2]={key, NULL};
	char	*expected = "ciao";
	t_sh_var	*val;

	set_shell_var(envs, key, "ciao");
	export_btin(list, envs);
	val = get_shell_var(envs, key);
	if (!val)
	{
		printf("ERROR: Variable '%s' not found\n", key);
		return (1);
	}
	if (strcmp(val->value, expected))
		return (1);
	return (0);
}

static int	test_unset(t_envs *envs)
{
	char	*list[2]={"key", NULL};
	char	*key = "key";
	char	*expected = "ciao";
	t_sh_var	*val;

	set_shell_var(envs, key, "ciao");
	export_btin(list, envs);
	val = get_shell_var(envs, key);
	if (!val)
	{
		printf("ERROR: Variable '%s' not found\n", key);
		return (1);
	}
	if (strcmp(val->value, expected))
		return (1);
	unset_btin(&envs, list);
	val = get_shell_var(envs, key);
	if (val)
		return (1);
	return (0);
}

static void _make_test(int *test_ret, int (*test_fct)(t_envs *), char *test_name, t_envs *envs)
{
	printf("%s: ", test_name);
	if (!test_fct(envs))
	{
		printf("OK\n");
	}
	else
	{
		printf("KO\n");
		*test_ret = 1;
	}
}
