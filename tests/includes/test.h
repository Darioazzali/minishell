/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 test.h												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: dazzali <dazzali@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/06/14 09:27:26 by dazzali		   #+#	  #+#			  */
/*	 Updated: 2025/06/19 09:10:07 by dazzali		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "libft.h"
# include <cjson/cJSON.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define G_CHECKMARK "\033[32m✓\033[0m"  // Green checkmark
# define R_BALLOT    "\033[31m✗\033[0m"  // Red X
# define GREEN_BOLD "\033[1;32m"
# define RED_BOLD "\033[1;31m"
# define NORMAL "\033[m"

typedef struct s_json_input_t
{
	char	*input_line;
	char	**input_array;
	int		array_size;
}	t_json_input_t;

typedef struct s_cd_t
{
	int		status;
	size_t	t_succ;
	size_t	t_fail;
	size_t	t_total;
}	t_cd_t;

#define MAKE_TEST(test_name, envs, test_ptr) \
	make_test(_##test_name, envs, #test_name, test_ptr)

char			*strip_newline(char *g_line);
t_json_input_t	*read_json_input(const char *filename);
void			free_json_input(t_json_input_t *input);
char			*read_file(const char *filename);
char			**extract_string_array(cJSON *json_array, int *array_size);
t_json_input_t	*read_json_input(const char *filename);
void			free_json_input(t_json_input_t *input);
void			print_json_input(const t_json_input_t *input);
char			**extract_string_array(cJSON *json_array, int *array_size);
t_list			*from_array_to_ll(char **arr, int size);
void			test_fail(char *test_name, char *message);
void			test_success(char *test_name, char *message);
#endif
