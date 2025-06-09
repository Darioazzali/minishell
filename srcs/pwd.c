/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pwd.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/09 17:37:52 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/09 17:38:31 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Basic pwd command
 *
 * Print the current working directory.
 *
 * @note For now the error message return from the command is not so
* 		 user friendly. We should understand if we can use errno
*/

int	main(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		print_program_error("pwd", "Error while "
			"displaying current directory\n");
		return (1);
	}
	else
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
