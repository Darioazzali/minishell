/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 cd.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/11 10:28:21 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/17 15:51:33 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "env.h"

static int	_update_oldpwd(t_envs *envs);
static int	_chdir_home_oldpwd(const char *var, t_envs *envs);
static int	_cd_err(char *message);
static int	_cd_error_chdir(const char *path);

/**
 * @brief Changes the current working directory (cd builtin implementation)
 * 
 * Implements the shell builtin command 'cd' with support for:
 * - cd (no args) → go to HOME directory
 * - cd ~ → go to HOME directory  
 * - cd - → go to OLDPWD and print new directory
 * - cd <path> → go to specified directory
 * 
 * Maintains PWD and OLDPWD environment variables
 * after successful directory change.
 * Provides specific error messages for various failure conditions.
 *
 * @param ac Argument count (including command name "cd")
 * @param av Argument vector where av[0]="cd" and av[1]=target_path
 * @param envs Pointer to shell environment variables structure
 * 
 * @return 0 on success (directory changed),
 * 1 on failure (error printed to stderr)
 * 
 * @see _chdir_home_oldpwd() for HOME/OLDPWD handling
 * @see _update_oldpwd() for environment variable updates
 * @see _cd_err() and _cd_error_chdir() for error reporting
 */
int	chdir_btin(int ac, const char **av, t_envs *envs)
{
	int			status;
	const char	*path;

	if (ac > 1)
		return (_cd_err("too many arguments"), 2);
	if (ac == 0)
		path = NULL;
	else
		path = av[0];
	if (path == NULL || !ft_strcmp(path, "~") || !ft_strcmp(path, "-"))
	{
		if (_chdir_home_oldpwd(path, envs))
			return (1);
	}
	else
	{
		if (*path == '\0')
			return (_cd_err("null directory"));
		status = chdir(path);
		if (status < 0)
			return (_cd_error_chdir(path));
	}
	if (_update_oldpwd(envs) == 1)
		return (1);
	return (0);
}

/**
* @brief Handles cd operations to HOME directory and OLDPWD (previous directory)
* 
* Internal helper function that processes special cd arguments:
* - NULL or "~" → change to HOME directory
* - "-" → change to OLDPWD (previous directory) and print new location
* 
* Retrieves target directory from shell environment variables and performs
* the directory change. For cd -, prints the new directory to stdout as
* required by POSIX specification.
*
* @param var The special path argument (NULL, "~", or "-")
* @param envs Pointer to shell environment variables structure
* 
* @return 0 on success (directory changed),
* 1 on failure (error printed to stderr)
* 
* @see get_shell_var_value() for environment variable retrieval
* @see _cd_err() for standard error reporting
* @see _cd_error_chdir() for chdir() failure reporting
* @see _pwd() for directory printing after cd -
*
*/
static int	_chdir_home_oldpwd(const char *var, t_envs *envs)
{
	char	*var_path;

	if (var == NULL || !ft_strcmp(var, "~"))
	{
		var_path = get_shell_var_value(envs, "HOME");
		if (!var_path)
			return (_cd_err("HOME not set"));
	}
	else if (!ft_strcmp(var, "-"))
	{
		var_path = get_shell_var_value(envs, "OLDPWD");
		if (!var_path)
			return (_cd_err("OLDPWD not set"));
	}
	if (chdir(var_path) < 0)
		return (_cd_error_chdir(var_path));
	if (var && !ft_strcmp(var, "-"))
		pwd_btin();
	return (0);
}

/**
* @brief Updates PWD and OLDPWD environment variables after directory change
* 
* Synchronizes shell environment variables with the actual
* current working directory:
* - Sets OLDPWD to the previous PWD value
* - Sets PWD to the current working directory (from getcwd())
* 
* This maintains the shell's directory history for cd - functionality and
* ensures environment variables reflect the actual filesystem state.
*
* @param envs Pointer to shell environment variables structure
* 
* @return 0 on success (variables updated),
* 1 on failure (error printed to stderr)
* 
*/
static int	_update_oldpwd(t_envs *envs)
{
	t_sh_var	*old_pwd;
	t_sh_var	*pwd;
	char		*new_pwd;

	old_pwd = get_shell_var(envs, "OLDPWD");
	pwd = get_shell_var(envs, "PWD");
	if (!old_pwd || !pwd)
		return (1);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (print_shell_error_ret_int(
				"Error getting current directory", 1));
	free(old_pwd->value);
	old_pwd->value = ft_strdup(pwd->value);
	if (!old_pwd->value)
	{
		free(new_pwd);
		return (print_shell_error_ret_int(MALLOC_ERROR_MSG, 1));
	}
	free(pwd->value);
	pwd->value = new_pwd;
	return (0);
}

static int	_cd_err(char *message)
{
	print_program_error("cd", message);
	return (1);
}

/* Handle chdir() system call errors with specific messages
 * @param path: the path that failed
 * @return: 1 (always fails)
 */
static int	_cd_error_chdir(const char *path)
{
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
