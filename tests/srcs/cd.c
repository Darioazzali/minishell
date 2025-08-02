/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cd.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/11 10:33:09 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/18 11:38:57 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "test.h"
#include "minishell.h"

static int	_cd_null_dir(t_envs *envs);
static int	_cd_perm_den(t_envs *envs);
static int	_cd_parent(t_envs *envs);
static int	make_test(int (*fun) (t_envs *), t_envs *envs,
				char *test_name, t_cd_t *t);
static int	_cd_no_args(t_envs *envs);
static int	_cd_tilde(t_envs *envs);
static int	_cd_absolute_path(t_envs *envs);
static int	_cd_nonexistent(t_envs *envs);
static int	_cd_file_not_dir(t_envs *envs);
static int	_cd_oldpwd(t_envs *envs);
static int	_cd_too_many_args(t_envs *envs);
static int	_cd_zero_args(t_envs *envs);
static int	_cd_home_not_set(t_envs *envs);

int	main(int ac, char **argv, char **environ)
{
	int 	status;
	t_envs	*envs;
	t_cd_t	t = {0};

	(void)ac;
	(void)argv;
	envs = parse_envs(environ);
	status = 0;
	MAKE_TEST(cd_null_dir, envs, &t);
	MAKE_TEST(cd_parent, envs, &t);
	MAKE_TEST(cd_perm_den, envs, &t);
	MAKE_TEST(cd_no_args, envs, &t);
	MAKE_TEST(cd_absolute_path, envs, &t);
	MAKE_TEST(cd_tilde, envs, &t);
	MAKE_TEST(cd_nonexistent, envs, &t);
	MAKE_TEST(cd_file_not_dir, envs, &t);
	MAKE_TEST(cd_oldpwd, envs, &t);
	MAKE_TEST(cd_too_many_args, envs, &t);
	MAKE_TEST(cd_zero_args, envs, &t);
	MAKE_TEST(cd_home_not_set, envs, &t);
	_print_test_result(&t);
	return (status);
}
static int	_cd_too_many_args(t_envs *envs)
{
	char *av[4] = {"cd", "arg1", "arg2", NULL};

	return (chdir_btin(3, (const char **)av, envs) == 0); // Should fail
}

static int	_cd_zero_args(t_envs *envs)
{
	char	*av[1] = {"cd"};
	char	*home = getenv("HOME");
	char	*pwd;
	int		result;

	if (chdir_btin(1, (const char **)av, envs) != 0)
		return (1);
	pwd = getcwd(NULL, 0);
	result = strcmp(pwd, home);
	free(pwd);
	return (result);
}

static int	_cd_null_dir(t_envs *envs)
{
	char	*av[2]={"cd", ""};

	if (chdir_btin(2, (const char **)av, envs) != 1)
	{
		test_fail((char *)__func__, NULL);
		return (1);
	}
	else
	{
		test_success((char *)__func__, NULL);
		return (0);
	}
}

static int	_cd_perm_den(t_envs *envs)
{
	char	*av[2]={"cd", "/root"};

	if (chdir_btin(2, (const char **)av, envs) != 1)
	{
		test_fail((char *)__func__, NULL);
		return (1);
	}
	else
	{
		test_success((char *)__func__, NULL);
		return (0);
	}
}

static int	_cd_parent(t_envs *envs)
{
	char	*av[2]={"cd", ".."};
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (chdir_btin(2, (const char **)av, envs) != 0);
}

static int	make_test(int (*fun) (t_envs *), t_envs *envs,
				char *test_name, t_cd_t *t)
{
	int		test_status;
	char	*pwd;
	char	**back;

	back = malloc(sizeof(char *) * 2);
	back[0] = "cd";
	pwd = getcwd(NULL, 0);
	test_status = fun(envs);
	t->status |= test_status;
	t->t_total++;
	if (test_status != 0)
	{
		test_fail(test_name, NULL);
		t->t_fail++;
		return (1);
	}
	test_success(test_name, NULL);
	t->t_succ++;
	back[1] = pwd;
	chdir_btin(2, (const char **)back, envs);
	free(pwd);
	return (0);
}

static int	_cd_no_args(t_envs *envs)
{
	char	*_home;
	char	*av[2]={"cd", NULL};
	char	*pwd;

	_home = getenv("HOME");
	chdir_btin(2, (const char **)av, envs);
	pwd = getcwd(NULL, 0);
	return (strcmp(pwd, _home));
}

static int	_cd_tilde(t_envs *envs)
{
	char	*av[2]={"cd", "~"};
	char	*pwd;
	char	*_home;

	_home = getenv("HOME");
	chdir_btin(2, (const char **)av, envs);
	pwd = getcwd(NULL, 0);
	return (strcmp(pwd, _home));
}

static int	_cd_absolute_path(t_envs *envs)
{
	char	*tmp="/tmp";
	char	*av[2]={"cd", tmp};
	char	*pwd;

	chdir_btin(2, (const char **)av, envs);
	pwd = getcwd(NULL, 0);
	return (strcmp(pwd, tmp));
}

static int	_cd_nonexistent(t_envs *envs)
{
	char	*av[2]={"cd","/nonexistent"};

	return (chdir_btin(2, (const char **)av, envs) == 0);
}

static int	_cd_file_not_dir(t_envs *envs)
{
	char	*av[2]={"cd","/etc/passwd"};

	return (chdir_btin(2, (const char **)av, envs) == 0);
}

static int	_cd_oldpwd(t_envs *envs)
{
	char	*av[2]={"cd","/etc"};
	char	*av_1[2]={"cd","-"};
	char	*old_pwd;
	char	curr_pwd[1024];

	old_pwd = getcwd(NULL, 0);
	chdir_btin(2, (const char **)av, envs);
	getcwd(curr_pwd, 1024);
	if (strcmp(curr_pwd, old_pwd) == 0)
		return (1);
	chdir_btin(2, (const char **)av_1, envs);
	getcwd(curr_pwd, 1024);
	if (strcmp(curr_pwd, old_pwd) != 0)
		return (1);
	return (0);
}

static int	_cd_home_not_set(t_envs *envs)
{
	char 	*av[1] = {"cd"};
	char	*av_2[2] = {"HOME", NULL};
	int		result;

	unset_btin(&envs, av_2);
	result = (chdir_btin(1, (const char **)av, envs) == 0);
	set_shell_var(envs, "HOME", "/home");
	return (result);
}
