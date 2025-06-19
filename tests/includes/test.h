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

typedef struct s_json_input_t
{
	char	*input_line;
	char	**input_array;
	int		array_size;
}	t_json_input_t;

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
#endif
