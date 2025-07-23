/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 execute_command.c									:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/07/26 09:08:26 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/07/26 09:30:36 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "execution/path.c"
#include "test.h"

int	main(int argc, char **argv)
{
	char	*prog_name;
	char	*path_env;
	char	*expected;
	char	*prog_path;

	if (argc != 3)
	{
		write(2, "Expected 2 argument\n", 21);
		exit(EXIT_FAILURE);
	}
	prog_name = argv[1];
	expected = argv[2];
	path_env = getenv("PATH");
	if (!path_env)
	{
		fprintf(stderr, "Failed to get PATH\n");
		exit(1);
	}
	prog_path = get_path(prog_name, path_env);
	assert(prog_path);
	if (strcmp(prog_path, expected))
	{
		test_fail("Expected: ", expected);
		printf("Got: %s \n", prog_path);
		return (1);
	}
	free(prog_path);
	return (0);
}
