/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 error.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/09 18:44:59 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/09 18:47:10 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *message);

void	print_program_error(char *program_name, char *message)
{
	if (!program_name)
		return ;
	print_error(program_name);
	print_error(": ");
	if (message)
		print_error(message);
	else
		print_error("Error");
	print_error("\n");
}

static void	print_error(char *message)
{
	size_t	len;

	len = strlen(message);
	write(2, message, len);
}
