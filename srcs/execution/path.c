/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dazzali <dazzali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:05:08 by dazzali           #+#    #+#             */
/*   Updated: 2025/07/28 12:07:25 by dazzali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*check_path_candidate(char *dir, char *program_name);
char		*get_path(char *program_name, char *path);

char	*resolve_exec_path(char *prog_name, t_ctx *ctx)
{
	char	*exec_path;
	char	*path_var;

	if (ft_strncmp(prog_name, "./", 2) == 0
		|| ft_strncmp(prog_name, "/", 1) == 0)
		exec_path = prog_name;
	else
	{
		path_var = get_shell_var_value(ctx->envs, "PATH");
		if (!path_var)
			exec_path = ft_strdup(prog_name);
		else
			exec_path = get_path(prog_name, path_var);
	}
	return (exec_path);
}

char	*get_path(char *program_name, char *path)
{
	char	**path_arr;
	char	*result;
	size_t	i;

	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (print_shell_error_ret_null(MALLOC_ERROR_MSG));
	i = 0;
	while (path_arr[i])
	{
		result = check_path_candidate(path_arr[i], program_name);
		if (result)
		{
			free_str_array(path_arr);
			return (result);
		}
		i++;
	}
	free_str_array(path_arr);
	return (NULL);
}

static char	*check_path_candidate(char *dir, char *program_name)
{
	char	*tmp;
	char	*complete_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	complete_path = ft_strjoin(tmp, program_name);
	free(tmp);
	if (!complete_path)
		return (NULL);
	if (access(complete_path, F_OK) == 0)
		return (complete_path);
	free(complete_path);
	return (NULL);
}
